#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>
#include<netinet/in.h>
#include <fcntl.h> 
#include <sys/stat.h> 
 

int main()
{
	char server_msg[256];
	strcpy(server_msg, "up");
	int server_socket;
	server_socket=socket(AF_INET, SOCK_STREAM,0);
	struct sockaddr_in server_address;
	server_address.sin_family=AF_INET;
	server_address.sin_port=htons(5000);
	server_address.sin_addr.s_addr=INADDR_ANY;
	bind(server_socket,(struct sockaddr *)&server_address, sizeof(server_address));
	listen(server_socket, 10);
	int client_socket;
	client_socket=accept(server_socket, NULL, NULL);
	printf("enter the input of crane in R:",&server_msg);
        scanf("%s",&server_msg);
       printf("H=hoist moving in the direction %s\n",server_msg);
	send(client_socket, server_msg, sizeof(server_msg),0);
	main();
return 0;
}
