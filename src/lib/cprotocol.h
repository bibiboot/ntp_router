#pragma once

#include "globals.h"

#define ROUTER_MAC 0
#define NODE1_MAC 1
#define NODE2_MAC 2
#define NODE3_MAC 3

#define NODE1_IP 1
#define NODE2_IP 2
#define NODE3_IP 3

#define CNTP_PORT 3

#define C_HLEN 68

/*
struct data {
    uint32_t dest_mac;
    uint32_t src_mac;
};

struct pattern {
    uint64_t value;
};

struct custom_ethernet {
    uint16_t next_hop;
};

struct custom_ip {
    uint16_t src_ip;
    uint16_t dest_ip;
};

struct custom_udp {
    uint16_t port;
};

struct custom_header {
    struct custom_ethernet custeth;
    struct custom_ip custip;
    struct custom_udp custudp;
};
*/
/*
 * Custom protocol
 */
struct custom_packet_header{
    uint16_t next_hop_addr;
    uint16_t dst_addr;
    uint16_t src_addr;
    uint16_t dst_port;
    char padding[60];
};
