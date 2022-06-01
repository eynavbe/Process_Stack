// C program for linked list implementation of stack
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include "mallocCalloc.cpp"
#include <cstring>

#define TXT 1024;

//the node struct
struct StackNode {
	int start;
	char next[1024][1024];
};


//Checks if the stack is empty
int isEmpty(struct StackNode* root)
{
	return (root->start == 0);
}

//push value into the stack.
void push(struct StackNode* root, char * data)
{
	
	printf("%s pushed to stack\n", data);
	char data2[1024];
	strcpy(data2, data); 
	int TOP = root->start;
	int MAX = 1024;
	if(TOP==MAX-1)
    {
        printf("stack is full\n");
        return;
    }
    root->start = root->start + 1;
		strcpy(root->next[root->start], data); 

}

//pop text from the stack
char * pop(struct StackNode* root)
{
	//If there is nothing in the stack it will return an empty string and pop nothing
	if (isEmpty(root))
		return (char*)"";
	//Takes out the first node and the node after it is updated to be the root
	// struct StackNode* temp = *root;
	char * popped = root->next[root->start];
	(root)->start = (root)->start-1;

	return popped;
}

//display (output) the stack top.
char * peek(struct StackNode* root)
{
	//If there is nothing in the stack it will return an empty string
	if (isEmpty(root))
		return (char*)"";
	//return the data of the first node
	return root->next[root->start];
}