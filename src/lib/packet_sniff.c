#include "packet_sniff.h"
#include "packet_print.h"
#include "filter.h"
#include "cntp_handler.h"


void packet_capture(unsigned char *args,const struct pcap_pkthdr *header, const unsigned char *packet)
{

    if (true == is_cntp(packet,args)) {
        printf(KMAG "CNTP PACKET RECEIVED \n" RESET);
        packet_print(header,packet);
        cntp_handler(header,packet,args);
    } else {
        printf(KMAG "NOT DESTINED TO ME. DROPPING PACKET \n" RESET);
        packet_print(header,packet);
    }
}

void *configure_capture(void *args)
{
    pcap_t *handle;

    struct interface *inf = (struct interface *)args;

    printf ("Inteface name is %s\n",inf->inf_name);
    printf ("Inteface address is %d\n",inf->addr);
    printf ("Inteface socket is %d\n",inf->sock);

    handle = pcap_open_live(inf->inf_name, SNAP_LEN, 1, 1000, errbuf);
    if (NULL == handle)
    {
        printf( "Couldn't open device %s: %s\n", inf->inf_name, errbuf);
        exit(EXIT_FAILURE);
    }

    pcap_loop(handle,-1,packet_capture,(u_char *)args);

}
