//����������->����˫������
//���������� ����������Ƿǽ�������

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



//ǰ��+���� -> ����������
//��ǰ�����ҵ����ڵ�
//���ݸ��ڵ� + ���� ���ֳ�������������
//�����������ȣ���ǰ��ֳ�������������
//�����⴦��


typedef struct TreeNode
{
	struct TreeNode *left;
	struct TreeNode *root;
	int val;

}	TreeNode;
//#������ʽ
struct Result
{
	struct TreeNode *root;	//�����������Ľ��
	int used;			//�������Ĺ�����ʹ�õ��� ǰ������ĸ���
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


