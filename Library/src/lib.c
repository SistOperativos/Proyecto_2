#include<stdio.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include <sys/stat.h>
#include <fcntl.h>
#include <strings.h>

char* charCon(int num) {
    char* buf = malloc(sizeof(num));
    snprintf(buf, sizeof buf, "%d", num);
    return buf;
}

int writePos(int fd, int position){
    char* msg = charCon(position);
    int sz = write(fd, "\n", strlen("\n")); 
    sleep(1);
    sz = write(fd, msg, strlen(msg));
    sleep(1);
    return 0;
}

int initDriver(){
    int fd = open("/dev/myarmdriver",O_RDWR | O_NONBLOCK); 
    if (fd < 0) 
    { 
        perror("r1"); 
        exit(1); 
    } 
    sleep(1);
    return fd;
}

int closeDriver(int fd){
    close(fd); 
    return 0;
}

/*

int main() 
{ 
  int fd = initDriver(); 
  int writing = writePos(fd, 5);
  int closing = closeDriver(fd);

}
 */