#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <cstddef>
using namespace std;

const int EMPTY_FILE = -99;
const int NUM_CHOICES = 5;
enum MENU_CHOICE { SHOW, ADD, DELETE, FIND, EXIT };
const char CHAR_CHOICES[NUM_CHOICES] = { 'S', 'A', 'D', 'F', 'E' };
const string STRING_CHOICES[NUM_CHOICES] = { "Show Nodes", "Add Nodes", "Delete Nodes",
							"Find Nodes", "Exit Program" };

const string MENU_HDR = "\n=========================================================="
	"=====================\n"
	"                           Kings Binary Trees\n"
	"                                 Main Menu\n"
	"=========================================================="
	"=====================\n";
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
void InOrderDisplay(BstNode* myTree, int& numItems)
{
	
	if (myTree != NULL)
	{
		
		InOrderDisplay(myTree->left, numItems);
		cout << setw(6) << myTree->data << " ";
		numItems++;
		if (numItems%10 == 0)
			cout << endl;
		InOrderDisplay(myTree->right, numItems);
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
	if (newNode != NULL)
	{
		newNode->data = data;
		newNode->parent = NULL;
		newNode->left = newNode->right = NULL;
	}
	else
	{
		cout << "Memory Allocation Error\n";
		newNode = NULL;
	}
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
		cout << "\nPlease free the nodes before destroying the tree!\n";
	}
}
string getFile()
{
	//Fix this shit
	ifstream inStream;

	bool isValid = false;
	string userInput;

	while (!isValid)
	{
		cin.clear();
		cout << "Please input file name of file to be read: ";
		cin >> userInput;
		inStream.open(userInput.c_str());

		if (inStream)
			isValid = true;
		else
		{
			cout << "\nFile Not Found\n";
			isValid = false;

		}
	}
	return userInput;
}
void ProcessFile(string fileName, BsTree* &myTree)
{
	BstNode* srchNode = NULL;

	int numRead = EMPTY_FILE;
	ifstream inStream;
	inStream.open(fileName.c_str());
	inStream >> numRead;
	bool nodeFound = false;
	if (numRead != EMPTY_FILE)
	{
		do
		{
			srchNode = FindNode(numRead, myTree->root, nodeFound);
			if (nodeFound)
				cout << numRead << " found in tree, " << numRead << " will be ignored.\n";
			else
			{
				myTree->root = InsertNode(myTree->root, numRead);
				myTree->count++;
			}


		} while (inStream >> numRead);
	}
}

bool isValid(char userInput, MENU_CHOICE* myChoice)
{
	bool valid = false;
	for (int a = 0; a <= NUM_CHOICES - 1; a++)
	{
		if (userInput == CHAR_CHOICES[a])
		{
			valid = true;
			*myChoice = static_cast<MENU_CHOICE>(a);
		}
			
	}
	if (!valid)
		cout << "Please make a valid selection\n";
	return valid;
}
MENU_CHOICE getMenuChoice()
{
	char userInput;
	MENU_CHOICE myChoice = EXIT;
	do
	{
		cout << "Please make a selection: ";
		cin >> userInput;
		userInput = toupper(userInput);
	}while (!isValid(userInput,&myChoice));
	
	return myChoice;
}
void ShowMenu(int numNodes)
{
	MENU_CHOICE myChoice = EXIT;
	cout << endl << setw(28) << numNodes << " total nodes in tree\n";
	cout << setw(0) << MENU_HDR;
	
	for (int a = 0; a <= NUM_CHOICES - 1; a++)
		cout << setw(30) << CHAR_CHOICES[a] << "->" << STRING_CHOICES[a] << endl;
}

void showTree(BsTree* myTree)
{
	if (!isEmpty(myTree))
	{
		int numCols = 0;
		cout << "\nValues Stored in entire binary tree are:\n";
		InOrderDisplay(myTree->root, numCols);
		cout << endl;
	}
	else
		cout << "\nTree is empty\n";
}

int getNumToMod()
{
	int userInput = 0;
	bool valid = false;
	while (!valid)
	{
		cout << "Please enter positive integer: ";
		cin >> userInput;
		if (userInput >= 0)
			valid = true;
		else
			cout << "\nPlease enter an POSITIVE integer\n";
	}
	
	return userInput;
}

void processChoice(MENU_CHOICE myChoice,BsTree* &myTree)
{
	BstNode* tmpNode = NULL;
	int numToAdd = 0;
	int numToDel = 0;
	int numToFind = 0;
	int numItems = 0; //For InOrderDisplay recursive funciton.
	bool numFound = false;

	switch (myChoice)
	{
	case SHOW:
		showTree(myTree);
		
		break;
	case ADD:
		numToAdd = getNumToMod();
		FindNode(numToAdd, myTree->root, numFound); 
		if (!numFound)
		{
			myTree->root = InsertNode(myTree->root, numToAdd);
			myTree->count++;
			cout << numToAdd << " Added to binary tree\n";
		}
		else
			cout << endl << numToAdd << " already in binary tree ignoring input\n";
		break;

	case DELETE:
		numToDel = getNumToMod();
		FindNode(numToDel, myTree->root, numFound);
		if (numFound)
		{
			DeleteNode(numToDel, myTree);
			myTree->count--;
		}
		else
		{
			cout << "\nCant delete " << numToDel << ", its not found in binary tree!\n";
		}
		break;

	case FIND:
		numToFind = getNumToMod();
		tmpNode = FindNode(numToFind, myTree->root, numFound);
		if (numFound)
		{
			cout << "\nValues stored in subtree with  " << numToFind  << " as root " << endl;
			InOrderDisplay(tmpNode, numItems);

		}
		break;
		
	case EXIT:
		FreeNodes(myTree);
		DestroyTree(myTree);
		cout << "Good-Bye\n";
		break;
	}

}



int main(int argc, char* argv[])
{
	string fileName;
	ifstream inStream;
	BsTree* myTree = CreateTree();
	MENU_CHOICE myChoice = EXIT;
	//fileName = "Text.txt";
	fileName = getFile();
	ProcessFile(fileName, myTree);
	do {
		ShowMenu(myTree->count);
		myChoice = getMenuChoice();
		processChoice(myChoice, myTree);
	} while (myChoice != EXIT);
	return 0;
}


