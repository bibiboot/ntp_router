#include "cntp_handler.h"
#include "packet_routing.h"

void cntp_handler(const struct pcap_pkthdr *header,const unsigned char *packet,void* args)
{
    void *newpacket = (void *)malloc(header->len + 24);
    if (NULL == newpacket)
    {
        printf(KMAG "Error:malloc()\n");
        exit(1);
    }

    struct fwd_info fwd_info;
    memset(&fwd_info,0,sizeof(struct fwd_info));

    //Get receive timestamp
    printf(KMAG "\n received timestamp \n" RESET);
    printf("sizeof(struct timeval) is %ld\n",sizeof(struct timeval));
    printf("%ld seconds\n",(header->ts).tv_sec);
    printf("%ld microseconds\n",(header->ts).tv_usec);

    get_fwding_info(packet,&fwd_info);
    printf("Next hop is %d\n",fwd_info.next_hop);
    printf("Forwarding Interface is %s\n",fwd_info.fwding_inf_name);

    //get_drtt();

    //Get send timestamp

    packet_update(newpacket,packet,NULL,NULL,NULL,fwd_info.next_hop,header->len);
    packet_forward(newpacket,header->len + 24,args);
    //free(newpacket);

}
