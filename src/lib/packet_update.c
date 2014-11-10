#include "packet_update.h"

void packet_update(void *newpacket,const unsigned char *packet, struct timeval *rcvtimestamp,struct timeval *sendtimestamp,struct timeval *drtt,uint16_t next_hop,int packet_size,const struct pcap_pkthdr *header)
{
    unsigned char* payload = (unsigned char *)packet + C_HLEN;
   
    /* Ethernet frame min packet size is 64 bytes - 60 bytes (payload + data) + 4 bytes FRC*/ 
    if (packet_size <= 60)
    {
	packet_size = (C_HLEN + strlen(payload));	
	printf("\npacket size is %d\n",packet_size);
    }

    struct custom_header *pkthdr = (struct custom_header *)packet;
    (pkthdr->custeth).next_hop = htons(next_hop);
    memcpy(newpacket,pkthdr,packet_size);

    memcpy(newpacket + packet_size,"SOURABHK",8);
    memcpy(newpacket + packet_size + 8,"SOURABHK",8);
    memcpy(newpacket + packet_size + 16,"SOURABHK",8);
    /*memcpy(newpacket + packet_size,&(rcvtimestamp->tv_sec),4);
    memcpy(newpacket + packet_size + 4,&(rcvtimestamp->tv_usec),4);
    memcpy(newpacket + packet_size + 8,&(sendtimestamp->tv_sec),4);
    memcpy(newpacket + packet_size + 12,&(sendtimestamp->tv_usec),4);
    memcpy(newpacket + packet_size + 16,&(drtt->tv_sec),4);
    memcpy(newpacket + packet_size + 20,&(drtt->tv_usec),4);
   
    printf (KMAG "\nDEBUG START:\n" RESET); 
    printf("| rcv timestamp seconds:%ld ",rcvtimestamp->tv_sec);
    printf(" microseconds:%ld |",rcvtimestamp->tv_usec);
    printf("| drtt timestamp seconds:%ld ",drtt->tv_sec);
    printf(" microseconds:%ld |",drtt->tv_usec);
    printf("| send timestamp seconds:%ld ",sendtimestamp->tv_sec);
    printf(" microseconds:%ld |",sendtimestamp->tv_usec);
    printf (KMAG "\nDEBUG END:\n" RESET);*/ 

    printf(KMAG "Packet forwarded\n" RESET);
    packet_print(NULL,newpacket);

}
