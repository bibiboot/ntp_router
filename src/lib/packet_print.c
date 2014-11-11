#include "packet_print.h"
#include "cprotocol.h"


void packet_print(const u_char *packet,int packet_size)
{
    printf(KMAG "SNIFF: " RESET);
    struct custom_header *pkthdr = (struct custom_header *)packet;
    unsigned char *payload = (unsigned char *) packet + C_HLEN;
    
    struct timeval *temp = (struct timeval *)(packet + packet_size);

    printf("Total [%d]: Header size [%d]: Payload [%d]: \n",
         packet_size, C_HLEN,packet_size - 8);
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
    printf("| %4d |",ntohs((pkthdr->custudp).port));
   
    /*printf("| rcv timestamp seconds:%ld ",temp->tv_sec);
    printf(" microseconds:%ld |",temp->tv_usec);
    temp = temp + 1;
    printf("| drtt timestamp seconds:%ld ",temp->tv_sec);
    printf(" microseconds:%ld |",temp->tv_usec);
    temp = temp + 1;
    printf("| send timestamp seconds:%ld ",temp->tv_sec);
    printf(" microseconds:%ld |",temp->tv_usec);*/
    printf("\n++++++++++++++++++++++++++++++++++++++++++++\n");

}
