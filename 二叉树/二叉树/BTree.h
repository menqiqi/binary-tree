#pragma once

#include<stdio.h>
#include<assert.h>
#include<stdlib.h>

typedef int TDataType;
typedef struct BTreeNode{
	TDataType data;
	struct BTreeNode *left;
	struct BTreeNode *right;
}BTreeNode;

//�������Ľڵ�
BTreeNode *CreateNode(TDataType data)
{
	BTreeNode *node = (BTreeNode*)malloc(sizeof(BTreeNode));
	node->data = data;
	node->left = NULL;
	node->right = NULL;
	return node;
}

//������(�ѵ�)
//����ֵ��
//1.���������ĸ��ڵ�
//2.�������Ĺ����У�ʹ�õ��ַ�����(pUsedSize)
BTreeNode *CreateTree(int preOrder[], int size, int *pUsedSize)
{
	int leftUse;
	int rightUse;
	int rootValue = preOrder[0];
	BTreeNode *root;
	if(size <= 0)
	{
		*pUsedSize = 0;
		return NULL;
	}
	if(rootValue == -1){
		*pUsedSize = 1;
		return NULL;
	}
	root = CreateNode(rootValue);
	root->left = CreateTree(preOrder+1, size-1, &leftUse);
	root->right = CreateTree(preOrder+1+leftUse, size-1-leftUse, &rightUse);

	//����
	*pUsedSize = 1+leftUse+rightUse;

	return root;
}


//������
//ǰ�������
void PreOrder(BTreeNode *root)
{
	if(root == NULL)//����
	{
		return ;
	}
	printf("%d ",root->data);
	PreOrder(root->left);
	PreOrder(root->right);
}

//���������
void InOrder(BTreeNode *root)
{
	if(root == NULL)
	{
		return;
	}
	InOrder(root->left);
	printf("%d ",root->data);
	InOrder(root->right);
}

//���������
void PostOrder(BTreeNode *root)
{
	if(root == NULL)
	{
		return;
	}
	PostOrder(root->left);
	PostOrder(root->right);
	printf("%d ",root->data);
}

//�����Ľڵ����
//1.�����������
//2.�ñ�����⣨����һ��Ҫ�õ�ȫ�ֱ��������ַ������ã�
int GetNodeSize(BTreeNode *root)
{
	int left;
	int right;
	if(root == NULL)
	{
		return 0;
	}
	left = GetNodeSize(root->left);
	right = GetNodeSize(root->right);
	return left+right+1;
}

//��Ҷ�ӽڵ����
int GetLeafSize(BTreeNode *root)
{
	int left;
	int right;
	if(root == NULL)//����
	{
		return 0;
	}
	if((root->left==NULL) && (root->right==NULL))//ֻ��һ���ڵ����
	{
		return 1;
	}
	left = GetLeafSize(root->left);
	right = GetLeafSize(root->right);
	return left+right;
}

//���k��Ľڵ���
int GetLevelKSize(BTreeNode *root, int k)
{
	int left;
	int right;
	assert(k>=1);
	if(root == NULL)//����������㶼��0��
	{
		return 0;
	}
	if(k == 1)//��һ��ֻ��һ���ڵ�
	{
		return 1;
	}
	//�ҵĵ�K�㣬���������ĵ�K-1��
	left = GetLevelKSize(root->left, k-1);
	right = GetLevelKSize(root->right, k-1);
	return left+right;
}

//�����ĸ߶�/���
#define MAX(a,b) ((a)>(b)?(a):(b))
int GetHeight(BTreeNode *root)
{
	int left;
	int right;
	if(root == NULL)
	{
		return 0;
	}
	//������ֻ��һ���ڵ��ʱ�򣬿���д��Ҳ���Բ�д
	//д�Ļ���ʡ���κ�������
	left = GetHeight(root->left);
	right = GetHeight(root->right);
	return MAX(left,right)+1;
}
//
//��һ�����Ƿ�������(�ѵ�)
//ǰ�᣺�����data���ظ�
//����ҵ��ˣ����ؽڵ��ַ
//���û�ҵ�������NULL
//��ƥ�����������������������
BTreeNode *Find(BTreeNode *root, TDataType data)
{
	BTreeNode *result;
	if(root == NULL)
	{
		return NULL;
	}
	if(data == root->data)
	{
		return root;
	}
	result = Find(root->left, data);
	if(result != NULL)
	{
		//�������ҵ���
		return result;
	}
	result = Find(root->right, data);
	if(result != NULL)
	{
		//�������ҵ���
		return result;
	}
	else{
		return NULL;
	}
}





//�������Ĳ������(�ö���ʵ��)
#include "Queue.h"
void LevelOrder(BTreeNode *root)
{
	BTreeNode *front;
	Queue queue;
	QueueInit(&queue);

	if(root == NULL)
	{
		return;
	}
	QueuePush(&queue,root);//�ŵ��ǽڵ�ĵ�ַ������data
	while(!IsEmpty(&queue)){
		front = QueueTop(&queue);
		QueuePop(&queue);

		//front��ʼ�����ߣ��սڵ��ǲ�Ҫ��
		//�������
		if(front->left != NULL)
		{
			QueuePush(&queue,front->left);
		}
		if(front->right != NULL)
		{
			QueuePush(&queue,front->right);
		}
		//�������front�ڵ�
		printf("%d ",front->data);
	}
	//���ٶ��У�ջ����֮�󲻱����٣������б������٣�
	QueueDestroy(&queue);
}




//�ж�һ�����ǲ�����ȫ������
//��ȫ����������������������սڵ�ֻ�ܷ������
int IsCompleteTree(BTreeNode *root)
{
	BTreeNode *front;
	Queue queue;
	QueueInit(&queue);

	if(root == NULL)//��������ȫ������
	{
		return 1;
	}
	QueuePush(&queue,root);//�ŵ��ǽڵ�ĵ�ַ������data

	while(!IsEmpty(&queue)){
		front = QueueTop(&queue);
		QueuePop(&queue);
		//����Ͳ������������front����Ϊ��
		if(front == NULL)
		{
			//�������ȫ��������front����Ӧ�ö��ǿ�
			break;
		}
			QueuePush(&queue,front->left);
			QueuePush(&queue,front->right);
		
	}
	//����ʣ��ڵ��Ƿ���NULL
	//�ж�����Ϊ�� QueueTop(&queue) == NULL,������ǿն����ж�
	while(!IsEmpty(&queue)){
		front = QueueTop(&queue);
		QueuePop(&queue);//�����POP����front��ֵ����Զ����ͬһ��
		if(front != NULL)
		{
			//��������
			QueueDestroy(&queue);
			return 0;
		}
	}

	//���ٶ��У�ջ����֮�󲻱����٣������б������٣�
	QueueDestroy(&queue);
	return 1;
}


//���ǵݹ�ķ�ʽ������������ȱ�����ջʵ�֣�
//ǰ��
#include "Stack.h"
void PreOrderLoop(BTreeNode *root)
{
	BTreeNode *cur;
	BTreeNode *top;
	Stack stack;
	StackInit(&stack);

	cur = root;

	while(cur!=NULL || !StackEmpty(&stack)){
		while(cur != NULL){
			printf("%d ",cur->data);
			StackPush(&stack,cur);
			cur = cur->left;
		}
		//top���������͸��Ѿ���������
		top = StackTop(&stack);
		StackPop(&stack);

		cur = top->right;
	}
}

//����
void InOrderLoop(BTreeNode *root)
{

	BTreeNode *cur;
	BTreeNode *top;
	Stack stack;
	StackInit(&stack);

	cur = root;
	while(cur!=NULL || !StackEmpty(&stack)){
		while(cur != NULL){
			StackPush(&stack,cur);
			cur = cur->left;
		}
		top = StackTop(&stack);
		StackPop(&stack);
		printf("%d ",top->data);
		cur = top->right;
	}
}


//����
void PostOrderLoop(BTreeNode *root)
{
	BTreeNode *cur;
	BTreeNode *top;
	BTreeNode *last = NULL;//��¼��һ��������Ľڵ�
	Stack stack;
	StackInit(&stack);

	cur = root;
	while(!StackEmpty(&stack) || cur!=NULL){
		//����������
		while(cur != NULL){
			StackPush(&stack,cur);
			cur = cur->left;
		}
		//top���������Ѿ���������
		top = StackTop(&stack);
		if(top->right==NULL || top->right==last)
		{
			//�������������������
			printf("%d ",top->data);
			StackPop(&stack);
		//��¼����������Ľڵ�
			last = top;
	}
		else{
			//������û�б�������
			cur = top->right;
		}
	}
}



//����(��������������������ã�Ȼ�󽻻�)
//�ݹ�
void Mirror1(BTreeNode *root)
{
	BTreeNode *tmp;
	if(root == NULL)
	{
		return;
	}
	Mirror1(root->left);
	Mirror1(root->right);
	tmp = root->left;
	root->left = root->right;
	root->right = tmp;
}

//�ǵݹ�
void Mirror2(BTreeNode *root)
{
	BTreeNode *cur;
	BTreeNode *top;
	BTreeNode *last = NULL;
	BTreeNode *tmp;
	Stack stack;
	StackInit(&stack);

	cur = root;
	while(cur!=NULL || !StackEmpty(&stack)){
		//����������
		while(cur != NULL){
		StackPush(&stack,cur);
		cur = cur->left;
	}
	//top���������Ѿ���������
	top = StackTop(&stack);
	if(top->right==NULL || top->right==last)
	{
		//�������������������
		StackPop(&stack);
		//�滻��ԭ���Ĵ�ӡ
		tmp = top->left;
		top->left = top->right;
		top->right = tmp;

		//��¼����������Ľڵ�
		last = top;
	}
	else{
		//���������û�б�������
		cur = top->right;
	}
	}
}

void Test()
{
	int preOrder[] = {1,2,3,-1,4,5,-1,-1,-1,6,-1,-1,7,8,-1,-1,9,-1,10};//��ǰ�����
	//int preOrder[] = {1,2,3,-1,-1,4,-1,-1,5,6};
	int size = sizeof(preOrder)/sizeof(preOrder[0]);
	int usedSize;
	BTreeNode *root = CreateTree(preOrder, size, &usedSize);
	int ret;

#if 0
	PreOrder(root);
	printf("\n");

	InOrder(root);
	printf("\n");

	PostOrder(root);
	printf("\n");

	printf("���Ľڵ�����ǣ�%d\n",GetNodeSize(root));
	printf("Ҷ�ӽڵ�ĸ���Ϊ��%d\n",GetLeafSize(root));
	printf("������Ľڵ���Ϊ��%d\n",GetLevelKSize(root,3));
	printf("�������Ϊ��%d\n",GetHeight(root));

	Find(root,9);

	LevelOrder(root);
	printf("\n");

	ret = IsCompleteTree(root);
	if(ret == 1){
		printf("����ȫ������\n");
	}
	else{
		printf("������ȫ������\n");
	}

	PreOrderLoop(root);
	printf("\n");

	InOrderLoop(root);
	printf("\n");

	PostOrderLoop(root);
	printf("\n");

	Mirror1(root);
	Mirror2(root);
#endif

}