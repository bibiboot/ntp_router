#include "packet_print.h"
#include "cprotocol.h"


void packet_print(const struct pcap_pkthdr *header,const u_char *packet)
{
    //int packet_size = (int)header->len;

    printf(KMAG "SNIFF: " RESET);
    struct custom_header *pkthdr = (struct custom_header *)packet;
    unsigned char *payload = (unsigned char *) packet + C_HLEN;
    
    /*void *payload = (void *) packet + C_HLEN;

    struct timeval *rcvt = (struct timeval *)packet + 11;
    struct timeval *sendt = (struct timeval *)packet + 19;
    struct timeval *drtt = (struct timeval *)packet + 27;*/


    //printf("Total [%d]: Header size [%d]: Payload [%d]: %s\n",
     //     packet_size, C_HLEN,packet_size - 8, payload);
    printf("++++++++++++++++++++++++++++++++++++++++++++\n");
    printf("| %s ","NEXT_HOP");
    printf("| %s ","SRC_IP");
    printf("| %s ","DEST_IP");
    printf("| %s ","PORT");
    printf("| %s |","PYLD");
    printf("\n");
    printf("| %8d ",ntohs((pkthdr->custeth).next_hop));
    printf("| %6d ",ntohs((pkthdr->custip).src_ip));
    printf("| %7d ",ntohs((pkthdr->custip).dest_ip));
    printf("| %4d ",ntohs((pkthdr->custudp).port));
    printf("| %s |",payload);
    /*printf("| rcv timestamp seconds:%ld ",rcvt->tv_sec);
    printf(" microseconds:%ld |",rcvt->tv_usec);
    printf("| drtt timestamp seconds:%ld ",drtt->tv_sec);
    printf(" microseconds:%ld |",drtt->tv_usec);
    printf("| send timestamp seconds:%ld ",sendt->tv_sec);
    printf(" microseconds:%ld |",sendt->tv_usec);*/
    printf("\n++++++++++++++++++++++++++++++++++++++++++++\n");

}
