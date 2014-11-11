#include "packet_sniff.h"
#include "packet_print.h"
#include "filter.h"
#include "cntp_handler.h"

int calc_packet_size(uint64_t *temp)
{
    int packet_size = 0;
   
   /* Ethernet frame min packet size is 64 bytes - 60 bytes (payload + data) + 4 bytes FRC*/
    while (1)
    {
	if (*temp == 0)
   	{
	     break;
	}	
        temp++;
	packet_size++;
    }
    packet_size = (packet_size * 8); 
    printf("\npacket_size is %d\n",packet_size);

    return packet_size;

}

void packet_capture(unsigned char *args,const struct pcap_pkthdr *header, const unsigned char *packet)
{
    int packet_size = 0;

    if (true == is_cntp(packet,args)) {
        printf(KMAG "CNTP PACKET RECEIVED \n" RESET);
     	packet_size = calc_packet_size((uint64_t *)packet);  
	packet_print(packet,packet_size);
        cntp_handler(header,packet,args,packet_size);
    } else {
        printf(KMAG "NOT DESTINED TO ME. DROPPING PACKET \n" RESET);
        //packet_print(header,packet);
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

	printf(KMAG "calling pcap_loop\n" RESET);

    pcap_loop(handle,-1,packet_capture,(u_char *)args);

}
