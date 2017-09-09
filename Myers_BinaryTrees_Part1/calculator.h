//Programmer: Dawn Myers
#ifndef CALCULATOR_H
#define CALCULATOR_H
#include <fstream>
using namespace std;

#define OPERATOR 0
#define DATA 1
#define FAIL 1
#define SUCCEED 0

typedef
struct
{
	int data;
	int dataType;
} DataNode;

typedef
struct node
{
	DataNode *nodeData;
	struct node *leftChild;
	struct node *rightChild;
} TreeNode;

class calculator
{
public:
	calculator();
	~calculator();
	void mainMethod();
private:
	int scan(DataNode *data, FILE *fptr);
	TreeNode *makeTreeNode(DataNode *data);
	void insertTreeNode(TreeNode *newTreeNode, TreeNode **root);
	void inOrder(TreeNode *currentTreeNode);
	void preOrder(TreeNode *currentTreeNode);
	void postOrder(TreeNode *currentTreeNode);
	void destroyTree(TreeNode *root);
};
#endif

