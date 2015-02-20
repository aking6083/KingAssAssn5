#include "stdafx.h"
#include <iostream>

using namespace std;

const int treeData [10] = {20, 65,43,87,10,45,76,23,87,55};
//Binary Tree Node

struct BstNode {
	int data;
	BstNode* left;
	BstNode* right;

};

struct BsTree {
	BstNode* root;
	int count;
};
//Traverse list in pre-order
void PreOrder (BstNode* subTree)
{
	if (subTree != NULL)
	{
		cout << subTree->data << endl;
		PreOrder(subTree->left);
		PreOrder(subTree->right);
	}
	return;
}


//Post order traversal
void PostOrder (BstNode* subTree)
{
	if (subTree != NULL)
	{
		PostOrder (subTree->left);
		PostOrder (subTree->right);
		cout << subTree->data << endl;
	}
}
BstNode* CreateNode(int data)
{
	BstNode* newNode = new BstNode();
	newNode->data = data;
	newNode->left = newNode->right = NULL;
	return newNode;

}

BsTree * CreateTree()
{
	BsTree* newTree = new (nothrow) BsTree;
	if (newTree)
	{
		newTree->root = NULL;
		newTree->count = 0;
	}
	return newTree;
}

BstNode* Insert(BstNode* rootPtr, int data)
{
	if (!rootPtr)
	{
		rootPtr = CreateNode(data);
		
	}
	else if (data < rootPtr->data) 
	{
		rootPtr->left = Insert(rootPtr->left,data);
		
	}
	else 
	{
		rootPtr->right = Insert(rootPtr->right,data);
		
	}
	return rootPtr;
}

int main(int argc, char* argv[])
{
	BsTree* myTree = CreateTree();
	BstNode* root = NULL;
	root = Insert(root,76);
	myTree->count++;
	
	root = Insert(root,46);
	myTree->count++;
	
	root = Insert(root,26);
	myTree->count++;
	
	root = Insert(root,54);
	myTree->count++;
	
	root = Insert(root,34);
	myTree->count++;
	
	root = Insert(root, 99);
	myTree->count++;

	root = Insert(root, 230);
	myTree->count++;

	root = Insert (root, 1);
	myTree->count++;

	root = Insert(root,41);
	myTree->count++;
	
	root = Insert(root,32);
	myTree->count++;

	root = Insert(root,34);
	myTree->count++;

	root = Insert(root, 74);
	myTree->count++;

	root = Insert(root, 94);
	myTree->count++;
	
	root = Insert (root, 15);
	myTree->root = root;
	
	PreOrder(myTree->root);
	cout << endl;
	PostOrder(myTree->root);
	return 0;
}



