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

#include <stdbool.h>

int max_jobs = 5; // max number of jobs provided in assignment pdf
int max_line = 80; // max number in line provided in assignment pdf
int max_argc = 80; // max number of args provided in assignment pdf

// jobs struct (4.1) to store job id, foreground or not, status, and its command input
struct job { 
    int pid;
    bool foreground;
    char status[100];
    char input[100];
};

struct job jobs[5]; // global array of jobs
int jobs_size = 0; // global counter of current jobs, both f
pid_t pid; // global pid for handlers

char* args[90]; // instantiate args arrray
char input[100]; // instantiate input string
char original[100]; // instantiate original string to store command before using strtok
char directory[256]; // instantiate working directory string for current directory

// print all current jobs, both running and stopped 
void print_jobs() {
    printf("Printing Jobs\n");

    for (int i = 0; i < jobs_size; i++)
    {
        printf("[%d] (%d) %s %s", i+1, jobs[i].pid, jobs[i].status, jobs[i].input);
    }
}


// go through jobs array and see if id matches a stored job
bool findJob(int id) {
    printf("Checking if PID exists\n");

    bool found = false;
    for (int i = 0; i < jobs_size; i++) 
    {
        if (jobs[i].pid == id) 
        {
            found = true;
        }
    }
    return found;
}


// takes in token and if it starts with "%" then will take the index and return its pid match the job id, else return pid from token
int getPID(char *token) {
    printf("Getting Job PID\n");

    token = strtok(NULL, " ");
    int pid_to_kill = -1;
    if (token[0] == '%') {
        token = strtok(token, "%%");
        pid_to_kill = strtol(token, NULL, 10) - 1;

        if (pid_to_kill < jobs_size) 
        {
            pid_to_kill = jobs[pid_to_kill].pid;
        } 
        else 
        {
            pid_to_kill = -1;
        }
    }
    else 
    {
        pid_to_kill = strtol(token, NULL, 10);
    }
    return pid_to_kill;
}


// using the id, will go through jobs array and shift all jobs after specfied job matching id, forward
void removeJob(int id) {
    printf("Removing Job\n");

    if (!findJob(id)) {
        printf("Job Not Found\n");
        return;
    }

    printf("Job size before is %d\n", jobs_size);

    bool move = false;
    for (int i = 0; i < jobs_size; i++) 
    {
        if (jobs[i].pid == id) 
        {
            move = true;
        }
        if (move && (i+1 != jobs_size)) 
        {
            jobs[i].pid = jobs[i+1].pid;
            jobs[i].foreground = jobs[i+1].foreground;
            strcpy(jobs[i].status, jobs[i+1].status);
            strcpy(jobs[i].input, jobs[i+1].input);

        }
        else if (move && (i+1 == jobs_size)) 
        {
            jobs_size--;
        }
    }

    printf("Job size after is %d\n", jobs_size);
}


// using the id, will kill the job then will remove it from jobs array
void killJob(int pid) {
    printf("Killing Job\n");

    if (!findJob(pid)) 
    {
        printf("Job Not Found\n");
        return;
    }

    kill(pid, SIGKILL);
    removeJob(pid);
    
    printf("Job %d getting killed\n", pid);
}


// creates file pointer with name and lets stdin be input file
FILE *inputFile(bool inputting, char *name) 
{
    printf("Input File Creating\n");

    FILE *file = NULL;
    if (inputting)
    {
        file = fopen(name, "r");
        if (file != NULL)
        {
            dup2(fileno(file), STDIN_FILENO);
        }
    }
    return file;
}


// creates file pointer with name and let stdout be output file
FILE *outputFile(bool outputting, bool appending, char *name) 
{
    printf("Output File Creating\n");

    FILE *file = NULL;
    if (outputting)
    {
        if (appending) {
            file = fopen(name, "a");
        }
        else 
        {
           file = fopen(name, "w"); 
        }
        
        if (file != NULL){
            dup2(fileno(file), STDOUT_FILENO);
        }
    }
    return file;
}


// program execution for both foreground and background
void executing(char *token, char *input_file_name, char *output_file_name, bool inputting, bool outputting, bool appending) 
{
    printf("Program Executing\n");

    char last_token[100]; // instantiate string to be check if foreground or background
    int amount; // variable used to keep track of amount of args
    bool fg = false; // to check if job is foreground or background

    // reset args array to all nulls
    while ((args[amount] != NULL) && (amount < 80)) {
        args[amount] = NULL;
        amount++;
    }    

    args[0] = (char*) token; // args will store the command being ran
    token = strtok(NULL, " ");

    amount = 1; // start looking at args for command
    // goes though entered command and stores args
    while ((token != NULL) && (amount < 80)) {
        // skip pass input/outpout characters
        if ((strcmp(token, "<") == 0) || (strcmp(token, ">") == 0)){
            token = strtok(NULL, " ");
        }
        else {
            args[amount] = token;
            amount++;
        }
        token = strtok(NULL, " ");
    }

    amount = 0;
    // goes and finds the last argument
    while ((args[amount] != NULL) && (amount < 80)) {
        strcpy(last_token, args[amount]);
        amount++;
    }

    // if last argument is "&" then foreground, if so remove it so exec does not have it
    if  (!(strcmp(last_token, "&") == 0)) {
        fg = true;
    }
    else {
        args[amount--] = NULL;
    }

    pid = fork();
    // pid = 0: child process; else parent process
    if (pid == 0) 
    {
        signal(SIGINT, SIG_IGN); // for ctrl c signals
        signal(SIGTSTP, SIG_IGN); // for ctrl z signals
        inputFile(inputting, input_file_name);
        outputFile(outputting, appending, output_file_name);
        execv(args[0], args);
        execvp(args[0], args);
        exit(321);
    } 
    else 
    {
    // adding job into jobs array with the correct information
    jobs[jobs_size].pid = pid; // job pid
    jobs[jobs_size].foreground = fg; // foreground or backgorund
    strcpy(jobs[jobs_size].status, "Running"); // status
    strcpy(jobs[jobs_size].input, original); // command input
    jobs_size++;
    }

    // if job is foreground, returns when job is finished or interupted
    if (fg == true) {   
        int status;
        waitpid(pid, &status, WUNTRACED);
        if (!WIFSTOPPED(status))
        {
            removeJob(pid);
        }
    }
    pid = 0; // reset so handlers will work correctly
}


// takes id of job and will move it to foreground 
void foreground(int id) 
{
    printf("Foregrounding Job %d\n", id);

    if (!findJob(id)) 
    {
        printf("Job Not Found\n");
        return;
    }

    for (int i = 0; i < jobs_size; i++) 
    {
        // if jobid matches, will change job information and send signal to continue
        if (jobs[i].pid == id) 
        {
            pid = id;
            strcpy(jobs[i].status, "Running");
            jobs[i].foreground = true;
            kill(pid, SIGCONT);

            // if job is foreground, returns when job is finished or interupted
            if (jobs[i].foreground==true) 
            {      
                int status;
                waitpid(pid, &status, WUNTRACED);
                if (!WIFSTOPPED(status))
                {
                    removeJob(pid);
                }     
            }
            pid = 0;  // reset so handlers will work correctly
        }
    }
}


// takes id of stopped job and will move it to background 
void background(int id) {
    printf("Backgrounding Job %d\n", id);

    if (!findJob(id)) 
    {
        printf("Job Not Found\n");
        return;
    }
            
    for (int i = 0; i < jobs_size; i++) 
    {
        // if jobid matches, will change job information and send signal to continue if job is correctly stopped
        if (jobs[i].pid == id) {
            if (strcmp(jobs[i].status, "Stopped") == 0) {
                strcpy(jobs[i].status, "Running");
                kill(id, SIGCONT);
            }
            else {
                printf("Job %d was not stopped\n", pid);
            }
        }
    }

}


// handler for ctrl c to kill currently running foreground job
void c_handler(int sig) {
    printf("Ctrl C Handler\n");

    if (pid != 0)
    {
        kill(pid, SIGKILL);
    }
}


// handler for ctrl z to stop currently running foreground job
void z_handler(int sig) {
    printf("Ctrl Z Handler\n");

    if (pid != 0) 
    {
        for (int i = 0; i < jobs_size; i++) 
        {
            // if jobid matches, will change job information and send signal to stop
            if (jobs[i].pid == pid) 
            {
                kill(pid, SIGSTOP);
                strcpy(jobs[i].status, "Stopped");
                jobs[i].foreground = false;
            }
        }
    }
}


// handler to reap child process
void childHandler(int signum) {
    printf("Child Process Handler\n");

    pid_t jobPid = waitpid(-1, 0, WNOHANG); // waits for child process to finish/interupt
    if (jobPid > 0)
    {
        printf("Removing Child Process %d\n", jobPid);
        removeJob(jobPid);
    }
}


int main(int argc, char const *argv[])
{   
    signal(SIGINT, c_handler); // setups ctrl c handler
    signal(SIGTSTP, z_handler); // setups ctrl z handler
    signal(SIGCHLD, childHandler); // setups handler for child process reaps

    char *token; // to handle requests
    bool quit = false; // to keep shell running until quit is inputted
    
    char file_check[100]; // copy input to get filenames if specfied
    char input_file_name[100]; // input file name storage
    char output_file_name[100]; // output file name storage
    bool inputting = false;
    bool outputting = false;
    bool appending = false;
    FILE *input_file = NULL;
    FILE *output_file = NULL;

    // gets current working directory
    if (getcwd(directory, sizeof(directory)) == NULL) 
    {
        perror("getcwd() error"); 
    }

    // while loop runs until "quit" is the input
    while (!quit) 
    {
        // get input, strip ending newline from terminal and then get first token of input while spliting at spaces
        printf("prompt > ");
        fgets(input, 1048, stdin);
        strcpy(original, input);
        strcpy(file_check, input);

        // if input is empty, ask for input again
        if (strcmp(input, "\n")==0) 
        { 
            printf("empty command\n"); 
            continue;
        }

        // need to handle space and tabbed commands


        // go through input to see if filenames are specfied
        token = strtok(file_check, "\n");
        token = strtok(token, " ");
        inputting = false;
        outputting = false;
        appending = false;

        while (token != NULL)
        {
            if (strcmp(token, "<")==0) 
            {
                token = strtok(NULL, " ");
                inputting = true;
                strcpy(input_file_name, token);
            }
            else if (strcmp(token, ">")==0) 
            {
                token = strtok(NULL, " ");
                outputting = true;
                strcpy(output_file_name, token);
            }
            else if (strcmp(token, ">>")==0) 
            {
                token = strtok(NULL, " ");
                outputting = true;
                appending = true;
                strcpy(output_file_name, token);
            }
            token = strtok(NULL, " ");
        }
        
        // start to split up input into components
        token = strtok(input, "\n");
        token = strtok(token, " ");

        // changing working directory
        if (strcmp(token, "cd")==0) 
        {
            token = strtok(NULL, " ");
            // if chdir is -1, then cd error, else store new working directory
            if (chdir(token) == -1) 
            {
                printf("cd: no such file or directory: %s\n", token);
            }
            else 
            {
                getcwd(directory, sizeof(directory));
            }
        }

        // print current working directory
        else if (strcmp(token, "pwd")==0) 
        {
            int console = dup(1); // saving console to file descriptor 1
            output_file = outputFile(outputting, appending, output_file_name);

            printf("%s\n", directory); 

            // reset output back to console
            dup2(console, 1);
            close(console);
            if (output_file != NULL) 
            {
                fclose(output_file);
            }
        }

        // quit shell
        else if (strcmp(token, "quit")==0) 
        { 
            quit = true; 
        }

        // print all jobs running or stopped
        else if (strcmp(token, "jobs")==0) 
        { 
            int console = dup(1); // saving console to file descriptor 1
            output_file = outputFile(outputting, appending, output_file_name);

            print_jobs();
            
            // reset output back to console
            dup2(console, 1);
            close(console);
            if (output_file != NULL) 
            {
                fclose(output_file);
            }
        }

        // restart specified job in foreground if possible
        else if (strcmp(token, "fg")==0) 
        { 
            int pid_to_fg = getPID(token);
            if (pid_to_fg != -1)
            {
                foreground(pid_to_fg);
            }
            else 
            {
                printf("Not possible for Job %d to be in Foreground\n", pid_to_fg);
            }
        }

        // restart specified job in background if possible
        else if (strcmp(token, "bg")==0) 
        { 
            int pid_to_bg = getPID(token);
            if (pid_to_bg != -1)
            {
                background(pid_to_bg);
            }
            else 
            {
                printf("Not possible for Job %d to be in Background\n", pid_to_bg);
            }
        }

        // kill specfied job if possible
        else if (strcmp(token, "kill")==0) 
        { 
            int pid_to_kill = getPID(token);
            if (pid_to_kill != -1)
            {
                killJob(pid_to_kill);
            }
            else {
                printf("Not possible to kill Job %d\n", pid_to_kill);
            }
        }

        // if not other commands then executable program
        else 
        {
            if (jobs_size < max_jobs) {
                executing(token, input_file_name, output_file_name, inputting, outputting, appending);
            }
            else {
                printf("Current number of jobs is at the limit\n");
            }
        }
    }

    printf("Shutting Down Shell\n");
    // not calling killJobs because does not to restructure jobs array
    for (int i = 0; i < jobs_size; i++)
    {
        printf("Job %d is getting killed\n", jobs[i].pid);
        kill(jobs[i].pid, SIGKILL);
    }
    return 0;
}
