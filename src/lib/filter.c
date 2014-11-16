#include "filter.h"

//HARDCODED
bool is_cntp(const unsigned char *packet,void *args)
{
    struct interface *inf = (struct interface *)args;
    struct custom_header *pkthdr = (struct custom_header *)packet;

    if (ntohs((pkthdr->custeth).next_hop) == inf->addr
        && ntohs((pkthdr->custip).src_ip) == inf->dnode_ip
        && ntohs((pkthdr->custudp).port) == CNTP_PORT) {
        return true;
    } else {
        return false;
    }
}
