#include "arpnet.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdbool.h>
#include <signal.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
char my_ip[] = "127.0.0.1";
struct timeval timeout;
timeout.tv_sec = 10;
timeout.tv_usec = 0;
int turnLeader_FLAG = 0;
int turnLeader = 0;
int main(){
int my_id = iptab_get_ID_of(my_ip);
int r_hsh, w_hsh, r_vot, w_vot, r_nor, w_nor;
int sock_fd, newsock_fd, send_sock_fd, check1
char next_ip[20];
votation_t vote_msg;
node_id winner_id;
message_t norm_msg;
int znode = hsh_imfirst(my_ip);
if(znode == 1){
		turnLeader_FLAG = 1;
	}
if(znode==0){
handshake_t hsh_msg;
hsh_init(&hsh_msg);
sock_fd = net_server_init();
newsock_fd = net_accept_client_timeout(sockfd, &timeout, NULL);
if(newsock_fd<0){
printf("Error in accepting the  client\n");
return 0;
}
r_hsh = read(newsockfd, &hsh_msg, sizeof(handshake_t));
if(r_hsh<0){
printf("Error in reading from the socket\n");
return 0;
}
check1 = hsh_check_availability(my_id, &hsh_msg );
next_ip = iptab_getaddr(my_id + 1);
send_sock_fd = net_client_connection_timeout(next_ip, &timeout);
if(send_sock_fd <0){
printf("Error in connecting to the  server\n");
return 0;
}
w_hsh = write(send_sock_fd, &hsh_msg, sizeof(handshake_t));
if(w_hsh<0){
printf("Error in writing to the  socket\n");
return 0;
}
close(sock_fd);
close(newsock_fd);
close(send_sock_fd);
if(check1 ==0){
printf("version is incorrect state\n");
return 0;
}
sock_fd = net_server_init();
newsock_fd = net_accept_client_timeout(sockfd, &timeout, NULL);
if(newsock_fd<0){
printf("Error in accepting the  client\n");
return 0;
}
r_hsh = read(newsockfd, &hsh_msg, sizeof(handshake_t));
if(r_hsh<0){
printf("Error in reading from the  socket\n");
return 0;
}
hsh_update_iptab( &hsm )
next_id = iptab_get_next( my_id );
next_ip = iptab_getaddr(next_id);
send_sock_fd = net_client_connection_timeout(next_ip, &timeout);
if(send_sock_fd <0){
printf("Error in connecting to the server\n");
return 0;
}
w_hsh = write(send_sock_fd, &hsh_msg, sizeof(handshake_t));
if(w_hsh<0){
printf("Error in writing to the socket\n");
return 0;
}
close(sock_fd);
close(newsock_fd);
close(send_sock_fd);
}
for(int i=0; i<10; i++){
vote_init(&vote_msg);
if(turnLeader_FLAG == 1){
turnLeader_FLAG = 0;
vote_do_votation(&vote_msg);
next_id = iptab_get_next( my_id );
next_ip = iptab_getaddr(next_id);
send_sock_fd = net_client_connection_timeout(next_ip, &timeout);
if(send_sock_fd <0){
printf("Votation: Error in connecting to the server\n");
return 0;
}
w_vot = write(send_sock_fd, &vote_msg, sizeof(votation_t));
if(w_vot<0){
printf("Votation: Error in writing to the socket\n");
return 0;
}
sock_fd = net_server_init();
newsock_fd = net_accept_client_timeout(sockfd, &timeout, NULL);
if(newsock_fd<0){
printf("Votation: Error in accepting the client\n");
 return 0;
 }
 r_vot = read(newsockfd, &vote_msg, sizeof(votation_t));
 if(r_vot<0){
 printf("Error in reading from the socket\n");
  return 0;
	    }
close(sock_fd);
close(newsock_fd);
close(send_sock_fd);
winner_id = vote_getWinner( &vote_msg );
if(winner_id != my_id){
msg_init(&norm_msg);
msg_set_ids( &norm_msg, my_id , winner_id );
next_ip = iptab_getaddr(winner_id);
send_sock_fd = net_client_connection_timeout(next_ip, &timeout);
if(send_sock_fd <0){
printf("Votation: Error in connecting to the server\n");
return 0;
}
w_vot = write(send_sock_fd, &norm_msg, sizeof(message_t));
if(w_vot<0){
printf("Votation: Error in writing to the socket\n");
return 0;
 }
close(send_sock_fd);
}
else{
turnLeader_FLAG = 1;
turnLeader = winner_id;
}
}
else{
sock_fd = net_server_init();
newsock_fd = net_accept_client_timeout(sockfd, &timeout, NULL);
if(newsock_fd<0){
printf("Votation: Error in accepting client\n");
return 0;
 }
r_vot = read(newsockfd, &vote_msg, sizeof(votation_t));
if(r_vot<0){
printf("Error in reading from the socket\n");
return 0;
}
vote_do_votation(&vote_msg);
next_id = iptab_get_next( my_id );
next_ip = iptab_getaddr(next_id);
send_sock_fd = net_client_connection_timeout(next_ip, &timeout);
if(send_sock_fd <0){
printf("Votation: Error in connecting to the server\n");
return 0;
}
w_vot = write(send_sock_fd, &vote_msg, sizeof(votation_t));
if(w_vot<0){
printf("Votation: Error in writing to the socket\n");
return 0;
}
close(sock_fd);
close(newsock_fd);
close(send_sock_fd);
}
if(turnLeader_FLAG ==0){
msg_init(&norm_msg);
sock_fd = net_server_init();
newsock_fd = net_accept_client_timeout(sockfd, &timeout, NULL);
if(newsock_fd<0){
printf("Checking: Error in accepting the  client\n");
return 0;
}
r_nor = read(newsockfd, &norm_msg, sizeof(message_t));
if(r_nor<0){
printf("Checking: Error in reading from the  socket\n");
return 0;
}
turnLeader = msg_get_turnLeader(&norm_msg );
close(sock_fd);
close(newsock_fd);
}
if(my_id == turnLeader){
turnLeader_FLAG = 1;
for(int j=0; j<10; j++){
}
}
else{
msg_set_recv(&norm_msg);
msg_mark(&norm_msg, my_id);
if(msg_all_visited(&norm_msg)){
msg_set_ids(&norm_msg, my_id, turnLeader);
msg_set_sent(&norm_msg);
next_ip = iptab_getaddr(turnLeader);
send_sock_fd = net_client_connection_timeout(next_ip, &timeout);
if(send_sock_fd <0){
printf("Error in connecting to the server\n");
return 0;
}
w_nor = write(send_sock_fd, &norm_msg, sizeof(message_t));
if(w_nor<0){
printf("Error in writing to socket\n");
return 0;
}
close(send_sock_fd);
}
else{
next_id = msg_rand(&norm_msg);
msg_set_ids(&norm_msg, my_id, turnLeader);
msg_set_sent(&norm_msg);
next_ip = iptab_getaddr(next_id);
send_sock_fd = net_client_connection_timeout(next_ip, &timeout);
if(send_sock_fd <0){
printf("Error in connecting to the server\n");
return 0;
}
w_nor = write(send_sock_fd, &norm_msg, sizeof(message_t));
if(w_nor<0){
printf("Error in writing to the socket\n");
return 0;
}
close(send_sock_fd);
next_ip = iptab_getaddr(turnLeader);
send_sock_fd = net_client_connection_timeout(next_ip, &timeout);
if(send_sock_fd <0){
printf("Error in connecting to the  server\n");
return 0;
}
w_nor = write(send_sock_fd, &norm_msg, sizeof(message_t));
if(w_nor<0){
printf("Error in writing tothe socket\n");
return 0;
}
close(send_sock_fd);
}
for(int k=0; k<9; k++){
msg_init(&norm_msg);
sock_fd = net_server_init();
newsock_fd = net_accept_client_timeout(sockfd, &timeout, NULL);
if(newsock_fd<0){
printf("Checking: Error in accepting the client\n");
return 0;
}
r_nor = read(newsockfd, &norm_msg, sizeof(message_t));
if(r_nor<0){
printf("Checking: Error in reading from the socket\n");
return 0;
}
close(sock_fd);
close(newsock_fd);
msg_set_recv(&norm_msg);
msg_mark(&norm_msg, my_id);
if(msg_all_visited(&norm_msg)){
 msg_set_ids(&norm_msg, my_id, turnLeader);
msg_set_sent(&norm_msg);
next_ip = iptab_getaddr(turnLeader);
send_sock_fd = net_client_connection_timeout(next_ip, &timeout);
if(send_sock_fd <0){
printf("Error in connecting tothe server\n");
return 0;
}
w_nor = write(send_sock_fd, &norm_msg, sizeof(message_t));
if(w_nor<0){
printf("Error in writing to the socket\n");
return 0;
}
close(send_sock_fd);
}
else{
next_id = msg_rand(&norm_msg);
msg_set_ids(&norm_msg, my_id, turnLeader);
msg_set_sent(&norm_msg);
next_ip = iptab_getaddr(next_id);
send_sock_fd = net_client_connection_timeout(next_ip, &timeout);
if(send_sock_fd <0){
printf("Error in connecting to the server\n");
return 0;
}
w_nor = write(send_sock_fd, &norm_msg, sizeof(message_t));
if(w_nor<0){
printf("Error in writing to the  socket\n");
return 0;
}
close(send_sock_fd);
next_ip = iptab_getaddr(turnLeader);
send_sock_fd = net_client_connection_timeout(next_ip, &timeout);
if(send_sock_fd <0){
printf("Error in connecting to the server\n");
return 0;
}
w_nor = write(send_sock_fd, &norm_msg, sizeof(message_t));
if(w_nor<0){
printf("Error in writing to the socket\n");
return 0;
}
close(send_sock_fd);
}		
	}
	}
}
	return 0;
}
