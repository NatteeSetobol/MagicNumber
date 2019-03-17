#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct branch 
{
	char op;
	int number;
	struct branch *left;
	struct branch *right;
};

struct tree
{
	struct branch *root;
};


void AddNumToTree(struct branch *currentBranch, struct branch *prevBranch, int num, int direction)
{
	if (currentBranch)
	{
		if (currentBranch->right)
		{
			AddNumToTree(currentBranch->right,currentBranch,num,0);
		}
		if (currentBranch->left)
		{
			AddNumToTree(currentBranch->left,currentBranch,num,1);
		}

		if (currentBranch->left == NULL &&  currentBranch->right == NULL)
		{
			currentBranch->right = (struct branch*) malloc(sizeof(struct branch));
			currentBranch->right->number = num;
			currentBranch->right->left = NULL;
			currentBranch->right->right = NULL;
			AddNumToTree(currentBranch->left,currentBranch,num,1);
		}
	} else {
		
		if (direction == 0)
		{
			prevBranch->right = (struct branch*) malloc(sizeof(struct branch));
			prevBranch->right->number = num;
			prevBranch->right->left = NULL;
			prevBranch->right->right = NULL;
		} else {
			prevBranch->left = (struct branch*) malloc(sizeof(struct branch));
			prevBranch->left->number = num;
			prevBranch->left->left = NULL;
			prevBranch->left->right = NULL;
		}
	}
}


void AddNumber(struct tree *currentTree,int number)
{
	if (currentTree->root == NULL)
	{
		currentTree->root = (struct branch*) malloc(sizeof(struct branch));
		currentTree->root->number = number;
		currentTree->root->left = NULL;
		currentTree->root->right = NULL;
	} else {
		AddNumToTree(currentTree->root,NULL,number,0);
	}
}

void WalkTree(struct branch  *root)
{
	if (root)
	{
		if (root->left)
		{
			printf("value = %i\n", root->left->number);
			WalkTree(root->left);
		}
		if (root->right)
		{
			printf("value = %i\n", root->right->number);
			WalkTree(root->right);
		}
	}

	return ;
}


bool CalculateBranch(struct branch* b,int total,int magic_number)
{
	bool result = false;

	if (b)
	{
		if (b->right)
		{
			int newTotal = total+b->right->number;
			result = CalculateBranch(b->right,newTotal,magic_number);
		}
		if (b->left && result == false)
		{
			int newTotal = total-b->left->number;
			result = CalculateBranch(b->left,newTotal,magic_number);
		}

		if (b->left == NULL && b->right == NULL && result == false)
		{
			if (magic_number == total)
			{
				result = true;
			}
		}
	}

	return result;

}

bool CalculateTree(struct tree *t,int magic_number)
{
	bool result=false;

	result = CalculateBranch(t->root,t->root->number,magic_number);
	return result;
}

void BuildTreeByList(int numbers[],int size,struct tree  *t)
{
	for (int numberIndex = 0; numberIndex < size;numberIndex++)
	{
		AddNumber(t,numbers[numberIndex]);
	}
}


int main()
{
	int magicNumber = -12;
	struct tree numberTree = {};
	int numbers[] = { 1, 13 };

	BuildTreeByList(numbers,2,&numberTree);

	if (CalculateTree(&numberTree,magicNumber))
	{
		printf("yes!\n");
	} else {
		printf("no!\n");
	}
}



