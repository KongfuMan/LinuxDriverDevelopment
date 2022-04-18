//
// Created by liang on 11/24/21.
//
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>


/** This is the application that read/write from the device
 * "./chrdevbaseAPP /dev/chrdevchild 1"  represents Read from device
 * "./chrdevbaseAPP /dev/chrdevchild 2"  represents Write into device
 * */
int main(int argc, char *argv[]){
    if (argc != 3){
        printf("Not enough input parameters, supposed to be 3");
        return -1;
    }
    //This will force stdout to be line-buffered.
    setvbuf(stdout, NULL, _IONBF, 0);
    int ret = 0;
    int fd = 0;
    char *file_name = argv[1];
    char buf[100];
    char write_buf[100];
    static char usr_data[] = {"user data"};
    fd = open(file_name, O_RDWR);  //open device `file_name`
    if (fd < 0){
        printf("Cannot open file '%s' \r\n", file_name);
        return -1;
    }else{
        printf("Open file '%s' success \r\n", file_name);
    }
    if (atoi(argv[2]) == 1){
        ret = read(fd, buf, 50);
        if (ret < 0){
            printf("failed to read file '%s'\r\n", file_name);
            return -1;
        }else{
            printf("Read from file '%s' success, data %s\r\n", file_name, buf);
        }
    }

    if (atoi(argv[2]) == 2){
        memcpy(write_buf, usr_data, sizeof(usr_data));
        ret = write(fd, write_buf, 50);
        if (ret < 0){
            printf("Failed to write file %s\r\n", file_name);
            return -1;
        }else{
            printf("Write file '%s' success\r\n", file_name);
        }
    }

    ret = close(fd);
    if (ret < 0){
        printf("Failed to close file '%s'\r\n", file_name);
        return -1;
    }else{
        printf("Close file '%s' success\r\n", file_name);
    }
    return 0;
}
