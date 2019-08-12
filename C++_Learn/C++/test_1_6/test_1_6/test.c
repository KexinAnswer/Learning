#include <stdio.h>


struct TreeNode {
	int val;
	struct TreeNode *left;
	struct TreeNode *right;
};

int max(int a, int b)
{
	return a > b ? a : b;
}

int maxDepth(struct TreeNode *root)
{
	if (root == NULL)
	{
		return 0;
	}

	return max(maxDepth(root->left), maxDepth(root->right)) + 1;
	
}

void postorderTraversal(struct TreeNode *root)
{
	if (root == NULL)
	{
		return;
	}

	postorderTraversal(root->left);
	postorderTraversal(root->right);
	printf("%d ", root->val);
}

//struct TreeNode* lowestCommonAbcestor(struct TreeNode *root, struct TreeNode *p, struct TreeNode *q)
//{
//	if (root = NULL)
//	{
//		return NULL;
//	}
//	
//	if (root->left == p || root->right == p)
//	{
//		return root;
//	}
//
//	lowestCommonAbcestor(roo t->left, p, q);
//	lowestCommonAbcestor(root->right, p, q);
//
//
//
//}

bool Search(struct TreeNode *root, int val)
{
	if (root->val == val)
		return true;
	return false;
}
struct TreeNode * Find(struct TreeNode *root, int val)
{
	if (root == NULL)
	{
		return NULL;
	}
	if (root->val == val)
	{
		return root;
	}

	
	struct TreeNode *left = Find(root->left,val);
	if (left != NULL)
	{
		return left;
	}
	struct TreeNode *right = Find(root->left, val);
	if (right != NULL)
	{
		return right;
	}
	else
	{
		return NULL;
	}
}


