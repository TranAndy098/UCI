#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <ctype.h>
#include <signal.h>
#include <fcntl.h>

#define MAX_LINE 1024
#define MAX_DIR_LEN 200
#define MAX_ARGC 80
#define MAX_JOBS 5

// job struct
struct job {
    pid_t pid;
    char status[20];
    int isForeground;
    char cmd[81];
    struct job *nextJob;
};
typedef struct job job;

// job array
job *jobs = NULL;
size_t numJobs = 0;

// function prototypes
void intHandler(int);
void stopHandler(int);
void childHandler(int);
char *getIOFile(char*, char, int*);
FILE *setInputStream(char*);
FILE *setOutputStream(char*, int);
void execLocal(char*, char*, char*, char*, int);
void insertJob(pid_t, char*, int);
void removeJob(pid_t);
job *findJob(int);
void killJob(char*);
void printJobs();
void fg(char*);
void bg(char*);

pid_t pid = 0; // current PID for foreground process

int main() {
    signal(SIGINT, intHandler); // set CTR-C handler
    signal(SIGCHLD, childHandler); // reaps sub-processes
    signal(SIGTSTP, stopHandler); // catch ctrl-z

    // initialize space for commands
    char cmd[MAX_LINE+1];
    char *cmdBuff = cmd;

    // main loop
    int quitting = 0;
    do {
        // get command and remove newline as needed
        printf("prompt >");
        size_t buffersize = MAX_LINE+1;
        size_t charsRead = getline(&cmdBuff, &buffersize, stdin);

        // if nothing read just redo the loop
        if (charsRead == 0 || (charsRead == 1 && cmd[0] == '\n'))
            continue;

        // make sure null is at the end
        if (cmd[charsRead-1] == '\n')
            cmd[charsRead-1] = '\0';

        // get operation
        char cmdCopy[MAX_LINE+1];
        strcpy(cmdCopy, cmd);
        char *op = strtok(cmd, " ");

        // check if the user specified input or output files
        int append = 0;
        char* inFileName = getIOFile(cmdCopy, '<', &append);
        char* outFileName = getIOFile(cmdCopy, '>', &append);

        // change working directory
        if (strcmp(op, "cd") == 0) {
            op = strtok(NULL, "");
            chdir(op);
        }
        // print working directory
        else if (strcmp(op, "pwd") == 0) {
            // save the current stdout, then set it
            int stdout = dup(1);
            FILE *outFile = setOutputStream(outFileName, append);

            // print the cwd
            char dir[MAX_DIR_LEN];
            printf("%s\n", getcwd(dir, MAX_DIR_LEN));

            // reset stdout back to terminal
            dup2(stdout, 1);
            close(stdout);
            if (outFile != NULL)
                fclose(outFile);
        }
        // quit shell
        else if (strcmp(op, "quit") == 0) {
            quitting = 1;
        }
        // kill a background process
        else if (strcmp(op, "kill") == 0) {
            op = strtok(NULL, "");
            killJob(op);
        }
        // show running and stopped jobs
        else if (strcmp(op, "jobs") == 0) {
            // save the current stdout, then set it
            int stdout = dup(1);
            FILE *outFile = setOutputStream(outFileName, append);

            printJobs(); // print jobs

            // reset stdout back to terminal
            dup2(stdout, 1);
            close(stdout);
            if (outFile != NULL)
                fclose(outFile);
        }
        // move process to foreground/running
        else if (strcmp(op, "fg") == 0) {
            op = strtok(NULL, "");
            fg(op);
        }
        // move process to background/running
        else if (strcmp(op, "bg") == 0) {
            op = strtok(NULL, "");
            bg(op);
        }
        // execute user program
        else {
            if (numJobs < MAX_JOBS)
                execLocal(op, cmdCopy, inFileName, outFileName, append);
        }

    } while (!quitting);

    // terminate all children
    job *currJob = jobs;
    while (currJob != NULL) {
        char currPid[10];
        sprintf(currPid,"%d",currJob->pid);
        currJob = currJob->nextJob;
        killJob(currPid);
    }

    return 0;
}

// get the args input file specified by <
char *getIOFile(char* cmd, char pipe, int *append) {
    printf(" - In %s -\n", "getIOFile");
    // look for pipe
    char *ptr = strchr(cmd, pipe);

    // if we found it, lets get the input file
    char* fileName = NULL;
    if(ptr != NULL) {
        // if we are setting the output file and there is 2 > then we are appending to a file
        if (*ptr == '>' && *(ptr+1) == '>') {
            *append = 1;
            ++ptr;
        }
        ptr += 2;
        char *endOfNamePtr = strchr(ptr, ' ');
        if (endOfNamePtr == NULL)
            endOfNamePtr = strchr(ptr, '\0');
        int fileNameSize = endOfNamePtr - ptr;
        fileName = (char*) malloc((fileNameSize + 1) * sizeof(char));
        memcpy(fileName, ptr, fileNameSize);
        fileName[fileNameSize] = '\0';
    }

    return fileName;
}

// create child process and execute the desired file
void execLocal(char *programName, char *wholeCmd, char *inFileName, char *outFileName, int appendOutput) {
    printf(" - In %s -\n", "execLocal");
    printf(" - In %s_%d -\n", "execLocal", 1);
    // we get 80 max arguments and first is function/file name
    char *args[MAX_ARGC] = {NULL};
    args[0] = programName;
    printf(" - In %s_%d -\n", "execLocal", 2);

    // parse arguments
    char *arg = strtok(NULL, " ");
    int count = 1;
    printf(" - In %s_%d -\n", "execLocal", 3);
    while (arg != NULL && count < MAX_ARGC) {
        // if we ran into a pipe, lets skip it and the next arg
        if (*arg == '<' || *arg == '>')
            strtok(NULL, " ");
        // else add the arg
        else {
            args[count] = arg;
            ++count;
        }
        arg = strtok(NULL, " ");
    }
    printf(" - In %s_%d -\n", "execLocal", 4);

    // determine if this is a background or foreground process
    int isForeground = 1;
    if (strcmp(args[count-1], "&") == 0) {
        isForeground = 0;
        args[count-1] = NULL; // remove background proc arg from args list   
    }
    printf(" - In %s_%d -\n", "execLocal", 5);

    // create child process or wait
    pid = fork();
    if (pid == 0) {
        signal(SIGINT, SIG_IGN);
        signal(SIGTSTP, SIG_IGN);
        setInputStream(inFileName);
        setOutputStream(outFileName, appendOutput);
        execvp(programName, args);
        execv(programName, args);
        exit(123);
    }
    // if parent, lets insert into jobs list
    else {
        insertJob(pid, wholeCmd, isForeground);
    }
    printf(" - In %s_%d -\n", "execLocal", 6);
    
    if (isForeground) {
        printf(" - In %s_%d -\n", "execLocal", 7);
        int status;
        waitpid(pid,&status,WUNTRACED); // return on foreground end or stopping
        if (!WIFSTOPPED(status)) {
            printf(" - In %s_%d -\n", "execLocal", 8);
            removeJob(pid);
        }
    }
    printf(" - In %s_%d -\n", "execLocal", 9);

    pid = 0; // make sure ctrl-c doesnt end a background process and kill will only be called on a valid pid
}

// set the input file stream
FILE *setInputStream(char* fileName) {
    printf(" - In %s -\n", "setInputStream");
    FILE *file = NULL;
    if (fileName != NULL) {
        
        // open the provided file
        file = fopen(fileName, "r");
        if (file != NULL) {
            int fd = fileno(file);
            dup2(fd, 0); // set stdin to redirect to this file
        }
    }

    return file;
}

// set the output file stream
FILE *setOutputStream(char* fileName, int append) {
    printf(" - In %s -\n", "setOutputStream");
    FILE *file = NULL;
    if (fileName != NULL) {

        // open the provided file
        FILE *file;
        if (append)
            file = fopen(fileName, "a");
        else
            file = fopen(fileName, "w");

        // if the file was successfully opened, setup stdout redirect
        if (file != NULL) {
            int fd = fileno(file);
            dup2(fd, 1);
        }
    }

    return file;
}

void insertJob(pid_t pPid, char *cmd, int isForeground) {
    printf(" - In %s -\n", "insertJob");
    // create new job
    job *newJob = (job*) malloc(sizeof(job));
    newJob->pid = pPid;
    strcpy(newJob->status, "Running");
    strcpy(newJob->cmd, cmd);
    newJob->nextJob = NULL;
    newJob->isForeground = isForeground;

    // insert newJob into list
    if (jobs == NULL) {
        jobs = newJob;
    }
    else {
        job *currJob = jobs;
        while(currJob->nextJob != NULL)
            currJob = currJob->nextJob;

        currJob->nextJob = newJob;
    }

    // increment numJobs
    ++numJobs;
}

void removeJob(pid_t pPid) {
    printf(" - In %s -\n", "removeJob");
    // empty list just return
    if (numJobs == 0)
        return;

    // if front one is to delete, we take and move head over
    job *toDel = NULL;
    if (jobs->pid == pPid) {
        toDel = jobs;
        jobs = jobs->nextJob;
    }
    // else loop till we find it
    else {
        job *currJob = jobs->nextJob;
        job *prevJob = jobs;
        while(currJob != NULL && currJob->pid != pid) {
            prevJob = currJob;
            currJob = currJob->nextJob;
        }

        toDel = currJob; // get potential one to delete

        // we are deleting and need to update the connection
        if (toDel != NULL)
            prevJob->nextJob = toDel->nextJob;
    }

    // free if we found the job
    if (toDel != NULL) {
        free(toDel);
        --numJobs;
    }
}

// find job by pid or job id
job *findJob(int id) {
    printf(" - In %s -\n", "findJob");
    job *currJob = jobs;
    int currJobId = 1;
    while (currJob != NULL && currJob->pid != id && currJobId != id) {
        currJob = currJob->nextJob;
        ++currJobId;
    }

    return currJob;
}

void killJob(char *id) {
    printf(" - In %s -\n", "killJob");
    // determine if searching by jobId or Pid
    int iId;
    int isJobId = 0;
    if (*id == '%') {
        isJobId = 1;
        ++id;
    }
    
    // find job
    iId = atoi(id);
    job *currJob = findJob(iId);

    if (currJob != NULL) {
        // make sure pid or jid matches what type of search the user did
        if ((!isJobId && currJob->pid != iId) || (isJobId && currJob->pid == iId))
            return;
        kill(currJob->pid, SIGKILL);
    }
}

void printJobs() {
    printf(" - In %s -\n", "printJobs");
    printf("[<job_id>] (<pid>) <status> <command_line>\n");

    int i = 0;
    job *currJob = jobs;
    while (currJob != NULL) {
        printf("[%d] (%d) %s %s\n", i+1, currJob->pid, currJob->status, currJob->cmd);
        currJob = currJob->nextJob;
        ++i;
    }
}

void fg(char *id) {
    printf(" - In %s -\n", "fg");
    // determine if searching by jobId or Pid
    int iId;
    int isJobId = 0;
    if (*id == '%') {
        isJobId = 1;
        ++id;
    }
    
    // find job
    iId = atoi(id);
    job *currJob = findJob(iId);

    if (currJob != NULL) {
        // make sure pid or jid matches what type of search the user did
        if ((!isJobId && currJob->pid != iId) || (isJobId && currJob->pid == iId))
            return;

        pid = currJob->pid;
        kill(pid, SIGCONT); // continue process
        strcpy(currJob->status, "Running"); // set running in list
        currJob->isForeground = 1; // make sure it is a foreground process now

        int status;
        waitpid(pid,&status,WUNTRACED); // wait for process since foreground
        if (!WIFSTOPPED(status))
            removeJob(pid);

	    pid = 0; // reset pid
    }
}

void bg(char *id) {
    printf(" - In %s -\n", "bg");
    // determine if searching by jobId or Pid
    int iId;
    int isJobId = 0;
    if (*id == '%') {
        isJobId = 1;
        ++id;
    }
    
    // find job
    iId = atoi(id);
    job *currJob = findJob(iId);

    if (currJob != NULL) {
        // make sure pid or jid matches what type of search the user did and that status is stopped
        if ((!isJobId && currJob->pid != iId) || (isJobId && currJob->pid == iId) || (strcmp(currJob->status, "Stopped") != 0))
            return;

        kill(currJob->pid, SIGCONT); // continue process
        strcpy(currJob->status, "Running"); // set running in list
        currJob->isForeground = 0; // make sure it is a background process now
    }
}

// handler to make sure parent isnt killed on sigint
void intHandler(int signum) {
    printf(" - In %s -\n", "intHandler");
    if (pid != 0)
        kill(pid, SIGKILL);
}

// handler for ctrl-z
void stopHandler(int signum) {
    printf(" - In %s -\n", "stopHandler");
    if (pid != 0) {
        kill(pid, SIGSTOP);
        job *stoppedJob = findJob(pid);
        strcpy(stoppedJob->status, "Stopped");
    }
}

// reap terminated subprocesses
void childHandler(int signum) {
    printf(" - In %s -\n", "childHandler");
    pid_t jobPid = waitpid(-1, 0, WNOHANG);
    if (jobPid > 0)
        removeJob(jobPid);
}
