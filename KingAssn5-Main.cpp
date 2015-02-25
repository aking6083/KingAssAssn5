/*****************************************************************************
// CODE FILENAME: KingAssn5.cpp
//	DESCRIPTION: Program to test binary tree structure.  Tree structure is loaded
//				from text file input by user.  The input text file will be space 
//				delimted integers less than or equal to 9999.  User will be 
//				presented with a menu of actions to perform on tree.  
//				MENU:
//				S->Show Tree ~ will show the entire binary tree formatted.
//				A->Add Nodes ~ will add a user proivded node to tree
//				D->Delete Nodes ~ will delete user provided node from tree
//				F->Find Nodes ~ Finds and shows the tree associated with user 
//								provided integer.
//	CLASS/TERM: CS372/SP8W1
//	DESIGNER: Adam King
//	FUNCTIONS: bool isEmpty(BsTree* myTree);
//	//Displays formatted sorted binary tree		
//	void InOrderDisplay(BstNode* myTree, int& numItems); 
//	BstNode* CreateNode(int data); ~Creates a node to add to binary tree
//	BsTree * CreateTree(); ~Creates the tree
//	BstNode* InsertNode(BstNode* rootPtr, int data); ~Inserts node to tree
//  ~Finds and returns node from tree
//	BstNode * FindNode(int data, BstNode* myTree, bool& found);
//	void DeleteFromTree(BstNode* &myTree); //Delete node from tree
//	void DeleteNode(int dataToDel, BsTree* &myTree); Delete a node
//	void FreeNodes(BsTree* &myTree); //Recursivley free nodes in a tree
//	void DestroyTree(BsTree* &myTree); //Destroy or de-allocate the tree
//	string getFile(); //Gets and validates the file from the user
//	void ProcessFile(string fileName, BsTree* &myTree); //Loads the binary tree
//	bool isValid(char userInput, MENU_CHOICE* myChoice); //Error Check for input
//	MENU_CHOICE getMenuChoice(); //Gets the menu choice from the user
//	void ShowMenu(int numNodes); //Shows menu to user
//	void showTree(BsTree* myTree); //for formatting
//	int getNumToMod(); //Get number to add delete or search
//  ~Process the users menu choice
//	void processChoice(MENU_CHOICE myChoice,BsTree* &myTree);
*****************************************************************************/

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <cstddef>
using namespace std;

const int EMPTY_FILE = -99; //File Empty Error code
const int NUM_CHOICES = 5; //Number of choice available to user
enum MENU_CHOICE { SHOW, ADD, DELETE, FIND, EXIT }; //enum of menu choices
//char array of menu choices
const char CHAR_CHOICES[NUM_CHOICES] = { 'S', 'A', 'D', 'F', 'E' }; 
//string array of menu choices
const string STRING_CHOICES[NUM_CHOICES] = { "Show Nodes", "Add Nodes", "Delete Nodes",
							"Find Nodes", "Exit Program" };

//Menu Header
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

//Binary search tree
struct BsTree {
	BstNode* root;
	int count;
};


//prototypes
bool isEmpty(BsTree* myTree);
void InOrderDisplay(BstNode* myTree, int& numItems);
BstNode* CreateNode(int data);
BsTree * CreateTree();
BstNode* InsertNode(BstNode* rootPtr, int data);
BstNode * FindNode(int data, BstNode* myTree, bool& found);
void DeleteFromTree(BstNode* &myTree);
void DeleteNode(int dataToDel, BsTree* &myTree);
void FreeNodes(BsTree* &myTree);
void DestroyTree(BsTree* &myTree);
string getFile();
void ProcessFile(string fileName, BsTree* &myTree);
bool isValid(char userInput, MENU_CHOICE* myChoice);
MENU_CHOICE getMenuChoice();
void ShowMenu(int numNodes);
void showTree(BsTree* myTree);
int getNumToMod();
void processChoice(MENU_CHOICE myChoice,BsTree* &myTree);

//*****************************************************************************
// FUNCTION: main
// DESCRIPTION: Driver function for program, directs traffic
// INPUT: command line arguments (not used)
// Parameters: 
// File: 
// OUTPUT:
// Return Val: 0 for sucess
// Parameters: 
// CALLS TO: CreateTree(),getFile(),ProcessFile(),ShowMenu(),getMenuChoice,
//			 processChoice(),
//*****************************************************************************
int main(int argc, char* argv[])
{
	string fileName;
	ifstream inStream;
	BsTree* myTree = CreateTree();
	MENU_CHOICE myChoice = EXIT;
	fileName = getFile();
	ProcessFile(fileName, myTree);
	do {
		ShowMenu(myTree->count);
		myChoice = getMenuChoice();
		processChoice(myChoice, myTree);
	} while (myChoice != EXIT);
	return 0;
}


//*****************************************************************************
// FUNCTION: InOrderDisplay
// DESCRIPTION: Shows the sorted binary tree
// INPUT:
// Parameters: int& numItems ~ for column formatting on recursive call
//			   BstNode* myTree ~ pointer to root in tree being passed
// OUTPUT:     
// Parameters: int& numItems ~ for column formatting on recursive call
// CALLS TO: InOrderDisplay()
//*****************************************************************************
void InOrderDisplay(BstNode* myTree, int& numItems)
{
	if (myTree != NULL)
	{
		InOrderDisplay(myTree->left, numItems); //Show lower 
		cout << setw(6) << myTree->data << " ";
		numItems++;
		if (numItems%10 == 0)//Column formatting
			cout << endl;
		InOrderDisplay(myTree->right, numItems); //Show upper
	}
}

//*****************************************************************************
// FUNCTION: CreateNode
// DESCRIPTION: Allocates new node for storage in binary search tree
// INPUT:
// Parameters: int data ~ data to be added
// File: 
// OUTPUT:
// Return Val: BstNode* newNode ~ ptr to newly created node.
//*****************************************************************************
BstNode* CreateNode(int data)
{
	BstNode* newNode = new BstNode();
	//Set new node
	if (newNode != NULL)
	{
		newNode->data = data;
		newNode->parent = NULL;
		newNode->left = newNode->right = NULL;
	}
	else //Error
	{
		cout << "Memory Allocation Error\n";
		newNode = NULL;
	}
	return newNode;

}

//*****************************************************************************
// FUNCTION: CreateTree
// DESCRIPTION: ~Creates the binary tree and inits all values to NULL and 0
// OUTPUT:
// Return Val: BsTree* newTree ~ pointer to newly created binary search tree.
// Parameters: 
// CALLS TO: 
//*****************************************************************************
BsTree * CreateTree()
{
	BsTree* newTree = new (nothrow)BsTree;
	if (newTree)
	{
		newTree->root = NULL;
		newTree->count = 0;
	}
	else //Error
	{
		cout << "Memory Allocation Error\n";
	}
	return newTree;
}
//*****************************************************************************
// FUNCTION: InsertNode
// DESCRIPTION: ~Inserts new node to binary search tree
// INPUT:
// Parameters: BstNode* rootPtr ~ pointer to root of tree
// OUTPUT:
// Return Val: rootPtr new root pointer
// Parameters: 
// CALLS TO: CreateNode,InsertNode,
//*****************************************************************************
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

//*****************************************************************************
// FUNCTION: FindNode
// DESCRIPTION: Finds and returns address of requested node
// INPUT:
// Parameters: int data ~ data to be found
//				BstNode* myTree ~ pointer to tree root
//				bool &found ~ was the node found
// OUTPUT:
// Return Val: BstNode* address of new node
// CALLS TO: FindNode()
//*****************************************************************************
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

//*****************************************************************************
// FUNCTION: DeleteFromTree
// DESCRIPTION: ~ Deletes a node from the tree
// INPUT:
// Parameters: BstNode* &myTree ~ pointer to tree root
// OUTPUT:
// Return Val: 
// Parameters: BstNode* &myTree
// CALLS TO: 
//*****************************************************************************
void DeleteFromTree(BstNode* &myTree)  //Change to node.
{
	BstNode* current; //current node
	BstNode* trailCurrent; //Node prior to current node
	BstNode* temp; //Temp node for storage

	if (myTree == NULL)
		cout << "Node delete error\n";
	else if (myTree->left == NULL && myTree->right == NULL) //If root
	{
		temp = myTree;
		myTree = NULL;
		delete temp;
	}
	else if (myTree->left == NULL) //Left side
	{
		temp = myTree;
		myTree = temp->right;  //Move it around
		delete temp;
	}
	else if (myTree->right == NULL)//Right side
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
//*****************************************************************************
// FUNCTION: DeleteNode
// DESCRIPTION: ~Searches and deletes node from root
// INPUT:
// Parameters: int dataToDel ~ data to be removed from tree
//			   BsTree* &myTree ~ Binary Search Tree
// File: 
// OUTPUT:
// Return Val: 
// Parameters: BsTree* &myTree ~ modified tree
// CALLS TO: DeleteFromTree()
//*****************************************************************************
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
			if (current == myTree->root) //Is it here
				DeleteFromTree(myTree->root);
			else if (trailCurrent->data > dataToDel) //Is it here
				DeleteFromTree(trailCurrent->left);
			else
				DeleteFromTree(trailCurrent->right);
		}
	}
}
//*****************************************************************************
// FUNCTION: 
// DESCRIPTION: 
// INPUT:
// Parameters: 
// File: 
// OUTPUT:
// Return Val: 
// Parameters: 
// CALLS TO: 
//*****************************************************************************

void FreeNodes(BsTree* &myTree)
{
	if (!isEmpty(myTree))
	{
		DeleteFromTree(myTree->root);
		FreeNodes(myTree);
	}
}
//*****************************************************************************
// FUNCTION: 
// DESCRIPTION: 
// INPUT:
// Parameters: 
// File: 
// OUTPUT:
// Return Val: 
// Parameters: 
// CALLS TO: 
//*****************************************************************************

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
//*****************************************************************************
// FUNCTION: 
// DESCRIPTION: 
// INPUT:
// Parameters: 
// File: 
// OUTPUT:
// Return Val: 
// Parameters: 
// CALLS TO: 
//*****************************************************************************

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
//*****************************************************************************
// FUNCTION: 
// DESCRIPTION: 
// INPUT:
// Parameters: 
// File: 
// OUTPUT:
// Return Val: 
// Parameters: 
// CALLS TO: 
//*****************************************************************************

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

//*****************************************************************************
// FUNCTION: 
// DESCRIPTION: 
// INPUT:
// Parameters: 
// File: 
// OUTPUT:
// Return Val: 
// Parameters: 
// CALLS TO: 
//*****************************************************************************

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
//*****************************************************************************
// FUNCTION: 
// DESCRIPTION: 
// INPUT:
// Parameters: 
// File: 
// OUTPUT:
// Return Val: 
// Parameters: 
// CALLS TO: 
//*****************************************************************************

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
//*****************************************************************************
// FUNCTION: 
// DESCRIPTION: 
// INPUT:
// Parameters: 
// File: 
// OUTPUT:
// Return Val: 
// Parameters: 
// CALLS TO: 
//*****************************************************************************

void ShowMenu(int numNodes)
{
	MENU_CHOICE myChoice = EXIT;
	cout << endl << setw(28) << numNodes << " total nodes in tree\n";
	cout << setw(0) << MENU_HDR;
	
	for (int a = 0; a <= NUM_CHOICES - 1; a++)
		cout << setw(30) << CHAR_CHOICES[a] << "->" << STRING_CHOICES[a] << endl;
}

//*****************************************************************************
// FUNCTION: 
// DESCRIPTION: 
// INPUT:
// Parameters: 
// File: 
// OUTPUT:
// Return Val: 
// Parameters: 
// CALLS TO: 
//*****************************************************************************

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

//*****************************************************************************
// FUNCTION: 
// DESCRIPTION: 
// INPUT:
// Parameters: 
// File: 
// OUTPUT:
// Return Val: 
// Parameters: 
// CALLS TO: 
//*****************************************************************************

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

//*****************************************************************************
// FUNCTION: 
// DESCRIPTION: 
// INPUT:
// Parameters: 
// File: 
// OUTPUT:
// Return Val: 
// Parameters: 
// CALLS TO: 
//*****************************************************************************

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
			cout << "Deleted " << numToDel << endl;
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
//*****************************************************************************
// FUNCTION: 
// DESCRIPTION: 
// INPUT:
// Parameters: 
// File: 
// OUTPUT:
// Return Val: 
// Parameters: 
// CALLS TO: 
//*****************************************************************************

bool isEmpty(BsTree* myTree)
{
	bool isEmpty = false;

	if (myTree->root == NULL)
		isEmpty = true;

	return isEmpty;
}
