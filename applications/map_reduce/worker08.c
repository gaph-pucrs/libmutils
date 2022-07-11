#include <memphis.h>
#include <stdlib.h>
#include <stdio.h>
#include "map_reduce_std.h"

message_t msg;
message_t msg1;

int main()
{
    unsigned int sum_cum = 0;

    printf("Worker%d\n", memphis_get_id()-255-1);

    memphis_receive(&msg, master);

    printf("Recebeu\n");
	
    sum_cum += sum(msg.payload, msg.length);

    memphis_receive(&msg1, worker09);
        sum_cum += sum(msg1.payload, msg.length);
    memphis_receive(&msg1, worker10);
    sum_cum += sum(msg1.payload, msg.length);
    memphis_receive(&msg1, worker12);
    sum_cum += sum(msg1.payload, msg.length);

    msg1.payload[0]=sum_cum;
    msg1.length = 1;
    memphis_send(&msg1, master);
    
    printf("Enviou\n");

    return 0;
}