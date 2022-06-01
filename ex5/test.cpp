#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <cstring>
#include "mystack.cpp"
#include "helpFunc.cpp"

pthread_t thread_s;
pthread_t thread_c;

int test_stack(){

    struct StackNode* root =(StackNode*) mmap(NULL, sizeof(struct StackNode), PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS, -1, 0); 
    root->start = 0;

    char word1[]="Hello World1";
    char word2[] = "Hello World2";
    //nothing on top
    char * top_w = peek(root);
    if(compareStr(top_w, (char*)"", 1)){
        printf("Top element is %s\n",top_w);
    }
    //if the result is wrong
    else{
        printf("Error: the top element is incorrect\n");
    }
    push(root, word1);
    top_w = peek(root);
    //the top has "Hello World1" after push it.
    if(compareStr(top_w, word1, strlen(word1))){
        printf("Top element is %s\n",top_w);
    }
    //if the result is wrong
    else{
        printf("Error: the top element is incorrect\n");
    }
    push(root, word2);
    top_w = peek(root);
    //the top has "Hello World2" after push it.
    if(compareStr(top_w, word2, strlen(word2))){
        printf("Top element is %s\n",top_w);
    }
    //if the result is wrong
    else{
        printf("Error: the top element is incorrect\n");
    }
    pop(root);
    printf("pop element from the stack\n");
    top_w = peek(root);
    //after pop the top need to be "Hello World1"
    if(compareStr(top_w, word1, strlen(word1))){
        printf("Top element is %s\n",top_w);
    }
    //if the result is wrong
    else{
        printf("Error: the top element is incorrect\n");
    }
    pop(root);
    //pop the last word from the stack
    printf("pop element from the stack\n");
    top_w = peek(root);
    if(compareStr(top_w, (char*)"", 1)){
        printf("Top element is %s\n",top_w);
    }
    //if the result is wrong
    else{
        printf("Error: the top element is incorrect\n");
    }
    pop(root);
    //pop nothing
    printf("pop element from the stack\n");
    top_w = peek(root);
    if(compareStr(top_w, (char*)"", 1)){
        printf("Top element is %s\n",top_w);
    }
    //if the result is wrong
    else{
        printf("Error: the top element is incorrect\n");
    }
    //if the result is wrong
    printf("After compare wrong element with top element: ");
    if(compareStr(top_w, word2, strlen(word2))){
        printf("Top element is %s\n",top_w);
    }
    else{
        printf("Error: the top element is incorrect\n");
    }
    return 0;
}


void* runclient(void *vargp)
{
    //open client terminal and run it
    system("g++ client.cpp -o runC");
    system("./runC");
    return 0;
    
}

void* runserver(void *vargp)
{
    //open server terminal and run it
    system("g++ server.cpp -o runS");
    system("./runS");
    return 0;
    
}


int test_if_run_server()
{
    //open threads for client and server so they can work in the same terminal
    //open thread for the server
    pthread_create(&thread_s, NULL, runserver, NULL);
    sleep(1);
    //open thread for client
    pthread_create(&thread_c, NULL, runclient, NULL);
    sleep(1);
    //continue to 'work
    pthread_join(thread_c, NULL);
    sleep(1);
    system("make clean");

    return 0;
}

int main(){
    
    if(!test_stack()){
        printf("----------test_stack pass with success----------\n");
    }
    system("g++ server.cpp -lpthread -o runS");
    test_stack();
    test_if_run_server();

    return 0;
}