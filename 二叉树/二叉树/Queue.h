//��ʽ����
#pragma once

#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

struct BTreeNode;

typedef BTreeNode* QDataType;

typedef struct QueueNode{ //��ʽ���нڵ�Ľṹ�嶨��
	QDataType data;
	struct QueueNode* next;
}QueueNode;

typedef struct Queue{ //��ʽ���еĽṹ�嶨��
	QueueNode* front;//��ͷָ��
	QueueNode* rear;//��βָ��
}Queue;

//��ʼ��
void QueueInit(Queue *pQueue)
{
	pQueue->front = pQueue->rear = NULL;
	
}

//����
void QueueDestroy(Queue *pQueue)
{
	QueueNode* cur;
	QueueNode* next;
	for(cur=pQueue->front; cur!=NULL; cur=next)
	{
		next = cur->next;
		free(cur);
	}
	pQueue->front = pQueue->rear = NULL;
}

static QueueNode* QCreateNode(QDataType data)
{
	QueueNode* newNode = (QueueNode*)malloc(sizeof(QueueNode));
	assert(newNode);
	newNode->data = data;
	newNode->next = NULL;
	return newNode;
}

//�����Ӷ�β����У�
void QueuePush(Queue *pQueue, QDataType data)
{
	QueueNode* newNode = QCreateNode(data);
	//���������һ���ڵ㶼û��
	if(pQueue->front == NULL)
	{
		pQueue->front = pQueue->rear = newNode;
		return;
	}
	//�������
	pQueue->rear->next = newNode;
	pQueue->rear = newNode;
}

//ɾ���Ӷ�ͷɾ����
void QueuePop(Queue* pQueue)
{
	QueueNode *cur = pQueue->front;
	assert(pQueue != NULL);
	assert(pQueue->front != NULL);
	//���������ֻ��һ���ڵ�
	if(pQueue->front == NULL)
	{
		pQueue->rear = NULL;
		return;
	}
	//�������
	pQueue->front = cur->next;
	free(cur);
}

//�Ƿ�Ϊ��
int IsEmpty(const Queue* pQueue)
{
	return pQueue->front == NULL;
}

//��
QDataType QueueTop(Queue* pQueue)
{
	assert(pQueue != NULL);//��ַ��Ϊ��
	assert(pQueue->front != NULL);//����Ϊ�գ���֧��
	return pQueue->front->data;
}

//�������ݸ���
int QueueSize(const Queue* pQueue)
{
	int size = 0;
	QueueNode* cur;
	for(cur=pQueue->front; cur!=NULL; cur=cur->next)
	{
       size++;
	}
	return size;
}
