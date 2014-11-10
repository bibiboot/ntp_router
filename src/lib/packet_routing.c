#include "packet_routing.h"
#include "sock_details.h"

/* Hard code everything - This is basically routing/forwarding function of router */
//[TBA: HARDCODE VALUES ACC TO TOPOLOGY and CAREFULLY]

void get_fwding_info(const unsigned char *packet,struct fwd_info *args,void *arg)
{
    struct interface *inf = (struct interface *)arg;

    struct custom_header *pkthdr = (struct custom_header *)packet;

    if (ntohs((pkthdr->custip).dest_ip) == 5) {
            args->next_hop = 3;
    	    inf->sk.sll_ifindex = inf_to_index("eth0");
            //strcpy(args->fwding_inf_name,"eth1");
    } else if (ntohs((pkthdr->custip).dest_ip) == 6) {
            args->next_hop = 4;
    	    inf->sk.sll_ifindex = inf_to_index("eth1");
            //strcpy(args->fwding_inf_name,"lo");
    } else {
    }

}

