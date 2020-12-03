#include "stack.h"

void InitStack(SqStack *S)
{
	S->base = (SElemType *)malloc(STACK_INIT_SIZE * sizeof(SElemType));
	if(!S->base)
	{
		printf("内存分配失败!\n");
		exit(OVERFLOW);
	}

	S->top = S->base;
	S->stacksize = STACKINCREMENT;
	return OK;
}

void GetTop(SqStack *S, SElemType *e)
{
	if(S->top == S->base)
		return ERROR;

	*e = *(S->top - 1);
	return OK;
}

void Push(SqStack *S, SElemType e)
{
	if(S->top - S->base >= STACK_INIT_SIZE)   
	{
		S->base = (SElemType *)realloc(S->base, (S->stacksize + STACKINCREMENT) * sizeof(SElemType));
		if(!S->base)
		{
			printf("内存分配失败!\n");
			exit(OVERFLOW);
		}

		S->top = S->base + S->stacksize;
		S->stacksize += STACKINCREMENT;
	}

	*S->top++ = e;
	
	return OK;
}

void Pop(SqStack *S, SElemType *e)
{
	if(S->top == S->base)
		return ERROR;

	*e =  *--S->top;

	return OK;
}
void StackDestroy(SqStack *S)
{
	free(S->base);
	S->base = NULL;
	S->top = NULL;
	S->stacksize = 0;
	return OK;
}

void ClearStack(SqStack *S)
{
	S->top = S->base;
}

char Precede(char t1, char t2) {  
    int i,j;  
    char pre[][7]={           
    //运算符之间的优先级制作成一张表格  
        {'>','>','<','<','<','>','>'},  
        {'>','>','<','<','<','>','>'},  
        {'>','>','>','>','<','>','>'},  
        {'>','>','>','>','<','>','>'},  
        {'<','<','<','<','<','=','0'},  
        {'>','>','>','>','0','>','>'},  
        {'<','<','<','<','<','0','='}};  
    switch(t1){  
        case '+': i=0; break;  
        case '-': i=1; break;  
        case '*': i=2; break;  
        case '/': i=3; break;  
        case '(': i=4; break;  
        case ')': i=5; break;  
        case '=': i=6; break;  
    }  
    switch(t2){  
        case '+': j=0; break;  
        case '-': j=1; break;  
        case '*': j=2; break;  
        case '/': j=3; break;  
        case '(': j=4; break;  
        case ')': j=5; break;  
        case '=': j=6; break;  
    }  
    return pre[i][j];  
}  

char In(OperandType c)
{
	switch(c)
	{
	case '+':
	case '-':
	case '*':
	case '/':
	case '(':
	case ')':
	case '=':
		return TRUE;
	default:
		return FALSE;
	}

}


OperandType Operate(OperandType a, OperandType theta, OperandType b)
{
	OperandType c;
	switch(theta)
	{
	case '+':
		c = a + b;
		break;
	case '-':
		c = a - b;
		break;
	case '*':
		c = a * b;
		break;
	case '/':
		c = a / b;
		break;
	}
	return c;
}

OperandType EvaluateExpression()
{
	SqStack OPTR, OPND;
	OperandType a, b, d, x, theta;
	char c;  
	char z[6];   
	int i;
	InitStack(&OPTR);   
	Push(&OPTR, '=');   
	InitStack(&OPND);   

	c = getchar();
	GetTop(&OPTR, &x);
	while(c != '=' || x != '=')
	{
		if(In(c))   
		{
			switch(Precede(x, c))
			{
			case '<':   
				Push(&OPTR, c);
				c = getchar();
				break;
			case '=':
				Pop(&OPTR, &x);   
				c = getchar();
				break;
			case '>':
				Pop(&OPTR, &theta); 
				Pop(&OPND, &b);
				Pop(&OPND, &a);
				Push(&OPND, Operate(a, theta, b));
				break;
			}
		}
			else if(c >= '0' && c <= '9')  
			{
				i = 0;
				do
				{
					z[i] = c;
					i ++;
					c = getchar();
				}while(c >= '0' && c <= '9');
				z[i] = 0;
				d = atoi(z); 
				Push(&OPND, d);
			}
			else   
			{
				printf("ERROR3\n");
				exit(1);
			}
			GetTop(&OPTR, &x);
		}
	GetTop(&OPND, &x);
	StackDestroy(&OPTR);
	StackDestroy(&OPND);
	return x;
}

