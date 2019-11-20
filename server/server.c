/*
 *Based of a server retrieved from: https://dzone.com/articles/web-server-c
 * On: 30/8/19
 *
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define EOL "\r\n"
#define EOL_SIZE 2

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

void send_new(int fd, char *msg)
{
    int len = strlen(msg);
    if (send(fd, msg, len, 0) == -1)
    {
        printf("Error in send\n");
    }
}

int recv_new(int fd, char *buffer)
{
    char *p = buffer;              // Use of a pointer to the buffer rather than dealing with the buffer directly
    int eol_matched = 0;           // Use to check whether the recieved byte is matched with the buffer byte or not
    while (recv(fd, p, 1, 0) != 0) // Start receiving 1 byte at a time
    {
        if (*p == EOL[eol_matched]) // if the byte matches with the first eol byte that is '\r'
        {
            ++eol_matched;
            if (eol_matched == EOL_SIZE) // if both the bytes matches with the EOL
            {
                *(p + 1 - EOL_SIZE) = '\0'; // End the string
                return (strlen(buffer));    // Return the bytes recieved
            }
        }
        else
        {
            eol_matched = 0;
        }
        p++; // Increment the pointer to receive next byte
    }
    return (0);
}
void request_response(int fd, int msg){
    switch(msg){
        case 0:
            printf("200 OK, Content-Type: text\n");
            send_new(fd, "HTTP/1.1 200 OK\r\n");
            send_new(fd, "Server : Web Server in C\r\n\r\n");
            break;
        case 1:
            printf("400 Bad Request, Content-Type: text\n");
            send_new(fd, "HTTP/1.1 400 Bad Request Error\r\n");
            send_new(fd, "Server : Web Server in C\r\n\r\n");
            break;
        default:
            printf("400 Bad Request, Content-Type: text\n");
            send_new(fd, "HTTP/1.1 400 Bad Request Error\r\n");
            send_new(fd, "Server : Web Server in C\r\n\r\n");
            break;
    }
}

void driver_com(char* msg)
{
    FILE *file;
    file = fopen("/dev/ttyACM0","w");  //Opening device file
    int i = 0;
    // for(i = 0 ; i < 3 ; i++)
    // {
    fprintf(file,"%s\n",msg); //Writing to the file
    sleep(1);
    //}
    fclose(file);
}

int connection(int fd)
{
    char request[500], resource[500], *ptr;
    int fd1, length;
    if (recv_new(fd, request) == 0)
    {
        printf("Recieve Failed\n");
    }
    printf("%s\n", request);
    // Check for a valid browser request
    ptr = strstr(request, " HTTP/");
    printf("%s", ptr);
    if (ptr == NULL)
    {
        printf("NOT HTTP !\n");
    }
    else
    {
        *ptr = 0;
        ptr = NULL;

        if (strncmp(request, "GET ", 4) == 0)
        {
            printf("200 OK, Content-Type: json");
            send_new(fd, "HTTP/1.1 200 OK\r\n");
            send_new(fd, "Server : Web Server in C\r\n\r\n");
            send_new(fd, "{\"tag\": \"u\"}");
            ptr = request + 4;
        }
        if(strncmp(request, "POST /api/move", 14) == 0)
        {
            //receive_image(fd,1);
            char string[2048];
            printf("\n \n");
            read(fd, string, 512);
            printf("%s", string);
            char* value;
            if(strstr(string, "value:1a") != NULL){
                value = "1";
                request_response(fd, 0);
                printf("\n %s \n", value);
            }
            else if (strstr(string, "value:1b") != NULL){
                value = "1";
                request_response(fd, 0);
                printf("\n %s \n", value);
            }
            else if (strstr(string, "value:1c") != NULL){
                value = "1";
                request_response(fd, 0);
                printf("\n %s \n", value);
            }
            else if (strstr(string, "value:2a") != NULL){
                value = "2";
                request_response(fd, 0);
                printf("\n %s \n", value);
            }
            else if (strstr(string, "value:2b") != NULL){
                value = "2";
                request_response(fd, 0);
                printf("\n %s \n", value);
            }
            else if (strstr(string, "value:2c") != NULL){
                value = "2";
                request_response(fd, 0);
                printf("\n %s \n", value);
            }
            else if(strstr(string, "value:3a")!= NULL){
                value = "3";
                request_response(fd, 0);
                printf("\n %s \n", value);
            }
            else if(strstr(string, "value:3b")!= NULL){
                value = "3";
                request_response(fd, 0);
                printf("\n %s \n", value);
            }
            else if(strstr(string, "value:3c")!= NULL){
                value = "3";
                request_response(fd, 0);
                printf("\n %s \n", value);
            }
            else if(strstr(string, "value:4a")!= NULL){
                value = "4";
                request_response(fd, 0);
                printf("\n %s \n", value);
            }
            else if(strstr(string, "value:4b")!= NULL){
                value = "4";
                request_response(fd, 0);
                printf("\n %s \n", value);
            }
            else if(strstr(string, "value:4c")!= NULL){
                value = "4";
                request_response(fd, 0);
                printf("\n %s \n", value);
            }
            else if(strstr(string, "value:5a")!= NULL){
                value = "5";
                request_response(fd, 0);
                printf("\n %s \n", value);
            }
            else if(strstr(string, "value:5b")!= NULL){
                value = "5";
                request_response(fd, 0);
                printf("\n %s \n", value);
            }
            else if(strstr(string, "value:5c")!= NULL){
                value = "5";
                request_response(fd, 0);
                printf("\n %s \n", value);
            }
            else if(strstr(string, "value:6a")!= NULL){
                value = "6";
                request_response(fd, 0);
                printf("\n %s \n", value);
            }
            else if(strstr(string, "value:6b")!= NULL){
                value = "6";
                request_response(fd, 0);
                printf("\n %s \n", value);
            }
            else if(strstr(string, "value:6c")!= NULL){
                value = "6";
                request_response(fd, 0);
                printf("\n %s \n", value);
            }
            else if(strstr(string, "value:7a")!= NULL){
                value = "7";
                request_response(fd, 0);
                printf("\n %s \n", value);
            }
            else if(strstr(string, "value:7b")!= NULL){
                value = "7";
                request_response(fd, 0);
                printf("\n %s \n", value);
            }
            else if(strstr(string, "value:7c")!= NULL){
                value = "7";
                request_response(fd, 0);
                printf("\n %s \n", value);
            }
            else if(strstr(string, "value:8a")!= NULL){
                value = "8";
                request_response(fd, 0);
                printf("\n %s \n", value);
            }
            else if(strstr(string, "value:8b")!= NULL){
                value = "8";
                request_response(fd, 0);
                printf("\n %s \n", value);
            }
            else if(strstr(string, "value:8c")!= NULL){
                value = "8";
                request_response(fd, 0);
                printf("\n %s \n", value);
            }
            else if(strstr(string, "value:9a")!= NULL){
                value = "9";
                request_response(fd, 0);
                printf("\n %s \n", value);
            }
            else if(strstr(string, "value:9b")!= NULL){
                value = "9";
                request_response(fd, 0);
                printf("\n %s \n", value);
            }
            else if(strstr(string, "value:9c")!= NULL){
                value = "9";
                request_response(fd, 0);
                printf("\n %s \n", value);

            }else{
                value = "0";
                request_response(fd, 1);
                printf("Internal error");
            }
            driver_com(value);
            close(fd);
        }else{
            request_response(fd, 1);
        }
    }
    shutdown(fd, SHUT_RDWR);
}

int main(int argc, char *argv[]) {
    int sockfd, newsockfd, portno, pid;
    socklen_t clilen;
    struct sockaddr_in serv_addr, cli_addr;
    /*
    if (argc < 2) {
        fprintf(stderr, "ERROR, no port provided\n");
        exit(1);
    }
    */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        error("ERROR opening socket");
    bzero((char *) &serv_addr, sizeof(serv_addr));
    portno =  9016;//atoi(argv[1]);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);
    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
        error("ERROR on binding");
    listen(sockfd, 5);
    printf("Server running in port %d", portno);
    clilen = sizeof(cli_addr);
    /*
    Server runs forever, forking off a separate
    process for each connection.
    */
    while (1) {
        newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);
        if (newsockfd < 0)
            error("ERROR on accept");
        pid = fork();
        if (pid < 0)
            error("ERROR on fork");
        if (pid == 0)
        {
            close(sockfd);
            connection(newsockfd);
            exit(0);
        }
        else
            close(newsockfd);
    } /* end of while */
    close(sockfd);
    return 0; /* we never get here */
}