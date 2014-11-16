#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/wait.h>
#include <stdbool.h>
#include <sys/time.h>
#include <pthread.h>
#include <pcap.h>
#include <netpacket/packet.h>
#include <net/ethernet.h> /* the L2 protocols */

#include "config.h"
#include "color.h"
#include "cprotocol.h"
#include "uthash.h"

#define SNAP_LEN 1518

// Interface Information

#define NUM_OF_INF 3

#define INF1 "eth1"
#define INFADDR1 2
#define DNODEIP1 1

#define INF2 "eth0"
#define INFADDR2 3
#define DNODEIP2 4

FILE *LOGFILE;

typedef struct hashl {
    int key;
    char value[100];
    UT_hash_handle hh;
} dict_node;

struct interface {
    char inf_name[64];
    uint16_t addr;
    uint16_t dnode_ip;  // Used for filtering
    int sock;
    struct sockaddr_ll sk;
    pthread_t thrd;
};


struct fwd_info {
    uint16_t next_hop;
    char fwding_inf_name[64];
};

struct globals {
    struct config config;
    dict_node *hashl;
    struct interface inf[NUM_OF_INF];
    pthread_t ipc_th;
    char *drtt;
};

char errbuf[PCAP_ERRBUF_SIZE];

extern struct globals globals;
