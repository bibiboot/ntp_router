#include "packet_update.h"

void packet_update(void *newpacket,const unsigned char *packet, struct timestamp *recv_kern,struct timeval *drtt,uint16_t next_hop,int packet_size,const struct pcap_pkthdr *header)
{
    unsigned char *payload = (unsigned char *)packet + C_HLEN;
   
    struct custom_header *pkthdr = (struct custom_header *)packet;
    (pkthdr->custeth).next_hop = htons(next_hop);
    memcpy(newpacket,pkthdr,packet_size);

    memcpy(newpacket + packet_size,&(recv_kern->sec),4);
    memcpy(newpacket + packet_size + 4,&(recv_kern->fsec),4);
    memcpy(newpacket + packet_size + 8,&(drtt->tv_sec),4);
    memcpy(newpacket + packet_size + 12,&(drtt->tv_usec),4);
   
    printf(KMAG "\nPacket forwarded : Ignore Lengths in this forwarded packet\n" RESET);
    packet_print(newpacket,packet_size);
    printf(KMAG "(Updated packet size)" RESET);
    packet_size = calc_packet_size((uint64_t *)newpacket);

}
