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
		printf("��ѡ��:>");
		scanf("%d", &input);
		switch (input)
		{
			//�����ϵ��
		case ADD:
			AddContact(&con);
			break;
			//ɾ����ϵ��
		case DELATE:
			DelContact(&con);
			break;
			//������ϵ��
		case SEARCH:
			SearchContact(&con);
			break;
			//�޸���ϵ��
		case CHANGE:
			ChangeContact(&con);
			break;
			//��ӡͨѶ��
		case SHOW:
			ShowContact(&con);
			break;
			//ͨѶ������
		case SORT:
			SortContact(&con);
			break;
			//�ͷŶ�̬�ڴ�ռ�
		case EXIT:
			DistoryContact(&con);
			printf("�˳�����\n");
			break;
		default:
			printf("ѡ�����������ѡ��\n");
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