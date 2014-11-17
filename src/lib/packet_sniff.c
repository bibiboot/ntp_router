#include "packet_sniff.h"
#include "packet_print.h"
#include "filter.h"
#include "cntp_handler.h"
#include "my_rawsocket_ts.h"

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

void *packet_capture(void *args)
{
    struct msghdr msg; //add this in globals.h
    struct iovec entry;// add this in globals.h
    struct control control;//add this in globals.h
    char *payload;
    int payload_len = 1024;
    struct sockaddr_in from_addr;
    int ret;
    int s;
    int err_packet;
    int packet_size;
    struct timeval recv_usr;

    struct custom_header *hdr;//similar to AB's custom_packet_header
    struct timestamp recv_kern;
    struct timestamp time_diff;
    struct timestamp *from_packet_kern;
    struct interface *arg;//similar to AB's struct receiver_arg

    arg = (struct interface *)args;

    //arg->inf_index = create_socket(arg->inf_name,&(arg->sk));
    //already created in main.c

    payload = (char *)malloc(payload_len);
    memset(payload,0,payload_len);

    printf(KMAG "Sniffing started\n" RESET);
    s = create_recv_rawsocket_ts(arg->inf_name);
    set_promisc(arg->inf_name,s);
    setup_raw_msghdr(&msg,
                 &entry,
                 &control,
                 payload,
                 payload_len,
                 &from_addr);

    while(1)
    {
        ret = recv_rawpacket_ts(s, &msg, 0, &err_packet, &recv_kern);
        if (ret < 0){
            printf("Error receiving\n");
            exit(1);
        }

        gettimeofday(&recv_usr, 0);

        if (!err_packet) {
            hdr = (struct custom_header*)payload;

            if (true == is_cntp(payload,args)) {
                printf(KMAG "CNTP PACKET RECEIVED \n" RESET);

		if (ret <= 60) {
                    packet_size = calc_packet_size((uint64_t *)payload);
		}
		else {
		    packet_size = ret;
		}

	        packet_print(payload,packet_size);

                printf("packet received: user space ts:%ld.%06ld:received %d bytes\n",
                        (long)recv_usr.tv_sec, (long)recv_usr.tv_usec, ret);
                printf("packet received: kernel space ts:%ld.%06ld:received %d bytes\n",
                       (long)recv_kern.sec, (long)recv_kern.fsec, ret);

                cntp_handler(&recv_kern,payload,args,packet_size);
            }
	    else {
                printf("packet received: user space ts:%ld.%06ld:received %d bytes\n",
                        (long)recv_usr.tv_sec, (long)recv_usr.tv_usec, ret);
	    	printf(KMAG "Ignoring Packet Not CNTP\n" RESET);
	    }
        }


               /* if (IS_DRTT_REQUEST(hdr)) {
                    printf("received drtt request\n");
                    create_drtt_response(hdr, arg->my_addr, CUSTOM_HEADER_SZ + TIMESTAMP_SZ, &recv_kern);
                    printf("processed response\n");
                    //print_drtt_packet((void*)payload);

                    gettimeofday(&recv_usr, 0);
                    printf("sending packet: user space ts:%ld.%06ld\n",
                            (long)recv_usr.tv_sec,
                            (long)recv_usr.tv_usec);
                    //send_packet(arg->send_sfd, &(arg->sk),
                      //          (void*)payload,
                       //         ret);
                    send_packet(arg->send_sfd, &(arg->sk),
                                (void*)payload,
                                CUSTOM_HEADER_SZ + (2 * TIMESTAMP_SZ));
                    printf("response packet sent..\n");
                }

                else if (IS_DRTT_RESPONSE(hdr)){
                    printf("received drtt response: kernel space ts:%ld.%06ld:received %d bytes\n",
                           (long)recv_kern.sec, (long)recv_kern.fsec, ret);
                    ///create_timestamp(&ts);
                    //from_packet = (struct timestamp*)(hdr+1);
                    cal_time_diff(&time_diff, &recv_kern, payload);
                }
            }

            //Regular packet
            //print_drtt_packet((void *)payload);
        }
        else{
            printf("encountered our packet\n");
        }
        //print_rawpacket(&msg, ret, payload, s, 0);*/

    }

}

