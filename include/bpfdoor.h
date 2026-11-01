#pragma once
#include "pch.h"
#include <sys/socket.h>
#include <linux/filter.h>
#include <linux/if_ether.h>
#include <unistd.h>


bool start_bpfdoor();

// 헤더들 구조체

#pragma pack(push,1)

struct eth_hdr{
    uint8_t des_address[6];
    uint8_t source_address[6];
    uint16_t type;
};


#pragma pack(pop)

#pragma pack(push,1)

struct ip_hdr {
    // gcc에서 :4(비트 필드)와 같이 비트를 나눠 선언하면 낮은 비트부터 나열하기 때문에 ihl을 먼저 선언해야 version(4bit) -> ihl(4bit)순서대로 나열됨
    uint8_t ihl : 4;
    uint8_t version : 4;

    uint8_t tos;
    uint16_t length;
    uint16_t id;
    uint16_t offset;
    uint8_t ttl;
    uint8_t protocol;
    uint16_t checksum;

    uint32_t src_address;
    uint32_t dst_address;

};

#pragma pack(pop)

#pragma pack(push,1)

struct tcp_hdr{
    uint16_t src_port;
    uint16_t dst_port;

    uint32_t seq;
    uint32_t ack;

    uint8_t rsv : 4;
    uint8_t offset : 4;

    //flags 별로 나눠야할 수도 있음 (syn ack rst같은게 여기 있던 것 같다.)
    //rst는 0x04
    uint8_t flags;
    uint16_t window;
    uint16_t checksum;
    uint16_t urgent_ptr;

};

#pragma pack(pop)

#pragma pack(push,1)

struct udp_hdr{
    uint16_t src_port;
    uint16_t dst_port;
    uint16_t len;
    uint16_t checksum;
};

#pragma pack(pop)
