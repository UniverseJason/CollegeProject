#include "Stack.h"
/******
 * In this file, provide all of the definitions of the stack functions as described in stack.h.
 *
 * ****/

//Malloc a new StackImp, malloc an array of Elements of size maximumStackSize (store the address in stackElements pointer), set maxSize to be maximumStackSize, initialize count to be 0, and return a pointer to the StackImp.
Stack newStack(int maximumStackSize)
{
    StackImp * newStackImp = (StackImp*)malloc(sizeof(StackImp));
    newStackImp->stackElements = (Element*)malloc(maximumStackSize * sizeof(StackImp));
    if(newStackImp == NULL || newStackImp->stackElements == NULL) //check if we malloc the stack correctly.
    {
        printf("Error: malloc fail!\n");
        exit(0);
    } 
    
    newStackImp->maxSize = maximumStackSize;
    newStackImp->count = 0;
    return newStackImp;
}


//Free stackElements and then free the Stack s.
void freeStack(Stack s)
{
    free(s->stackElements);
    free(s);
}


//Push a new Element e onto the Stack s, and increment the count variable.  Print an error message if the stack was already full.
void push(Stack s, Element e)
{
    if(s->count == s->maxSize)
    {
        printf("Error: Stack Overflow\n");
        return;
    }

    s->count++;
    s->stackElements[s->count] = e;
}


//Pop an element off the stack, decrement the count variable, and return the element's value.
Element pop(Stack s)
{
    
    if(s->count == 0)
    {
        printf("Error: Stack is empty, unable to pop.\n");
        exit(0);
    }
    
    s->count--;
    return s->stackElements[s->count];
}


//Return true (1) if stack is empty and false (0) otherwise.
int isEmpty(Stack s)
{
    if(s->count == 0)
    {
        return 1;
    }
    return 0;
}


//Return the value of the top element of the stack (without removing it).
Element topElement(Stack s)
{
    
    if(isEmpty(s) == 1)
    {
        printf("Error: stack is empty, unable to find topElement.\n");
        exit(0);
    }
    
    return s->stackElements[s->count];
}
