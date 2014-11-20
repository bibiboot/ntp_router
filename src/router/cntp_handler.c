#include "cntp_handler.h"
#include "packet_routing.h"

void cntp_handler(struct timestamp* recv_kern,
                  unsigned char *packet,
                  void* args, int packet_len)
{
    unsigned long kernel_recv_time = (unsigned long)recv_kern->sec * SECONDS + recv_kern->fsec * NANOSECONDS;
    printf("[Kernel][ %lu ] : Recieved DRTT request\n", kernel_recv_time);

    unsigned char *newpacket = malloc(packet_len + 2*TIMESTAMP_LEN);

    if (newpacket == NULL) {
        printf(KMAG "Error:malloc()\n" RESET);
        exit(1);
    }

    struct fwd_info fwd_info;
    memset(&fwd_info, 0, sizeof(struct fwd_info));

    get_fwding_info(packet, &fwd_info,args);

    memcpy(newpacket, packet, packet_len);

    packet_update(newpacket, recv_kern, fwd_info.next_hop, packet_len);

    packet_forward(newpacket, packet_len + 2*TIMESTAMP_LEN, args);
}
