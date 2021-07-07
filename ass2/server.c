#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>
#include<netinet/in.h>
 
 int main()
 {
 	int network_socket; 
 	network_socket=socket(AF_INET,SOCK_STREAM,0);
 	struct sockaddr_in server_address;
 	server_address.sin_family = AF_INET;
 	server_address.sin_port=htons(5000);
 	server_address.sin_addr.s_addr=INADDR_ANY;
        int connection_status=connect(network_socket,(struct sockaddr *)&server_address, sizeof(server_address));
 	if(connection_status==-1)
 	{
        printf("The remote socket is in error state\n");
 	}
 	char server_response[256],HOIST_DIRECTION[256],i;
 	recv(network_socket, &server_response, sizeof(server_response),0);
      printf("Crane moving ===================%s\n==============>"server_response);
    fgets(server_response, sizeof(server_response), stdin);

    for (i = 0; server_response[i] != '\0'; ++i) {
        HOIST_DIRECTION[i] = server_response[i];
    }

    HOIST_DIRECTION[i] = '\0';
    printf("\nEnter the direction Hoist moves",&HOIST_DIRECTION);
    scanf("%s",&HOIST_DIRECTION);
 if(strcmp(HOIST_DIRECTION, "up") != 0  && strcmp(HOIST_DIRECTION, "down") !=0)
    {
    	printf("\nHi your hoist directon is wrong, Please enter either up or down");
    	main();
    }
    int n1,n2;
    int res = strcmp(HOIST_DIRECTION, "up"); 
    printf("Enter the floor : ");
    scanf("%d",&n1);
    int max = 200;
    int min = 0;
    
    
    int hoist_current_postion = 0;
    int i=0;
    if(n1>=0 && n1<=200){
        printf("hoist is moving upward\n");
        while (i <= n1)
        {
            if(i%5==0){
                printf("hoist moves |u|p|%d|u|p|\n", i);
                hoist_current_postion = i;
            }
            i++;
        }    
    } else {
        printf("Invalid floor level\n");
    }
    
    printf("Hoist current postion : %d\n",hoist_current_postion);
    printf("=========Hoist reached the Destination upwards=======");
     printf("\nEnter the direction Hoist moves:");
    scanf("%s",&HOIST_DIRECTION);
    printf("\nEnter the floor : ");
   scanf("%d",&n2);
    if(n2>n1 && n2<=200 && n2>=0){
        printf("Hoist is moving upward\n");
        while (i <= n2 )
        {
            if(i%5==0){
                printf("Hoist moves |u|p|%d|u|p|\n", i);
               hoist_current_postion = i;
            }
            i++;
        }    
    } else  
            {
      while (max <= min)
    		    {
			printf("%d\n",i-=5);
      scanf("%d\n",i);
        		 }	
    int res1 = strcmp(HOIST_DIRECTION, "down");
    if(n2<n1 && n2<=200 && n2>=0){
    printf("\nEnter the direction hoist moves:");
    scanf("%s",&HOIST_DIRECTION);

    
        printf("hoist is moving downward\n");
        while (i >= n2)
        {
            if(i%5==0){
                printf("Hoist moves |d|o|w|n|%d|d|o|w|n|\n",i);
                hoist_current_postion = i;
            }
            i--;
        }   
    } else
       {
      while (max <= min){
      int res1 = strcmp(HOIST_DIRECTION, "down");
      scanf("%d\n",i);
    		    {
			printf("%d\n",i-=5);
      scanf("%d\n",i);
       main(); 		
      
    		   }
      }
    
       }
    
    printf("Crane current postion : %d\n",hoist_current_postion);
     
    
    }
 main();



}

