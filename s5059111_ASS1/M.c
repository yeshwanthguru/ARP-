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
	if (arr2 != 4)
  {
		perror(" input arguments in M, syntax should be:\n./M (msg_num) (msg_delay) (RM_read\n");
		outputlogFile(" input arguments in M");
		return -1;
	}
	int n = atoi(arr2[1]);
	int offset = atoi(arr2[2]);
	int RM_RDONLY = atoi(arr2[3]);
	struct msgR* msg = (struct msgR*) valloc(2 * n * sizeof(struct msgR));
        int i = 0; 
	long int av_delay = 0; 
	fd_set rfds;
	int nfds = RM_RDONLY + 1;
	struct timeval timeout;
	timeout.tv_sec = 0;
	timeout.tv_usec = 5;
	int retval;
        printf("M -------> ready to receive messages\n");
	outputlogFile("M -------> ready to receive messages");
        while (i < 2 * n)
	{
		FD_ZERO(&rfds);
		FD_SET(RM_RDONLY, &rfds);
		retval = select(nfds, &rfds, NULL, NULL, &timeout);
		if (retval == -1)
		{
			perror("select() error in M");
			outputlogFile("select() error in M");
		}
		else if (retval)
		{
			if(read(RM_RDONLY, &msg[i], sizeof(struct msgR)) < 0)
			{
				perror("Error during R =/= M communication");
				outputlogFile("Error during R =/= M communication");
				exit(-3);
			}
			if (msg[i].receivetime.tv_usec > msg[i].timestamp.tv_usec)
				av_delay += msg[i].receivetime.tv_usec - msg[i].timestamp.tv_usec;
			else
				av_delay += msg[i].receivetime.tv_usec - msg[i].timestamp.tv_usec + 1000000;
			i++;
		}
	}
        printf("M received all messages\n");
	outputlogFile("M received all messages");
	
	av_delay /= 2 * n; //divide the sum of delays by the number of messages
	double beginningtime = (double)msg[0].timestamp.tv_sec + (double)msg[0].timestamp.tv_usec / 1000000;
	double endingtime = (double)msg[2 * n - 1].receivetime.tv_sec + (double)msg[2 * n - 1].receivetime.tv_usec / 1000000;
	double overalltime = endingtime - beginningtime;
        printf("\n");
	printf("number of G1|G2 cycles: %d\n", n);
	printf("number of messages received: %d\n", 2 * n);
	printf("offset delay in G1 | G2 cycles (usec): %d\n", offset);
	printf(" delay (latency) between generation and reception of messages (nsec): %ld\n", av_delay = 2 * n);
	printf("estimated bandwidth between G and R (bit/s): %lf\n", (double)(2 * 8 * n * sizeof(struct msgG)) / overalltime);
	printf("\n");
	printf("communication began at %lf\n", beginningtime);
	printf("communication ended at %lf\n", endingtime);
	printf("overall communication time %lf s\n", overalltime);
	printf("passed %ld bytes, which is equal to %ld bits\n", 2 * n * sizeof(struct msgG), 2 * 16 * n * sizeof(struct msgG));
	printf("\n");
        printf("M terminate...\n");
	outputlogFile("M terminate...");
	free(msg);
	close(RM_RDONLY);
	return 0;
}
