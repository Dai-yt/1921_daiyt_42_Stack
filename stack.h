#ifndef stack_h
#define stack_h
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#define TRUE 1
#define FALSE 0
#define OK 
#define ERROR 
#define INFEASIBLE -1  
#define OVERFLOW -2
#define STACK_INIT_SIZE 100  
#define STACKINCREMENT 10   

typedef char SElemType;
typedef char OperandType;  

typedef struct
{
	SElemType *base;
	SElemType *top;
	int stacksize;
}SqStack;

void InitStack(SqStack *S);
void GetTop(SqStack *S, SElemType *e);
void Push(SqStack *S, SElemType e);
void Pop(SqStack *S, SElemType *e);
void StackDestroy(SqStack *S);
void ClearStack(SqStack *S);
char Precede(char t1, char t2);
char In(OperandType c);
OperandType Operate(OperandType a, OperandType theta, OperandType b);
OperandType EvaluateExpression();

#endif
