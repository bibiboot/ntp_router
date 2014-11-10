#include "packet_update.h"

void packet_update(void *newpacket,const unsigned char *packet, uint64_t *rcvtimestamp,uint64_t *sendtimestamp,uint64_t *drtt,uint16_t next_hop,int packet_size)
{

    printf ("packet_size is %d\n",packet_size);

    struct custom_header *pkthdr = (struct custom_header *)packet;
    (pkthdr->custeth).next_hop = htons(next_hop);
    memcpy(newpacket,pkthdr,packet_size);

    memcpy(newpacket + packet_size,"SOURABHK",8);
    memcpy(newpacket + packet_size + 8,"SOURABHK",8);
    memcpy(newpacket + packet_size + 16,"SOURABHK",8);

    printf(KMAG "Packet forwarded\n" RESET);
    packet_print(NULL,newpacket);

}
