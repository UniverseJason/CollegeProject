/******************
*
* @ Student Jiaxing Li
* @ Student ID: ycy354
* This program convert infxi to postfix, and check the error at the same time;
*
********************/
#include "Stack.h"

#define MAX_LINE_LENGTH 50

int convertToPostfix(char *infixString, char *postfixString);
int evaluatePostfix(char *postfixString);
int operatorPre(char c);
int precedenceCheck(char op1, char op2);
int isOperator(char c);
int isOperand(char c);

int main()
{
	FILE *inputFile;
	inputFile = fopen("p1Input.txt", "r");
	if(inputFile == NULL){

		perror("Error opening file");
		return -1;
	}


	//This string will hold the infix equations that are read from inputFile, one at a time.
	char infixString[MAX_LINE_LENGTH];


	//Use fgets to read the next line from the inputFile.
	//Store the line into infixString.
	//The while loop repeats until there are no more lines in the file.
	while(fgets(infixString, MAX_LINE_LENGTH, inputFile)!=NULL){

		//If the line is blank, skip it.
		if(infixString[0] == '\n')
			continue;

		printf("Current infix string: %s",infixString);

		//postfixString is a string to store the equation from szInfixString converted into postfix.
		char postfixString[MAX_LINE_LENGTH];

		//Call the convertToPostfix function (that you are to implement below main).
		int returnMessage = convertToPostfix(infixString,postfixString);


		//convertToPostfix should return an integer letting us know if the infix string was in a valid format.
		//If the format is valid (we returned 0), then we call the evalutaePostfix function (that you are to implement below), and print the result of the evalution.
		//If the format is not valid (we returned something other than 0), then we print the corresponding error message.
		switch(returnMessage)
		{

			case 0: //0 means the infix string had no errors.  Go ahead and evaluate the postfix string.
				printf("Postfix string: %s\n",postfixString);
			    int result = evaluatePostfix(postfixString);
				printf("It evaluates to %d.\n",result);
				break;
			case 1:  //1 means the infix string is missing a left parenthesis.
				printf("WARNING: Missing left parenthesis.\n");
				break;
			case 2: //2 means the infix string is missing a right parenthesis.
				printf("WARNING: Missing right parenthesis.\n");
				break;
			case 3: // 3 means missing operator.
				printf("WARNING: Missing operator.\n");
				break;
			case 4: //4 means missing operand.
				printf("WARNING: Missing operand.\n");
				break;
			default:
				printf("WARNING: %d.\n", returnMessage);


		}

        // IMPORTANT: clean the buffer left inside the postfixString
        memset(postfixString,0,sizeof(postfixString));

		printf("\n\n");
	}

	fclose(inputFile);

	return 0;
}

//give value to operator
int operatorPre(char c)
{
    if(c=='*' || c=='/')
        return 2;
    else if(c=='+'|| c=='-')
        return 1;
    else
        return 0;
}


// if the precedence of : op1 > op2, return 1; 
// else return 0
int precedenceCheck(char op1, char op2)
{
    if ( operatorPre(op1) >= operatorPre(op2) ) return 1;
    else return 0;
}

// return 1 for ture, 0 for false
int isOperator(char c)
{
	if(c == '+' || c == '-' || c == '*' || c == '/')
		return 1;
	return 0;
}

// return 1 for true, 0 for false
int isOperand(char c)
{
    if( isdigit(c) || isalpha(c) )
        return 1;
	return 0;
}


/*******
int convertToPostfix(char *infixString, char *postfixString)

Input: 
infixString is a character array of length <= MAX_LINE_LENGTH that contains an equation in infix format.
postfixString is a currently empty character array of length <= MAX_LINE_LENGTH that we should fill with a postfix representation of infixString.

Output:
We return an integer based on any errors found in infixString.
If there are no errors, return 0.
If there is a missing (, return 1.
If there is a missing ), return 2.
If there is a missing operator, return 3 (for extra credit).
If there is a missing operand, return 4 (for extra credit).
*********/
int convertToPostfix(char *infixString, char *postfixString)
{
    StackImp *stack = newStack(strlen(infixString));
    Element type;
    int len = strlen(infixString);
    int i,j; //i for infix ; j for postfix

    //check infixString Error
    int a;
    int operandCount = 0;
    int operatorCount = 0;
    for(a=0; a<strlen(infixString); a++)
    {
        if(infixString[a]== ' ') continue;
        if(isOperand(infixString[a]) == 1) operandCount++;
        if(isOperator(infixString[a]) == 1) operatorCount++;
    }
    if(operandCount == operatorCount || operandCount == 0) return 4;
    if(operatorCount == 0)
    {
        return 3;
    }

    
    // loop each element inside the infixString
    for(i=0; i<len; i++) 
    {
        // 1. skip space
        if(infixString[i] == ' ') continue; 

        // 2. if is operand, put in to postfix directly
        else if(isOperand(infixString[i]) == 1) 
        {
            postfixString[j++]=infixString[i];
        }

        // 3. if it is operator, need to check
        else if(isOperator(infixString[i]) == 1) 
        {
            // while stack is not empty, and top is not '(', and top Element have higher precedence
            while(isEmpty(stack) == 0 && topElement(stack).operation != '(' && precedenceCheck(topElement(stack).operation, infixString[i]) == 1)
            {
                //keep add operator to the postfixString and pop it
                postfixString[j++] = topElement(stack).operation; 
                pop(stack);
            }
            
            //push the current operator to the stack
            type.operation = infixString[i];
            push(stack,type);
        }

        // 4. push character in stack if it is '('
        else if(infixString[i] == '(') 
        {
            //check error first
            int n;
            for(n=i; n<strlen(infixString); n++)
            {
                if(infixString[n] == ')') break;  
                if(infixString[n] != ')' && n == strlen(infixString)-1)
                {
                    return 2; // Error message 2
                }
            }

            // push ( in to the stack
            type.operation = infixString[i];
            push(stack, type);
        }


        // 5. if is ')', keep find until the '('
        else if(infixString[i] == ')')  
        {
            // check error
            int n;
            if(isEmpty(stack) == 1)
            {
                return 1;
            }
            else
            {
                for(n=strlen(infixString); n>=0; n--)
                {
                    if(infixString[n]=='(') break;
                    if(infixString[n] != '(' && n == 0)
                    {
                        return 1; // Error message 1
                    }
                }
            }

            while(topElement(stack).operation != '(')
            {
                // then pop what operation left in the stack befor '('
                postfixString[j++] = topElement(stack).operation; 
                pop(stack); 
            }
            pop(stack); // pop the '(' away
        }
        

    } // end of the big for-loop 

    //pop rest of the element left in the stack to the postfixString
    while(stack->count != 0)
    {
        postfixString[j++] = topElement(stack).operation;
        pop(stack);
    }

    
    freeStack(stack);
    return 0; // infixString have no error and finish the convert To Postfix
}



/************
evaluatePostfix(char *postfixString)

Input:
postfixString is a string of length <= MAX_LINE_LENGTH that contains an equation in postfix representation.
If your convertToPostfix() function is correct, this string should be in a valid postfix format.

Output:
Return an integer representing what the postfix equation evaluated to.
************/
int evaluatePostfix(char *postfixString)
{
    StackImp *stack = newStack(strlen(postfixString));
    Element num1, num2, ele;
    num1.operand = 0;
    num2.operand = 0;
    ele.operand = 0;

    //check each element one by one
    int i;
    for(i=0; postfixString[i] != '\0'; i++)
    {
        //skip the space in case
        if(postfixString[i] == ' ') continue;

        // if is a operand, push to the stack
        else if(isOperand(postfixString[i]) == 1)
        {
            ele.operand = postfixString[i] - '0';
            push(stack, ele);
        }

        //if is a operator, pop two element and do the calculation
        else
        {
            num2.operand = topElement(stack).operand;
            pop(stack);

            num1.operand = topElement(stack).operand;
            pop(stack);
        
            switch(postfixString[i])
            {
                case '+': 
                    ele.operand = num1.operand + num2.operand;
                    push(stack, ele);
                    break;
                case '-': 
                    ele.operand = num1.operand - num2.operand;
                    push(stack, ele);
                    break;
                case '*': 
                    ele.operand = num1.operand * num2.operand;
                    push(stack, ele);
                    break;
                case '/': 
                    ele.operand = num1.operand / num2.operand;
                    push(stack, ele);
                    break;
            }
        }
    
    }//end of the for loop

    //return the result in the stack
	return topElement(stack).operand;
}