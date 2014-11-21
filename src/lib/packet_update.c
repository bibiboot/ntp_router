#include "packet_update.h"

void packet_update(unsigned char  *newpacket,
                   struct timestamp *recv_kern, uint16_t next_hop,
                   int packet_len)
{
    struct custom_packet_header *hdr = (struct custom_packet_header *)newpacket;
    unsigned char *new_payload = newpacket + packet_len;

    hdr->next_hop_addr = htons(next_hop);

    memcpy(new_payload, &(recv_kern->sec), 4);
    memcpy(new_payload + 4, &(recv_kern->fsec), 4);

    struct timestamp *drtt_st = (struct timestamp *)(new_payload + 8);
    drtt_st->sec = 0;
    drtt_st->fsec = atoi(globals.drtt);
}
