//搜索二叉树->有序双向链表
//二叉搜索数 的中序遍历是非降序排列

Node* prev;

func(Node *node)
{
	node->left = prev;
	if (prev != NULL)
	{
		prev->right = node;
	}
	prev = node;
}
 
void inorder(Node* root)
{
	
	inorder(root->left);

	func(root);

	inorder(root->right);

}



//前序+中序 -> 构建二叉树
//在前序中找到根节点
//根据根节点 + 中序 ，分成左右两棵子树
//根据子树长度，把前序分成左右两棵子树
//子问题处理


typedef struct TreeNode
{
	struct TreeNode *left;
	struct TreeNode *root;
	int val;

}	TreeNode;
//#数组形式
struct Result
{
	struct TreeNode *root;	//创建出的树的结点
	int used;			//创建数的过程中使用掉的 前序遍历的个数
};
struct TreeNode *CreatTree(int *preorder, int size)
{
	int rootValue = preorder[0];
	if (rootValue == '#')
	{
		struct Result reslut
		{
			.root = NULL;
			.used = 1;
		};

		return result;
	}
	TreeNode *root  = malloc();

	struct Result left_r = CreatTree(preorder + 1, size - 1);
	struct Result right_r = CreatTree(preorder + 1 + left_r, size - 1 - left_r);
	
	root->left = left_r;
	root->root = right_r;

}


