#include "cprotocol.h"
#include "packet_print.h"

void reverse_kernel_timestamp(unsigned char *payload, int offset)
{
    unsigned char *timestamp_payload = payload + offset;

    int i;
    for(i=0; i<4; i++) {
        char temp = timestamp_payload[i];
        timestamp_payload[i] = timestamp_payload[7-i];
        timestamp_payload[7-i] = temp;
    }
}

void packet_print(unsigned char *packet, int packet_len)
{
    printf(KMAG "SNIFF: " RESET);
    printf("Total [%d]: Header size [%d]: Payload [%d]: \n",
           packet_len, C_HLEN, packet_len - C_HLEN);

    struct custom_packet_header *hdr = (struct custom_packet_header *)packet;
    printf("++++++++++++++++++++++++++++++++++++++\n");
    printf("| NEXT_HOP | SRC_IP | DEST_IP | PORT |\n");
    printf("++++++++++++++++++++++++++++++++++++++\n");
    printf("| %8d | %6d | %7d | %4d |\n",ntohs(hdr->next_hop_addr),
                                       ntohs(hdr->src_addr),
                                       ntohs(hdr->dst_addr),
                                       ntohs(hdr->dst_port));
    printf("++++++++++++++++++++++++++++++++++++++\n");

    /*
     * First timestamp will be kernel timestamp
     * Second timestamp will be SO_TIMESTAMP.
     *
     * Hence alternatively the timestamp
     * But this has a bug as the drtt is just
     * a number and do not need to be converted.
     */
    /*
    unsigned char *payload = packet + C_HLEN;
    int payload_len = packet_len - C_HLEN;

    while (payload_len) {
        payload_len -= TIMESTAMP_LEN;
    }*/

    /* Reverse Remote transmission timestamp */
    reverse_kernel_timestamp(packet, C_HLEN);

    struct timestamp *local_tx  = (struct timestamp *)(packet + C_HLEN);
    struct timestamp *remote_rx = (struct timestamp *)(packet + C_HLEN + TIMESTAMP_LEN);

    unsigned long local_xmit_time   = (unsigned long)EXTRACT_64BITS(local_tx);
    unsigned long remote_recv_time  = (unsigned long)remote_rx->sec * SECONDS + remote_rx->fsec * NANOSECONDS;
    struct timestamp *drtt_st       = (struct timestamp *)(packet + C_HLEN + 2*TIMESTAMP_LEN);

    printf("Local transmit timestamp   : %lu\n", local_xmit_time);
    printf("Remote receieve timestamp  : %lu\n", remote_recv_time);
    printf("Roundtrip delay            : %ld\n" , drtt_st->fsec);
}
