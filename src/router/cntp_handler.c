#include "cntp_handler.h"
#include "packet_routing.h"

void cntp_handler(const struct pcap_pkthdr *header,const unsigned char *packet,void* args,int packet_size)
{
    struct timeval rcvtimestamp;
    struct timeval sendtimestamp;
    struct timeval drtt;
    struct fwd_info fwd_info;

    void *newpacket = (void *)malloc(packet_size + 24);
    if (NULL == newpacket)
    {
        printf(KMAG "Error:malloc()\n");
        exit(1);
    }

    memset(&fwd_info,0,sizeof(struct fwd_info));

    //Get receive timestamp
    rcvtimestamp.tv_sec = (header->ts).tv_sec;
    rcvtimestamp.tv_usec = (header->ts).tv_usec;

    get_fwding_info(packet,&fwd_info,args);

    //get_drtt();
    gettimeofday(&drtt,NULL);

    //Get send timestamp
    gettimeofday(&sendtimestamp,NULL);

    /*printf("| rcv timestamp seconds:%ld ",rcvtimestamp.tv_sec);
    printf(" microseconds:%ld |",rcvtimestamp.tv_usec);
    printf("| drtt timestamp seconds:%ld ",drtt.tv_sec);
    printf(" microseconds:%ld |",drtt.tv_usec);
    printf("| send timestamp seconds:%ld ",sendtimestamp.tv_sec);
    printf(" microseconds:%ld |",sendtimestamp.tv_usec);*/


    packet_update(newpacket,packet,&rcvtimestamp,&sendtimestamp,&drtt,fwd_info.next_hop,packet_size);
    packet_forward(newpacket,packet_size + 24,args);
    //free(newpacket);

}
