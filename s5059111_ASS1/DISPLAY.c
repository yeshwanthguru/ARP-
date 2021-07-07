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
 int res;         
 int pipe_RM[2];  
 int outputlogfile;   
  pid_t process[4];
  char message_number[32];
  char message_delay[32];
  char timeout[32];
  printf("Enter the number of messages: ");
  scanf("%s", message_number);
  printf("Enter the messages offset (usec): ");
  scanf("%s", message_delay);
  printf("Enter the select timeout value (usec): ");
  scanf("%s", timeout);
  FILE *f;
  f = fopen("./outputlogfile.txt", "w");
  if (f == NULL)
  {
    perror("Error opening the outputlog file\n");
    exit(EXIT_FAILURE);
  }
  fclose(f);
  outputlogFile("outputlog file created");
  if(pipe(pipe_RM) < 0)
  {
    perror("Error opening pipe between R =/= M");
    outputlogFile("Error opening pipe between R =/= M");
		return -2;
	}
  outputlogFile("R == M pipe created");
  char * myfifo = "/tmp/myfifo";
  if (mkfifo(myfifo, S_IRUSR | S_IWUSR) != 0)
  {
    perror("Error opening pipe between G =/= R");
    outputlogFile("Error opening pipe between G =/= R");
  }
  int pipe_GR = open(myfifo, O_RDWR);
  if (pipe_GR == 0)
  {
    perror("Cannot open fifo");
    outputlogFile("Cannot open fifo");
    unlink(myfifo);
    exit(1);
  }
  outputlogFile("G == R pipe created");
	if ((process[0] = fork()) < 0)
  {
    perror("Error in creating M");
    outputlogFile("Error in creating M");
		return -1;
	}
  if (process[0] == 0)
  {
    close(pipe_RM[1]);  
    char RM_RDONLY[32];   
    sprintf(RM_RDONLY, "%d", pipe_RM[0]);
    char* arr3[] = {"./M", message_number, message_delay, RM_RDONLY, NULL};
		execvp(arr3[0], arr3);
  }
  printf("M process----------created---------> by Master,PID: %d\n", process[0]);
  outputlogFile("M process ------- created-------> by Master");
	if ((process[1] = fork()) < 0)
  {
    perror("Error creating R");
    outputlogFile("Error creating R");
		return -1;
	}
  if (process[1] == 0)
  {
    close(pipe_RM[0]); 
    char GR_RDONLY[32];   
    char RM_WRONLY[32];  
    sprintf(GR_RDONLY, "%d", pipe_GR);
    sprintf(RM_WRONLY, "%d", pipe_RM[1]);

    char* arr3[] = {"./R", message_number, GR_RDONLY, RM_WRONLY, timeout, NULL};
		execvp(arr3[0], arr3);
  }

  printf("R process------- created-------> by Master,PID: %d\n", process[1]);
  outputlogFile("R process-------- created------> by Master");
  close(pipe_RM[0]);  
  close(pipe_RM[1]);
	if ((process[2] = fork()) < 0)
  {
		perror("Error creating G1");
    outputlogFile("Error creating G1");
		return -1;
	}
  if (process[2] == 0)
  {
    char GR_WRONLY[32];
    sprintf(GR_WRONLY, "%d", pipe_GR);

    char* arr3[] = {"./G", message_number, message_delay, GR_WRONLY, "1", NULL};
		execvp(arr3[0], arr3);
  }
  printf("G1 process------ created------> by Master,  PID: %d\n", process[2]);
  outputlogFile("G1 process----- created------> by Master");
	if ((process[3] = fork()) < 0)
  {
		perror("Error creating G2");
    outputlogFile("Error creating G2");
		return -1;
	}
  if (process[3] == 0)
  {
    char GR_WRONLY[32];  
    sprintf(GR_WRONLY, "%d", pipe_GR);
    char* arr3[] = {"./G", message_number, message_delay, GR_WRONLY, "2", NULL};
		execvp(arr3[0], arr3);
    return 0;
  }
  printf("G2 process ------ created----> by Master, PID: %d\n", process[3]);
  outputlogFile("G2 process------ created----> by Master");
  close(pipe_GR); 
 for (int i = 0; i < 4; i++)
  {
    waitpid(process[i], &res, 0);
    if (!WIFEXITED(res))
  		perror("Process terminate with an error.\n");
		printf("Process %d exited with value %d\n",process[i], WEXITSTATUS(res));
  }
  outputlogFile("All the processes terminate");
  unlink(myfifo);
  return 0;
}
void outputlogFile(char* msg)
{
  FILE *f;
  f = fopen("./outputlogfile.txt", "a");
  if (f == NULL)
  {
    perror("Error opening log file\n");
    exit(EXIT_FAILURE);
  }
  time_t currentTime = time(NULL);
  char *timeStr = ctime(&currentTime);
  fprintf(f, "%s --- %s ---\n", timeStr, msg);
  fclose(f);
}
