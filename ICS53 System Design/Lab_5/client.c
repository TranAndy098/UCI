// Andy Quoc Anh Dinh Tran 57422363

// gcc client.c -o client
// ./client 127.0.0.1 30000

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#define MAXLINE 1024

// variables
char input[100]; // instantiate input string

int open_clientfd(char *hostname, char *port) {

    int clientfd;
    struct addrinfo hints, *listp, *p;

    /* Get a list of potential server addresses */
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_socktype = SOCK_STREAM; /* Open a connection */
    hints.ai_flags = AI_NUMERICSERV; /* …using numeric port arg. */
    hints.ai_flags |= AI_ADDRCONFIG; /* Recommended for connections */
    getaddrinfo(hostname, port, &hints, &listp);

    /* Walk the list for one that we can successfully connect to */
    for (p = listp; p; p = p->ai_next) {
        
        /* Create a socket descriptor */
        if ((clientfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) < 0){
            continue; /* Socket failed, try the next */
        }
            
        /* Connect to the server */
        if (connect(clientfd, p->ai_addr, p->ai_addrlen) != -1){
            break; /* Success */
        }
        
        close(clientfd); /* Connect failed, try another */
    }

    /* Clean up */
    freeaddrinfo(listp);
    
    if (!p) /* All connects failed */{
        return -1;
    }
    else /* The last connect succeeded */{
        
        return clientfd;
    }
}

int main(int argc, char const *argv[])
{   
    bool quit = false; // to keep shell running until quit is inputted

    int clientfd;
    char *host, *port, buf[MAXLINE];

    int end = 0;

    host = (char*) argv[1];
    port = (char*) argv[2];

    clientfd = open_clientfd(host, port);

    if (clientfd != -1) {
        printf("> ");

        while ((!quit) && (fgets(buf, MAXLINE, stdin) != NULL)) {
            write(clientfd, buf, strlen(buf));

            end = read(clientfd, buf, MAXLINE);
            buf[end] = '\0';
            
            if (strcmp(buf, "quit")==0) 
            {
                quit = true;
                break;
            } 

            printf("%s\n", buf);
            printf("> ");
            buf[0] = '\0';
        }
    }
    else {
        printf("No Server Found\n ");
    }

    close(clientfd); 
    return 0;
}