// Andy Quoc Anh Dinh Tran 57422363

// gcc server.c -o server -lm
// ./server MSFT.csv TSLA.csv 30000

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <math.h>

#define MAXLINE 1024
#define LISTENQ 100

typedef struct sockaddr SA;

// functions
int open_listenfd(char *port);
void command_handler(int connfd);
bool stock_checker(char *stock);
bool date_checker(char *date);
int token_length(char *token);
bool date_checkfile(char *desired_date, char *desired_stock);
int range_checkfile(char *desired_start_date, char *desired_end_date, char *desired_stock);
void price_on_date(char *desired_date, char *desired_stock, char *token);
void maxprofit_on_date(char *desired_start_date, char *desired_end_date, char *desired_stock, char *token);

// variables
char *file_1, *file_2;
char stock_list[MAXLINE];
int list_size = 0;

int main(int argc, char const *argv[])
{   
    int listenfd, connfd;
    socklen_t clientlen;

    struct sockaddr_storage clientaddr; /* Enough room for any addr */
    char client_hostname[MAXLINE], client_port[MAXLINE];
    
    file_1 = (char *) argv[1];
    file_1 = strtok(file_1, ".");
    file_2 = (char *) argv[2];
    file_2 = strtok(file_2, ".");

    int i = 0;
    while (file_1[i] != '\0')
    {
        i++;
    }
    list_size = i;
    i = 0;
    while (file_2[i] != '\0')
    {
        i++;
    }
    list_size += i;
    sprintf(stock_list,"%s | %s",file_2,file_1);
    
    listenfd = open_listenfd((char*) argv[3]);
    if (listenfd != -1) {
        
        while (1) {
            printf("server started\n");
            clientlen = sizeof(struct sockaddr_storage); /* Important! */
            connfd = accept(listenfd, (SA *)&clientaddr, &clientlen);
            getnameinfo((SA *) &clientaddr, clientlen, client_hostname, MAXLINE, client_port, MAXLINE, 0);
            command_handler(connfd);
            close(connfd);
        }
    }
    else {
    }

    return 0;
}

void command_handler(int connfd)
{
    size_t n;
    char buf[MAXLINE];
    char *token, *stock, *start_date, *end_date; // to handle requests
    bool quit = false; // to keep shell running until quit is inputted
    char whitespace[MAXLINE];
    char price[MAXLINE];

    while ((!quit) && ((n = read(connfd, buf, MAXLINE)) != 0)) {

        strcpy(whitespace, buf);
        
        buf[n] = '\0';
        fputs(buf, stdout);

        // if input is empty, ask for input again
        if (strcmp(buf, "\n")==0) 
        { 
            write(connfd, "Invalid syntax", 15);
            continue;
        }

        token = strtok(whitespace, "\n");
        token = strtok(token, "     ");

        if (token == NULL) 
        { 
            write(connfd, "Invalid syntax", 15);
            continue;
        }
        if (strcmp(token, "\n")==0) 
        { 
            write(connfd, "Invalid syntax", 15);
            continue;
        }

        // start to split up input into components
        token = strtok(buf, "\n");
        token = strtok(token, "     ");

        // changing working directory
        if (strcmp(token, "quit")==0) 
        {
            write(connfd, "quit", 5);
            quit = true;
        }

        else if (strcmp(token, "List")==0) 
        {
            write(connfd, stock_list, list_size+4);
        }

        else if (strcmp(token, "Prices")==0) 
        {
            stock = strtok(NULL, "     ");
            if (stock_checker(stock) == false) {
                write(connfd, "Invalid syntax", 15);
                continue;
            }

            start_date = strtok(NULL, "     ");
            if (date_checker(start_date) == false) {
                write(connfd, "Invalid syntax", 15);
                continue;
            }

            if (date_checkfile(start_date, stock) == false) {
                write(connfd, "Unknown", 8);
                continue;
            }
            
            price_on_date(start_date, stock, price);
            write(connfd, price, strlen(price));
        }

        else if (strcmp(token, "MaxProfit")==0) 
        {
            stock = strtok(NULL, "     ");

            if (stock_checker(stock) == false) {
                write(connfd, "Invalid syntax", 15);
                continue;
            }

            start_date = strtok(NULL, "     ");
            if (date_checker(start_date) == false) {
                write(connfd, "Unknown", 8);
                continue;
            }

            end_date = strtok(NULL, "     ");
            if (date_checker(end_date) == false) {
                write(connfd, "Invalid syntax", 15);
                continue;
            }

            int range = range_checkfile(start_date, end_date, stock);

            if (range == 0) {
                write(connfd, "Unknown", 8);
                continue;
            }
            if (range == 1) {
                write(connfd, "Invalid syntax", 15);
                continue;
            }

            maxprofit_on_date(start_date, end_date, stock, price);
            write(connfd, price, strlen(price));
        }

        else {
            write(connfd, "Invalid syntax", 15);
        }

        strcpy(buf, "\0");
    }

    close(connfd);
    exit(0);
}


bool stock_checker(char *stock) {
    if (stock == NULL) {
        return false;
    }

    if (!(strcmp(stock, file_1)==0) && !(strcmp(stock, file_2)==0)) {
        return false;
    }
    return true;
}



bool date_checker(char *date) {
    bool date_correct = true;
    int date_check = 0;
    char digits[] = "1234567890";

    if (date == NULL) {
        return false;
    }

    date_correct = true;
    date_check = 0;

    while (date[date_check] != '\0') {
        if ((date_check == 4) || (date_check == 7)) {
            if (date[date_check] != '-') {
                date_correct = false;
                break;
            }
        }
        else {
            if ((date[date_check] < 48) || (57 < date[date_check])) {
                date_correct = false;
                break;
            }
        }
        date_check++;
    }

    if ((date_correct == false) || (date_check != 10)) {
        return false;
    }

    return true;
}


int token_length(char *token) {
    int i = 0;
    while (token[i] != '\0') {
        i++;
    }
    return i;
}


bool date_checkfile(char *desired_date, char *desired_stock) {


    char *token; // to handle requests
    char buf[1024];
    char * stock_file = malloc(strlen(desired_stock) + 1); 

    strcpy(stock_file, desired_stock);
    strcat(stock_file, ".csv");

    FILE *csvfile = fopen(stock_file, "r");


    if (csvfile == NULL) {
        free(stock_file);
        return false;
    }

    fgets(buf, 1024, csvfile); // skips first line

    while (fgets(buf, 1024, csvfile) != NULL) {
        token = strtok(buf, ",");
        
        

        if (strcmp(token, desired_date) == 0){
            fclose(csvfile);
            free(stock_file);
            return true;
        }
        
    }

    fclose(csvfile);
    free(stock_file);
    return false;

}


int range_checkfile(char *desired_start_date, char *desired_end_date, char *desired_stock) {


    char *token; // to handle requests
    char buf[1024];
    char * stock_file = malloc(strlen(desired_stock) + 1); 

    strcpy(stock_file, desired_stock);
    strcat(stock_file, ".csv");

    FILE *csvfile = fopen(stock_file, "r");


    if (csvfile == NULL) {
        free(stock_file);
        return 0;
    }

    fgets(buf, 1024, csvfile); // skips first line
    
    int s = -1;
    int e = -1;
    int i = 0;

    while (fgets(buf, 1024, csvfile) != NULL) {
        token = strtok(buf, ",");

        if (strcmp(token, desired_start_date) == 0){
            s = i;
        } 

        else if (strcmp(token, desired_end_date) == 0){
            e = i;
        } 
        i++;
    }

    fclose(csvfile);
    free(stock_file);
    if ((s == -1) || (e == -1)) {
        return 0; // not in file
    }
    if ( e <= s) {
        return 1; // end date before or is start date
    }
    return 2; // valid

}

void price_on_date(char *desired_date, char *desired_stock, char *return_price) {

    char *token; // to handle requests
    double value = 0;
    char buf[1024];
    char * stock_file = malloc(strlen(desired_stock) + 1); 
    strcpy(stock_file, desired_stock);
    strcat(stock_file, ".csv");

    FILE *csvfile = fopen(stock_file, "r");


    strcpy(return_price, "Unknown");

    if (csvfile == NULL) {
        free(stock_file);
        return;
    }

    fgets(buf, 1024, csvfile); // skips first line
    

    while (fgets(buf, 1024, csvfile) != NULL) {
        token = strtok(buf, ",");
        
        if (strcmp(token, desired_date) == 0){
            token = strtok(NULL, ","); // open
            token = strtok(NULL, ","); // high
            token = strtok(NULL, ","); // low
            token = strtok(NULL, ","); // close
            value = atof(token);
            value = round(value * 100) / 100;
            sprintf(return_price, "%.2f", value);
            break;
        }
    }

    fclose(csvfile);
    free(stock_file);

}


void maxprofit_on_date(char *desired_start_date, char *desired_end_date, char *desired_stock, char *return_price) {
    
    char *token; // to handle requests
    char buf[1024];
    char * stock_file = malloc(strlen(desired_stock) + 1); 
    strcpy(stock_file, desired_stock);
    strcat(stock_file, ".csv");

    FILE *csvfile = fopen(stock_file, "r");

    strcpy(return_price, "Unknown");

    if (csvfile == NULL) {
        free(stock_file);
        return;
    }

    fgets(buf, 1024, csvfile); // skips first line
    
    double current = 0;
    double lowest = 0;
    double cur_diff = 0;
    double max_diff = 0;
    bool range = false;
    

    while (fgets(buf, 1024, csvfile) != NULL) {
        token = strtok(buf, ",");
        
        if (strcmp(token, desired_start_date) == 0){
            token = strtok(NULL, ","); // open
            token = strtok(NULL, ","); // high
            token = strtok(NULL, ","); // low
            token = strtok(NULL, ","); // close
            current = atof(token);

            lowest = current;
            cur_diff = current - lowest;
            max_diff = cur_diff;
            range = true;
        }
        
        else if (strcmp(token, desired_end_date) == 0){
            token = strtok(NULL, ","); // open
            token = strtok(NULL, ","); // high
            token = strtok(NULL, ","); // low
            token = strtok(NULL, ","); // close
            current = atof(token);

            cur_diff = current - lowest;
            if (max_diff < cur_diff) {
                max_diff = cur_diff;
            }
            if (current < lowest) {
                lowest = current;
            }

            range = false;
            max_diff = round(max_diff * 100) / 100;
            sprintf(return_price, "%.2f", max_diff);
            break;
        } 
        else if (range) {
            token = strtok(NULL, ","); // open
            token = strtok(NULL, ","); // high
            token = strtok(NULL, ","); // low
            token = strtok(NULL, ","); // close
            current = atof(token);

            cur_diff = current - lowest;
            if (max_diff < cur_diff) {
                max_diff = cur_diff;
            }
            if (current < lowest) {
                lowest = current;
            }
        }
    }

    fclose(csvfile);
    free(stock_file);
}



int open_listenfd(char *port)
{
    struct addrinfo hints, *listp, *p;
    int listenfd, optval=1;

    /* Get a list of potential server addresses */
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_socktype = SOCK_STREAM; /* Accept connect. */
    hints.ai_flags = AI_PASSIVE | AI_ADDRCONFIG; /* …on any IP addr */
    hints.ai_flags |= AI_NUMERICSERV; /* …using port no. */
    getaddrinfo(NULL, port, &hints, &listp);

    /* Walk the list for one that we can bind to */
    for (p = listp; p; p = p->ai_next) {

        /* Create a socket descriptor */
        if ((listenfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) < 0){
            //printf("Socket failed\n");
            continue; /* Socket failed, try the next */
        }
        
        /* Eliminates "Address already in use" error from bind */
        setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, (const void *)&optval , sizeof(int));
        
        /* Bind the descriptor to the address */
        if (bind(listenfd, p->ai_addr, p->ai_addrlen) == 0){
            //printf("Socket binded, success\n");
            break; /* Success */
        }
        
        close(listenfd); /* Bind failed, try the next */
    }
    
    /* Clean up */
    freeaddrinfo(listp);
    
    if (!p) /* No address worked */{
        return -1;
    }
    
    /* Make it a listening socket ready to accept conn. requests */
    if (listen(listenfd, LISTENQ) < 0) {
        close(listenfd);
        return -1;
    }

    return listenfd;
}