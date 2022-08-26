/**
 * MA-Memphis
 * @file main.c
 *
 * @author Angelo Elias Dal Zotto (angelo.dalzotto@edu.pucrs.br)
 * GAPH - Hardware Design Support Group (https://corfu.pucrs.br/)
 * PUCRS - Pontifical Catholic University of Rio Grande do Sul (http://pucrs.br/)
 * 
 * @date March 2021
 * 
 * @brief Main file of the MA-Memphis mapper
 */

#include <memphis.h>
#include <memphis/services.h>

int main()
{
	const size_t MSG_FLITS = 128;
	const size_t MSG_BYTES = MSG_FLITS << 2;

	printf("Mapper task started at time %u\n", memphis_get_tick());

	static map_t mapper;
	map_init(&mapper);

	while(true){
		static int message[MSG_FLITS];
		memphis_receive_any(message, MSG_BYTES);

		switch(message[0]){
			case NEW_APP:
				map_new_app(&mapper, message[1], &message[2], &message[(message[1] << 1) + 2]);
				break;
			default:
				break;
		}
	}

	return 0;
}
