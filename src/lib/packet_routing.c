#include "packet_routing.h"

/* Hard code everything - This is basically routing/forwarding function of router */
//[TBA: HARDCODE VALUES ACC TO TOPOLOGY and CAREFULLY]

void get_fwding_info(const unsigned char *packet,struct fwd_info *args)
{
    struct custom_header *pkthdr = (struct custom_header *)packet;

    if (ntohs((pkthdr->custip).dest_ip) == 5) {
            args->next_hop = 3;
            strcpy(args->fwding_inf_name,"lo");
    } else if (ntohs((pkthdr->custip).dest_ip) == 6) {
            args->next_hop = 4;
            strcpy(args->fwding_inf_name,"lo");
    } else {
    }

}

