#include "packet_update.h"

void packet_update(void *newpacket,const unsigned char *packet, struct timeval *rcvtimestamp,struct timeval *sendtimestamp,struct timeval *drtt,uint16_t next_hop,int packet_size,const struct pcap_pkthdr *header)
{
    unsigned char *payload = (unsigned char *)packet + C_HLEN;
   
    struct custom_header *pkthdr = (struct custom_header *)packet;
    (pkthdr->custeth).next_hop = htons(next_hop);
    memcpy(newpacket,pkthdr,packet_size);

    memcpy(newpacket + packet_size,&(rcvtimestamp->tv_sec),4);
    memcpy(newpacket + packet_size + 4,&(rcvtimestamp->tv_usec),4);
    memcpy(newpacket + packet_size + 8,&(sendtimestamp->tv_sec),4);
    memcpy(newpacket + packet_size + 12,&(sendtimestamp->tv_usec),4);
    memcpy(newpacket + packet_size + 16,&(drtt->tv_sec),4);
    memcpy(newpacket + packet_size + 20,&(drtt->tv_usec),4);
   
    printf(KMAG "\nPacket forwarded : Ignore Lengths in this forwarded packet\n" RESET);
    packet_print(newpacket,packet_size);
    packet_size = calc_packet_size((uint64_t *)newpacket);

}
