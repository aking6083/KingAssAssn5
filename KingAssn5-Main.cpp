#include "stdafx.h"
#include <iostream>

using namespace std;

const int treeData[10] = { 20, 65, 43, 87, 10, 45, 76, 23, 87, 55 };
//Binary Tree Node

struct BstNode {
	int data;
	BstNode* parent;
	BstNode* left;
	BstNode* right;

};

struct BsTree {
	BstNode* root;
	int count;
};

bool isEmpty(BsTree* myTree)
{
	bool isEmpty = false;

	if (myTree->root == NULL)
		isEmpty = true;

	return isEmpty;
}

//Traverse list in sorted order
void InOrderDisplay(BstNode* myTree)
{
	if (myTree != NULL)
	{
		InOrderDisplay(myTree->left);
		cout << myTree->data << endl;
		InOrderDisplay(myTree->right);
	}
}

//Traverse list in pre-order
void PreOrder(BstNode* subTree)
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
void PostOrder(BstNode* subTree)
{
	if (subTree != NULL)
	{
		PostOrder(subTree->left);
		PostOrder(subTree->right);
		cout << subTree->data << endl;
	}
}
BstNode* CreateNode(int data)
{
	BstNode* newNode = new BstNode();
	newNode->data = data;
	newNode->parent = NULL;
	newNode->left = newNode->right = NULL;
	return newNode;

}
BsTree * CreateTree()
{
	BsTree* newTree = new (nothrow)BsTree;
	if (newTree)
	{
		newTree->root = NULL;
		newTree->count = 0;
	}
	return newTree;
}
BstNode* InsertNode(BstNode* rootPtr, int data)
{
	if (!rootPtr)
	{
		rootPtr = CreateNode(data);
	}
	else if (data < rootPtr->data)
	{
		rootPtr->left = InsertNode(rootPtr->left, data);
		rootPtr->parent = rootPtr;
	}
	else
	{
		rootPtr->right = InsertNode(rootPtr->right, data);
		rootPtr->parent = rootPtr;
	}
	return rootPtr;
}

BstNode * FindNode(int data, BstNode* myTree, bool& found)
{
	if (myTree == NULL)
	{
		//data not found in tree
		found = false;
		return myTree;
	}
	else if (data < myTree->data)
	{
		//search left subtree
		found = false;
		return FindNode(data, myTree->left, found);
	}
	else if (data > myTree->data)
	{
		//search right tree
		found = false;
		return FindNode(data, myTree->right, found);
	}
	else
	{
		//data found
		found = true;
		return myTree;
	}

}

void DeleteFromTree(BstNode* &myTree)  //Change to node.
{
	BstNode* current;
	BstNode* trailCurrent;
	BstNode* temp;

	if (myTree == NULL)
		cout << "Node delete error\n";
	else if (myTree->left == NULL && myTree->right == NULL)
	{
		temp = myTree;
		myTree = NULL;
		delete temp;
	}
	else if (myTree->left == NULL)
	{
		temp = myTree;
		myTree = temp->right;  //Move it around
		delete temp;
	}
	else if (myTree->right == NULL)
	{
		temp = myTree;
		myTree = temp->left;  //Move it around.
		delete temp;
	}
	else
	{
		current = myTree->left;
		trailCurrent = NULL;

		while (current->right != NULL)
		{
			trailCurrent = current;
			current = current->right;
		}
		myTree->data = current->data;

		if (trailCurrent == NULL) //No movement
			myTree->left = current->left;
		else
			trailCurrent->right = current->right;

		delete current;
	}
}


void DeleteNode(int dataToDel, BsTree* &myTree)
{
	BstNode* current = NULL;
	BstNode* trailCurrent = NULL;
	bool found = false;

	if (myTree->root == NULL)
		cout << "Tree is Empty";
	else
	{
		current = myTree->root;
		trailCurrent = myTree->root;

		while (current != NULL && !found)
		{
			if (current->data == dataToDel)
				found = true;
			else
			{
				trailCurrent = current;

				if (current->data > dataToDel)
					current = current->left;
				else
					current = current->right;
			}
		}
		if (current == NULL && dataToDel != 0)
			cout << dataToDel << " is not in the tree\n";
		else if (found)
		{
			if (current == myTree->root)
				DeleteFromTree(myTree->root);
			else if (trailCurrent->data > dataToDel)
				DeleteFromTree(trailCurrent->left);
			else
				DeleteFromTree(trailCurrent->right);
		}
	}
}

void FreeNodes(BsTree* &myTree)
{
	if (!isEmpty(myTree))
	{
		DeleteFromTree(myTree->root);
		FreeNodes(myTree);
	}
}

void DestroyTree(BsTree* &myTree)
{
	if (isEmpty(myTree))
	{
		myTree->root = NULL;
		myTree->count = 0;
		delete myTree;
	}
	else
	{
		FreeNodes(myTree);
		delete myTree;
	}
}


int main(int argc, char* argv[])
{
	BsTree* myTree = CreateTree();
	BstNode* root = NULL;
	BstNode* tmpNode = NULL;
	bool isNodeFound = false;

	root = InsertNode(root, 50);
	myTree->count++;

	root = InsertNode(root, 10);
	myTree->count++;

	root = InsertNode(root, 60);
	myTree->count++;

	root = InsertNode(root, 40);
	myTree->count++;

	root = InsertNode(root, 70);
	myTree->count++;

	root = InsertNode(root, 20);
	myTree->count++;

	root = InsertNode(root, 90);
	myTree->count++;

	myTree->root = root;

	tmpNode = FindNode(40, myTree->root, isNodeFound);

	InOrderDisplay(myTree->root);

	DeleteNode(0,myTree);
	cout << endl << endl << endl;
	
	InOrderDisplay(myTree->root);
	
	
	DestroyTree(myTree);
	InOrderDisplay(myTree->root);

	return 0;
}



