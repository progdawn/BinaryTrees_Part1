//Programmer: Dawn Myers
#include "calculator.h"
#include <iostream>
using namespace std;

calculator::calculator()
{
}


calculator::~calculator()
{
}

void calculator::mainMethod()
{
	DataNode *node = NULL;
	TreeNode *newTreeNode = NULL;
	TreeNode *root = NULL;

	int resultCode;

	cout << "Enter single-digit expression (Example: 3 + 2 / 1 * 4) >> ";

	node = (DataNode*)malloc(sizeof(DataNode)); //allocate memory for data node

	while (resultCode = scan(node, stdin) != EOF)
	{
		newTreeNode = makeTreeNode(node);
		insertTreeNode(newTreeNode, &root);

		node = (DataNode*)malloc(sizeof(DataNode));
	}

	cout << endl;

	cout << "In Order traversal: ";
	inOrder(root);
	cout << endl;

	cout << "Pre Order traversal: ";
	preOrder(root);
	cout << endl;

	cout << "Post Order traversal: ";
	postOrder(root);
	cout << endl;

	destroyTree(root);

	cin.ignore();
}

TreeNode* calculator::makeTreeNode(DataNode *data)
{
	TreeNode *newptr = NULL;

	if ((newptr = (TreeNode *)malloc(sizeof(TreeNode))) != (TreeNode *)NULL)
	{
		newptr->nodeData = data;
		newptr->leftChild = (TreeNode *)NULL;
		newptr->rightChild = (TreeNode *)NULL;
	}

	return (newptr);
}

void calculator::insertTreeNode(TreeNode *newTreeNode, TreeNode **root)
{
	if (*root == (TreeNode*)NULL)
		*root = newTreeNode;
	else
	{
		switch (newTreeNode->nodeData->dataType)
		{
			case OPERATOR:
				newTreeNode->leftChild = *root;
				*root = newTreeNode;
				break;
			case DATA:
				(*root)->rightChild = newTreeNode;
				break;
			default:
				break;
		}
	}
	return;
}

void calculator::destroyTree(TreeNode *root)
{
	if (root != NULL)
	{
		destroyTree(root->leftChild);
		destroyTree(root->rightChild);
		
		if (root->leftChild != NULL)
			root->leftChild = NULL;
		if (root->rightChild != NULL)
			root->rightChild = NULL;

		delete root;
	}
}

void calculator::inOrder(TreeNode *currentTreeNode)
{
	int nodeValue = 0;
	int leftValue = 0;
	int rightValue = 0;

	if (currentTreeNode != NULL)
	{
		inOrder(currentTreeNode->leftChild);

		if (currentTreeNode->nodeData->dataType == OPERATOR)
			cout << (char)currentTreeNode->nodeData->data;
		else
			cout << currentTreeNode->nodeData->data;

		inOrder(currentTreeNode->rightChild);
	}
}

void calculator::preOrder(TreeNode *currentTreeNode)
{
	int nodeValue = 0;
	int leftValue = 0;
	int rightValue = 0;

	if (currentTreeNode != NULL)
	{
		if (currentTreeNode->nodeData->dataType == OPERATOR)
			cout << (char)currentTreeNode->nodeData->data;
		else
			cout << currentTreeNode->nodeData->data;

		preOrder(currentTreeNode->leftChild);
		preOrder(currentTreeNode->rightChild);
	}
}

void calculator::postOrder(TreeNode *currentTreeNode)
{
	int nodeValue = 0;
	int leftValue = 0;
	int rightValue = 0;

	if (currentTreeNode != NULL)
	{
		postOrder(currentTreeNode->leftChild);
		postOrder(currentTreeNode->rightChild);
		
		if (currentTreeNode->nodeData->dataType == OPERATOR)
			cout << (char)currentTreeNode->nodeData->data;
		else
			cout << currentTreeNode->nodeData->data;
	}

}


int calculator::scan(DataNode *node, FILE *fptr)
{
	char c = 0;
	int resultCode = SUCCEED;
	
	while (isspace(c = (char)fgetc(fptr)) && (c != '\n')); //eat the whitespace

	switch (c)
	{
	case '+': case '-':
	case '*': case '/':
		(*node).dataType = OPERATOR;
		(*node).data = c; //resultCode = SUCCEED as it is initialized
		break;

	case '0': case '1':
	case '2': case '3':
	case '4': case '5':
	case '6': case '7':
	case '8': case '9':
		(*node).dataType = DATA;
		(*node).data = c - '0'; //resultCode = SUCCEED as it is initialized
		break;

	case '\n':
	case EOF:
		(*node).data = 0;
		resultCode = EOF;
		break;

	default:
		(*node).data = c;
		resultCode = FAIL;
		break;
	}

	return resultCode;
}
