#pragma once
#include "BTree.h"

//��������������ڵ������������Ƚ��
BTreeNode* GetAncestor(BTreeNode *root, BTreeNode *node1, BTreeNode *node2)
{
	//�ж�node1��node2���ĸ�����
	BTreeNode *node1InLeft = Find(root->left,node1->data);
	BTreeNode *node2InLeft = Find(root->left,node2->data);
	BTreeNode *node1InRight = Find(root->right,node1->data);
	BTreeNode *node2InRight = Find(root->right,node2->data);

	//�����ڵ㲻��ͬһ��������
	if((node1InLeft && node2InRight) || (node1InRight && node2InLeft))
	{
		return root;
	}
	if(node1InLeft)
	{
		return GetAncestor(root->left,node1,node2);
	}
	else
	{
		return GetAncestor(root->right,node1,node2);
	}
}

//�ж�һ�ö������Ƿ�Ϊƽ�������
//1.������������ƽ����
//2.���������߶�������1
int IsBalance(BTreeNode* root)
{
	int leftBalance;
	int rightBalance;
	int leftHeight;
	int rightHeight;
	int diff;//�߶Ȳ�
	if(root == NULL)
	{
		return 1;
	}
	//�ж��������Ƿ�ƽ��
	leftBalance = IsBalance(root->left);
	if(!leftBalance){
		//�����������ƽ�⣬û��Ҫ������������һ����ƽ��
		return 0;
	}
	//�ж��������Ƿ�ƽ��
	rightBalance = IsBalance(root->right);
	if(!rightBalance){
		//�����������ƽ�⣬��ô�����һ����ƽ��
		return 0;
	}
	leftHeight = GetHeight(root->left);
	rightHeight = GetHeight(root->right);
	//�߶�������1
	diff = leftHeight - rightHeight;
	if(diff>=-1 && diff<=1){
		return 1;
	}
	else{
		return 0;
	}
}

//�Ż�
int IsBalanceAd(BTreeNode *root, int *pHeight)
{
	int leftBalance;
	int rightBalance;
	int leftHeight;
	int rightHeight;
	int diff;
	if(root == NULL)
	{
		*pHeight = 0;
		return 1;
	}
	//�ж��������Ƿ�ƽ��
	leftBalance = IsBalanceAd(root->left,&leftHeight);
	if(!leftBalance){
		//��������ƽ�⣬�����һ����ƽ��
		*pHeight = -1;//��ƽ���������߶�û���ã���һ���������ֵ
			return 0;
	}
	//�ж��������Ƿ�ƽ��
	rightBalance = IsBalanceAd(root->right,&rightHeight);
	if(!rightBalance){
		//ͬ��
		*pHeight = -1;
		return 0;
	}
	//�������������ĸ߶�
	*pHeight = MAX(leftHeight,rightHeight)+1;
	//�߶Ȳ����1
	diff = leftHeight - rightHeight;
	if(diff>=-1 && diff<=1){
		return 1;
	}
	else{
		return 0;
	}
}

//�����������Զ�������ڵ�֮��ľ���
#include<stdio.h>
int MAX_TREE(int a, int b, int c)
{
	if(a>=b && a>=c){
	    return a;
	}
	if(b>=a && b>=c){
		return b;
	}
	return c;
}

//�Ż�����߶ȵĹ���
int GetLongDistance(BTreeNode *root)
{
	int leftLD;
	int rightLD;
	int leftHeight;
	int rightHeight;
	int rootLD;
	if(root == NULL){
		return 0;
	}                                                                                        
	leftLD = GetLongDistance(root->left);
	rightLD = GetLongDistance(root->right);
	leftHeight = GetHeight(root->left);
	rightHeight = GetHeight(root->right);
	rootLD = leftHeight+rightHeight;
	return MAX_TREE(leftLD, rightLD, rootLD);
}

void Test2()
{
	int preOrder[] = {1,2,3,-1,4,5,-1,-1,-1,6,-1,-1,7,8,-1,-1,9,-1,10};//��ǰ�����
	//int preOrder[] = {1,2,3,-1,-1,4,-1,-1,5,6};
	int size = sizeof(preOrder)/sizeof(preOrder[0]);
	int usedSize;
	int pHeight;
	int r;
	BTreeNode *root = CreateTree(preOrder, size, &usedSize);
	
	GetAncestor(root,root->left->left,root->left->right);

	if(IsBalanceAd(root,&pHeight) == 1){
		printf("��ƽ����\n");
	}
	else{
		printf("����ƽ����\n");
	}

	r = GetLongDistance(root);
	printf("�����ڵ�֮�����Զ������%d\n",r);
}
