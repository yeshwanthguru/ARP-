#include <stdio.h>
#include <string.h>
#include <unistd.h>
int main()
{
   char HOIST_DIRECTION[5];
   printf("\nEnter the direction Hoist moves:");
    scanf("%s",&HOIST_DIRECTION);
  //  printf("%s",CRANE_DIRECTION);
 if(strcmp(HOIST_DIRECTION, "up") != 0  && strcmp(HOIST_DIRECTION, "down") !=0)
    {
    	printf("\nHi your hoist directon is wrong, Please enter either up or down");
    	main();
    }
    int n1,n2;
    int res = strcmp(HOIST_DIRECTION, "up"); 
    printf("Enter the floor : ");
    scanf("%d",&n1);
    int hoistmax = 200;
    int hoistmin = 0;
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
  //  printf("%s",CRANE_DIRECTION);
    printf("\nEnter the floor : ");
   scanf("%d",&n2);
    if(n2>n1 && n2<=200 && n2>=0){
    //    scanf("%d\n",i);
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
      while (hoistmax <= hoistmin)
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
      while (hoistmax <= hoistmin){
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
  
// return 0;
 main();



}
