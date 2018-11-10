#pragma once

#include<stdio.h>
#include<stdlib.h>
#include<assert.h> 
#include<string.h>

struct BTreeNode;
typedef BTreeNode* StackDataType;

#define MAX_SIZE (100)

typedef struct Stack{
	StackDataType array[MAX_SIZE];
	int top;//��ʾ��ǰ����
}Stack;

//��ʼ��/����
//����ֻ�ܴ�ջ����/ɾ��ֻ�ܴ�ջ����/�飨ֻ�ܴ�ջ����
//����/�Ƿ��/�Ƿ���
//��----˳����β��
//ɾ----˳����βɾ

void StackInit(Stack *pStack)
{
	pStack->top = 0;
}

void StackDestroy(Stack *pStack)
{
	pStack->top = 0;
}

void StackPush(Stack *pStack, StackDataType data)
{
	assert(pStack->top < MAX_SIZE);
	pStack->array[pStack->top++] = data;
}

void StackPop(Stack *pStack)
{
	assert(pStack->top > 0);
	pStack->top--;
}

StackDataType StackTop(const Stack *pStack)
{
	assert(pStack->top > 0);
	return pStack->array[pStack->top-1];
}

int StackSize(const Stack* pStack)
{
	return pStack->top;
}

int StackFull(const Stack* pStack)
{
	return pStack->top >= MAX_SIZE;
}

int StackEmpty(const Stack* pStack)
{
	return pStack->top <= 0;
}

void StackCopy(Stack *pDest, Stack *pSrc)
{
	memcpy(pDest->array, pSrc->array, sizeof(StackDataType)* pSrc->top);
	pDest->top = pSrc->top;
}