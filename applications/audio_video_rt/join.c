#include <memphis.h>
#include <stdlib.h>
#include <stdio.h>
#include "audio_video_def.h"

int main()
{
	static int message[64];

	puts("Join start...");
	printf("Number of frames: %d\n", FRAMES);

	// memphis_real_time(AUDIO_VIDEO_PERIOD, JOIN_deadline, JOIN_exe_time);

	for(int k = 0; k < FRAMES; k++)
	{	
		memphis_receive(message, sizeof(message), FIR);

		memphis_receive(message, sizeof(message), idct);
	}

	puts("Join finished.\n");

	return 0;
}
