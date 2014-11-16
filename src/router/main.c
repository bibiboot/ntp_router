#include "globals.h"
#include "sock_details.h"
#include "packet_sniff.h"
#include "ipc_client.h"


void init()
{
    // interfac1
    strcpy(globals.inf[0].inf_name,INF1);
    globals.inf[0].addr = INFADDR1;
    globals.inf[0].dnode_ip = DNODEIP1;
    globals.inf[0].sock = create_socket(globals.inf[0].inf_name,&(globals.inf[0].sk));

    // interfac2
    strcpy(globals.inf[1].inf_name,INF2);
    globals.inf[1].addr = INFADDR2;
    globals.inf[1].dnode_ip = DNODEIP2;
    globals.inf[1].sock = create_socket(globals.inf[1].inf_name,&(globals.inf[1].sk));
}

void start()
{
    //pthread_create(&(globals.inf[0].thrd),0,&configure_capture,(void*)(&globals.inf[0]));
    //pthread_create(&(globals.inf[1].thrd),0,&configure_capture,(void*)(&globals.inf[1]));
    pthread_create(&(globals.ipc_th) ,0 , start_ipc_client , NULL);

    //pthread_join(globals.inf[0].thrd,NULL);
    //pthread_join(globals.inf[1].thrd,NULL);
    pthread_join(globals.ipc_th, NULL);

}

int main(int argc, char *argv[])
{
    //init();

    start();

    return 0;
}


