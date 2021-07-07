#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <fcntl.h>
#include <string.h>
#include <time.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/select.h>
#include "structmsgG.h"
#include "structmsgR.h"
int main(int arr1, char* arr2[])
{
	if (arr2 != 5)
  {
		perror("  input arguments in G,  should be:\n./G (messsage_num)\n (message_offset)\n G1R_write \n(1 or 2)\n");
		perror("  input arguments in G");
		return -1;
	}
	int n = atoi(arr2[1]);
	int offset = atoi(arr2[2]);
	int GR_WRONLY = atoi(arr2[3]);	
        char Gnum = arr2[4][0];
	struct timeval t;
	struct msgG msg;
	msg.g = Gnum;
        if (Gnum == '1')
	{
		printf("G1 ----> send messages\n");
		outputlogFile("G1 -----> send messages");
	}
	else
	{
		printf("G2 ----->send messages\n");
		outputlogFile("G2 -----> send messages");
	}
      for (int i = 0; i < n; i++)
	{
		gettimeofday(&t, NULL);
		msg.timestamp = t;
		msg.x = i + 1;
               usleep(offset + offset * rand() / RAND_MAX);
               if(write(GR_WRONLY, &msg, sizeof(struct msgG)) < 0)
		{
			perror("Error in G =/= R communication");
			outputlogFile("Error in G =/= R communication");
			exit(-3);
			}
	}
        if (Gnum == '1')
	{
		printf("G1 terminate...\n");
		outputlogFile("G1 terminate...");
	}
	else
	{
		printf("G2 terminate...\n");
		outputlogFile("G2 terminate...");
	}
	close(GR_WRONLY);
	return 0;
}
