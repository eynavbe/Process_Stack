#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include "helpFunc.cpp"
#include "mystack.cpp"
#include <sys/mman.h> 
#include <fcntl.h>

#include <limits.h>
#include <netinet/in.h>

#define PORT 8081
struct flock lock;
int file;
#include <cstring>

#define TXT 1024;

void* HelloWorld(int newAdrsSckt,struct StackNode* root)
{
    memset(&lock, 0, sizeof(lock));
    //Initializes the beginning of the stack
    char client_message[1024];
    //create socket to recive message from the client
    int new_socket = newAdrsSckt;
    //recive a message from the client and put him into "client_message"
    if(recv(new_socket , client_message , 1024 , 0) < 0)
    {
        puts("DEBUG: recv failed");
    }
    
    //while the message is not an exit message
    while(!compareStr(client_message, (char*)"EXIT", 4)){	
        /*
        Before touching the stack we lock the program so that another customer
        does not change the stack at the same time
        */	
       
        lock.l_type = F_WRLCK;
        fcntl(file, F_SETLKW, &lock);
        //Sleep for 5 seconds so we can see the thread action
        sleep(5);
        if(compareStr(client_message, (char*)"PUSH", 4)){
            int j = 0;
            char * wordS = (char*)mymalloc(j*sizeof(char));
            int n=0;
            //Sends to "push" only the text you want to add to the stack without the command. Put the text in "wordS".
            for(size_t i = 5; i<strlen(client_message); i++){
                if (client_message[i] != '\n' && ((int)i)-5 == j)
                {
                    wordS[n++] = client_message[i];
                    j++;
                } 
            }
            push(root, (char*) wordS);
            // printf("pid1: %d\n", fdNum);
        }else if(compareStr(client_message, (char*)"POP", 3)){
            //Sends the command "pop" and prints the element removed from the stack
            printf("%s popped from stack\n", pop(root));
        }else if(compareStr(client_message, (char*)"TOP", 3)){
            //Sends the command "top" to peek function. print the top element.
            char * top_w = peek(root);
            printf("Top element is %s\n",top_w);
            //sent the top element to the client
            send(new_socket, top_w, strlen(top_w), 0);
            printf("%s message sent\n",top_w);
        }else{
            //If no valid command was received: "pop", "top" or "push", send error
            printf("ERROR: ");
            int i = 0;
            while (client_message[i] != ' ' && client_message[i] != '\n')
            {
                printf("%c",client_message[i]);
                i++;
            }
            printf("\n");
        }
        //unlock the program
        lock.l_type = F_UNLCK;
        fcntl(file, F_SETLKW, &lock);

        //receive the message from the client and put him into "client_message"
        if(recv(new_socket , client_message , 1024 , 0) < 0)
        {
            puts("DEBUG: recv failed");
            break;
        }
    }
    return 0;  
}
fd_set read_fd;
int main(int argc, char const* argv[])
{
    printf("in main\n");
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    file = open("./lock.txt",O_RDWR, S_IRUSR | S_IWUSR);
    struct StackNode* root =(StackNode*) mmap(NULL, sizeof(struct StackNode), PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS, -1, 0); 
    root->start = 0;
    //The socket() call creates a socket in the specified domain and of the specified type.
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0))
        == 0) {
        perror("DEBUG: socket failed");
        exit(EXIT_FAILURE);
    }
    printf("set socket address\n");

    //Set socket option.
     if (setsockopt(server_fd, SOL_SOCKET,
                   SO_REUSEADDR | SO_REUSEPORT, &opt,
                   sizeof(opt))) {
        perror("DEBUG: setsockopt");
        exit(EXIT_FAILURE);
    }
    printf("after setsockopt\n");


    //Provide needed information about destination.
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    printf("after init address\n");

    // printf("%d\n" , bind(server_fd, (struct sockaddr*)&address,
    //          sizeof(address)));

    //associates an address with the socket descriptor.
    if (bind(server_fd, (struct sockaddr*)&address,
             sizeof(address))
        < 0) {
        perror("DEBUG: bind failed");
        exit(EXIT_FAILURE);
    }
    printf("after bind\n");

    // prepares a connection-oriented server to accept client connections.
    if (listen(server_fd, 3) < 0) {
        perror("DEBUG: listen");
        exit(EXIT_FAILURE);
    }
    printf("after listen\n");
    FD_ZERO(&read_fd);

    int fd = getpid();
    printf("pid: %d\n", fd);
    

    while(1){

        FD_SET(server_fd,&read_fd);
        printf("in while\n");
        //accept the connection of the new client
        new_socket = accept(server_fd, (struct sockaddr*)&address,
                (socklen_t*)&addrlen);
         printf("after accept\n");
        if (new_socket == -1) {
                perror("accept");
                exit(EXIT_FAILURE);
        }
        printf("after init new socket after accept\n");
        if (!fork()) { // this is the child process

            close(server_fd); // child doesn't need the listener
            printf("before send\n");
            sleep(5);
            HelloWorld(new_socket,root);
            exit(0);
        }
    }

    return 0;
}