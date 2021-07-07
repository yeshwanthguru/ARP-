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
		perror(" input arguments in R, syntax should be:\n./R (message_number)\n (G1R_read)\n (G2R_read)\n (RM_write) \n(timeout)\n");
		outputlogFile(" input arguments in R");
		return -1;
	}
	int n = atoi(arr2[1]);
        int GR_RDONLY = atoi(arr2[2]);
	int RM_WRONLY = atoi(arr2[3]);	
        struct msgG buf;
        struct msgR* msg = (struct msgR*) valloc(2 * n * sizeof(struct msgR));
	struct timeval t;
	char * myfifo = "/tmp/myfifo";
	GR_RDONLY = open(myfifo, O_RDONLY);
	if (GR_RDONLY == 0)
	{
		perror("Cannot====== open fifo");
		outputlogFile("Cannot ===== open fifo");
		unlink(myfifo);
		exit(1);
	}
	int nfds;
	nfds = GR_RDONLY + 1;
        fd_set rfds;
	struct timeval timeout;
	timeout.tv_sec = 0;
	timeout.tv_usec = atoi(arr2[4]);
	int retval;
	int i = 0;
	printf("R ready-------> receive messages\n");
	outputlogFile("R ready------> receive messages");
        while (i < 2 * n)
	{
		FD_ZERO(&rfds);
		FD_SET(GR_RDONLY, &rfds);
		retval = select(nfds, &rfds, NULL, NULL, &timeout);
        	if (retval == -1)
		{
			perror("select() error in R");
			outputlogFile("select() error in R");
		}
       	else if (retval)
		{
			if(read(GR_RDONLY, &buf, sizeof(struct msgG)) < 0)
			{
				perror("Error during G =/= R communication");
				outputlogFile("Error during G =/= R communication");
				exit(-3);
			}
			gettimeofday(&t, NULL);
			msg[i].timestamp = buf.timestamp;
			msg[i].g = buf.g;
			msg[i].x = buf.x;
			msg[i].receivetime = t;
			i++;
		}
	}
        printf("R----------> received all messages,----------> sending them to M\n");
	outputlogFile("R ------------->received all messages,----------> sending them to M");
        for (int i = 0; i < 2 * n; i++)      
	{
		if(write(RM_WRONLY, &msg[i], sizeof(struct msgR)) < 0)
		{
			perror("Error in R =/= M communication");
			outputlogFile("Error in R =/= M communication");
			exit(-3);
		}
	}
        printf("R has sent all messages\n");
	outputlogFile("R has sent all messages");
        printf("R terminate...\n");
	outputlogFile("R terminate...");
	free(msg); 
	close(GR_RDONLY);
        close(RM_WRONLY);
	unlink(myfifo);
	return 0;
}
