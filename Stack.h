/****************************
 Stack.h

Purpose:
	Struct definition of a Stack.
	Define the function protoypes used by Stacks.
 *************************/


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include<ctype.h> // isdigit


//We want two different types of stacks in our program. 
//When converting infix to postfix, we want a stack to store operators and parenthesis (characters).
//When evaluating a postfix string, we want a stack to store operands (integers).
//Therefore we are defining an Element to be the union of a char and int, and we can define our Stack to be a Stack of Elements.
typedef union{
		int operand;
		char operation;
} Element;


//Defining the a struct for a Stack Implementation.
typedef struct
{
	//The maximum size of the stack.
	int maxSize;
	
	//The number of elements currently in the stack.
	int count;
	
	//Pointer to an array of Elements to store data in the stack.
	Element *stackElements;
	
	
} StackImp;


//Defining a Stack to be a StackImp Pointer.
typedef StackImp *Stack;



/*****FUNCTION PROTOTYPES**********/

//Malloc a new StackImp, malloc an array of Elements of size maximumStackSize (store the address in stackElements pointer), set maxSize to be maximumStackSize, initialize count to be 0, and return a pointer to the StackImp.
Stack newStack(int maximumStackSize);


//Free stackElements and then free the Stack s.
void freeStack(Stack s);


//Push a new Element e onto the Stack s, and increment the count variable.  Print an error message if the stack was already full.
void push(Stack s, Element e);


//Pop an element off the stack, decrement the count variable, and return the element's value.
Element pop(Stack s);


//Return true (1) if stack is empty and false (0) otherwise.
int isEmpty(Stack s);


//Return the value of the top element of the stack (without removing it).
Element topElement(Stack s);

