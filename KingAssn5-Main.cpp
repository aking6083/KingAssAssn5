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

//Creates the node for the tree


/*int nodeLevel (btNode* binRoot, btNode* node)
{
	int depth = 0;
	
	while (node != binRoot)
	{
		//node = node->parent;
		depth++;
	}
	return depth;
}
*/

bool isExternal(BstNode* node)
{
	bool isXternal = false;
	
	//External means no kids.
	if (node != NULL)
	{
		if ((node->left == NULL) && (node->right == NULL ))
			isXternal = true;
	}
	return isXternal;
}

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
BstNode* GetNewNode(int data)
{
	BstNode* newNode = new BstNode();
	newNode->data = data;
	newNode->left = newNode->right = NULL;
	return newNode;

}


BstNode* Insert(BstNode* rootPtr, int data)
{
	if (!rootPtr)
	{
		rootPtr = GetNewNode(data);
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
	BstNode* root = NULL;
	root = Insert(root,76);
	root = Insert(root,46);
	root = Insert(root,26);
	root = Insert(root,54);
	root = Insert(root,34);
	root = Insert(root, 99);
	root = Insert(root, 230);
	root = Insert (root, 1);
	root = Insert(root,41);
	root = Insert(root,32);
	root = Insert(root,34);
	root = Insert(root, 74);
	root = Insert(root, 94);
	root = Insert (root, 15);
	


	PreOrder(root);
	cout << endl;
	PostOrder(root);
	return 0;
}


