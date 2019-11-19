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
            printf("200 OK, Content-Type: text\n");
            send_new(fd, "HTTP/1.1 200 OK\r\n");
            send_new(fd, "Server : Web Server in C\r\n\r\n");
            //receive_image(fd,1);

        }

        if(strncmp(request, "POST /categorize", 16) == 0)

        if (ptr == NULL)
        {
            //receive_image(fd,2);
        }
        else
        {
            /*
            if (ptr[strlen(ptr) - 1] == '/')
            {
                strcat(ptr, "index.html");
            }
            strcpy(resource, webroot());
            strcat(resource, ptr);
            char *s = strchr(ptr, '.');
            int i;
            for (i = 0; extensions[i].ext != NULL; i++)
            {
                if (strcmp(s + 1, extensions[i].ext) == 0)
                {
                    fd1 = open(resource, O_RDONLY, 0);
                    printf("Opening \"%s\"\n", resource);
                    if (fd1 == -1)
                    {
                        printf("404 File not found Error\n");
                        send_new(fd, "HTTP/1.1 404 Not Found\r\n");
                        send_new(fd, "Server : Web Server in C\r\n\r\n");
                        send_new(fd, "<html><head><title>404 Not Found</head></title>");
                        send_new(fd, "<body><p>404 Not Found: The requested resource could not be found!</p></body></html>");
                        //Handling php requests
                    }
                    else if (strcmp(extensions[i].ext, "php") == 0)
                    {
                        php_cgi(resource, fd);
                        sleep(1);
                        close(fd);
                        exit(1);
                    }
                    else
                    {
                        printf("200 OK, Content-Type: %s\n\n",
                               extensions[i].mediatype);
                        send_new(fd, "HTTP/1.1 200 OK\r\n");
                        send_new(fd, "Server : Web Server in C\r\n\r\n");
                        if (ptr == request + 4) // if it is a GET request
                        {
                            if ((length = get_file_size(fd1)) == -1)
                                printf("Error in getting size !\n");
                            size_t total_bytes_sent = 0;
                            ssize_t bytes_sent;
                            while (total_bytes_sent < length)
                            {
                                //Zero copy optimization
                                if ((bytes_sent = sendfile(fd, fd1, 0,
                                                           length - total_bytes_sent)) <= 0)
                                {
                                    if (errno == EINTR || errno == EAGAIN)
                                    {
                                        continue;
                                    }
                                    perror("sendfile");
                                    return -1;
                                }
                                total_bytes_sent += bytes_sent;
                            }
                        }
                    }
                    break;
                }
                int size = sizeof(extensions) / sizeof(extensions[0]);
                if (i == size - 2)
                {
                    printf("415 Unsupported Media Type\n");
                    send_new(fd, "HTTP/1.1 415 Unsupported Media Type\r\n");
                    send_new(fd, "Server : Web Server in C\r\n\r\n");
                    send_new(fd, "<html><head><title>415 Unsupported Media Type</head></title>");
                    send_new(fd, "<body><p>415 Unsupported Media Type!</p></body></html>");
                }
            }
            printf(&fd1);
            close(fd);
             */
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
    portno = 9000;    //atoi(argv[1]);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);
    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
        error("ERROR on binding");
    listen(sockfd, 5);
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
