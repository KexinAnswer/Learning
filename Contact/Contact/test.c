#define _CRT_SECURE_NO_WARNINGS 1

#include "Contact.h"

void menu()
{
	printf("***************************************\n");
	printf("***        1.Add       2.Detele     ***\n");
	printf("***        3.Search    4.Change     ***\n");
	printf("***        5.Show      6.Sort       ***\n");
	printf("***              0.Exit             ***\n");
	printf("***************************************\n");


}

void test()
{
	Contact con;

	

	Init(&con);
	int input = 0;
	
	do
	{
		menu();
		printf("请选择:>");
		scanf("%d", &input);
		switch (input)
		{
			//添加联系人
		case ADD:
			AddContact(&con);
			break;
			//删除联系人
		case DELATE:
			DelContact(&con);
			break;
			//查找联系人
		case SEARCH:
			SearchContact(&con);
			break;
			//修改联系人
		case CHANGE:
			ChangeContact(&con);
			break;
			//打印通讯率
		case SHOW:
			ShowContact(&con);
			break;
			//通讯率排序
		case SORT:
			SortContact(&con);
			break;
			//释放动态内存空间
		case EXIT:
			DistoryContact(&con);
			printf("退出程序！\n");
			break;
		default:
			printf("选择错误，请重新选择\n");
			break;
		}
	} while (input);
}


int main()
{

	test();

	system("pause");
	return 0;
}