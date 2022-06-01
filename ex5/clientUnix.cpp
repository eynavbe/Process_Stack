#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include "helpFunc.cpp"
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/un.h>
#define PORT 8081
 #define SERVER_PATH "tpf_unix_sock.server"
#define CLIENT_PATH "tpf_unix_sock.client"
int main(int argc, char const* argv[])
{
    //init socket number
    int sock = 0;
        struct sockaddr_un server_sockaddr;
 struct sockaddr_un client_sockaddr; 
    memset(&client_sockaddr, 0, sizeof(struct sockaddr_un));
    //will save our address
    struct sockaddr_in serv_addr;
    char buffer[1024] = { 0 };
    //The socket() call creates a socket in the specified domain and of the specified type.
    if ((sock = socket(AF_UNIX, SOCK_STREAM, 0)) < 0) {
        printf("\nDEBUG: Socket creation error \n");
        return -1;
    }
    //Provide needed information about destination.
    // serv_addr.sin_family = AF_UNIX;
     client_sockaddr.sun_family = AF_UNIX;   
    strcpy(client_sockaddr.sun_path, CLIENT_PATH); 
    
    unlink(CLIENT_PATH);
    int rc = bind(sock, (struct sockaddr *) &client_sockaddr, sizeof(client_sockaddr));
    if (rc == -1){
        printf("BIND ERROR \n");
        close(sock);
        return -1;
    }
        
    server_sockaddr.sun_family  = AF_UNIX;
    strcpy(server_sockaddr.sun_path, SERVER_PATH);
     rc = connect(sock, (struct sockaddr *) &server_sockaddr, sizeof(client_sockaddr));
    if(rc == -1){
        printf("CONNECT ERROR \n");
        close(sock);
        exit(1);
    }
    // serv_addr.sin_port = htons(PORT);
 
    //convert IPv4 and IPv6 addresses from text to binary form
    // if (inet_pton(AF_UNIX, "127.0.0.1", &serv_addr.sin_addr)
    //     <= 0) {
    //     printf(
    //         "\nDEBUG: Invalid address/ Address not supported \n");
    //     return -1;
    // }
    // //establishes a connection to the server.
    // if (connect(sock, (struct sockaddr*)&serv_addr,
    //             sizeof(serv_addr))
    //     < 0) {
    //     printf("\nDEBUG: Connection Failed \n");
    //     return -1;
    // }


char promp[1024];
  int f = 1;
  int i = 0;
  printf("Write down the command, type 'EXIT' to exit:\n");
  //Receives command from the user
  while(f){
      scanf("%c", &promp[i]);
      //If the user has finished the command stop receiving from the user
      if(promp[i] == '\n'){
          f= 0;
      }
      else{
          i++;
      }  
  }

// If the EXIT command is received - exit what shell you are writing.
  char* exit = (char*)"EXIT";
  //while the user does not click "exit" to exit the program he continue to receive commands
  while (!compareStr(promp, exit, 4))
  {
    f = 1;
    i = 0;
    //send the command to the server
    send(sock, promp, strlen(promp), 0);
    //If the command is top: Expect an answer from the server and print it
    if (compareStr(promp, (char*)"TOP", 3))
    {
      read(sock, buffer, 1024);
      printf("OUTPUT: %s\n", buffer);
    }
    //init the promp
    bzero(promp, sizeof(promp));
    //
    printf("Write down the command, type 'EXIT' to exit:\n");
    //Receives input from the user
    while(f){
      scanf("%c", &promp[i]);
      if(promp[i] == '\n'){
        f= 0;
      }
      else{
        i++;
      }  
    }
  }
  //If the "Exit" command is received, the program exits and tells the server
  send(sock, (char*)"EXIT", 4, 0);
  return 0;
}