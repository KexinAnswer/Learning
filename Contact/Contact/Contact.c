#define _CRT_SECURE_NO_WARNINGS 1

#include "Contact.h"

void CheckCapacity(Contact* con)
{
	//relloc void* 需要有指针接受
	//relloc()中，第二个参数是新的内存空间
	PeoInfo *ptr = realloc(con->data, (con->capacity + 2) * sizeof(PeoInfo));
	if (ptr == NULL)
	{
		printf("%s\n", strerror(errno));
		return;
	}
	else
	{
		con->data = ptr;
		con->capacity += 2;
		printf("增容成功！\n");
	}
}



int FindSign(const Contact* con,char* name)
{
	int i = 0;

	for (i = 0; i < con->sz; i++)
	{
		if (strcmp  (con->data[i].name,name) == 0)
		{
			return i;
		}
	}

	return -1;

}

void Init(Contact* con)
{
	
	//开辟动态内存空间
	PeoInfo* ptr = (PeoInfo*)malloc(2 * sizeof(PeoInfo));
	if (ptr == NULL)
	{
		printf("%s\n", strerror(errno));
		return;
	}
	con->data = ptr;

	//初始化结构体数组
	memset(con->data, 0,sizeof(con->data));
	//初始化通讯录数量
	con->sz = 0;
	//初始化容量
	con->capacity = 2;
	LoadContact(con);
}

void AddContact(Contact* con)
{
	assert(con != NULL);
	//判断动态内存是否够用
	if (con->sz == con->capacity)
	{
		CheckCapacity(con);
	}

	//输入信息
	printf("请输入姓名:>");
	scanf("%s", &(con->data[con->sz].name));
	
	printf("请输入性别:>");
	scanf("%s", &(con->data[con->sz].sex));

	printf("请输入年龄:>");
	scanf("%d", &(con->data[con->sz].age));

	printf("请输入电话:>");
	scanf("%s", &(con->data[con->sz].tele));

	printf("请输入地址:>");
	scanf("%s", &(con->data[con->sz].addr));

	con->sz++;

		
	printf("添加成功！\n");

}

void DelContact(Contact* con)
{

	char name[MAX_NAME] = { 0 };
	int pos = 0;
	int j = 0;
	
	assert(con != NULL);

	printf("请输入要删除的姓名:>");
	scanf("%s", &name);

	pos = FindSign(con, name);

	if (-1 == pos)
	{
		printf("没有您要删除的信息\n");
		return;
	}
	else
	{
		for (j = pos; j < con->sz - 1; j++)
		{
			con->data[j] = con->data[j + 1];
		}
		con->sz--;
		printf("删除成功！\n");
	}
}

void ShowContact(const Contact* con)
{
	int i = 0;
	printf("%10s\t%5s\t%5s\t%12s\t%20s\n","姓名","性别","年龄","电话","地址");
	for (i = 0; i < con->sz; i++)
	{
		printf("%10s\t%5s\t%5d\t%12s\t%20s\n", con->data[i].name, con->data[i].sex, con->data[i].age, con->data[i].tele, con->data[i].addr);

	}
}

void SearchContact(const Contact* con)
{
	char name[MAX_NAME] = { 0 };
	int pos = 0;

	assert(con != NULL);

	printf("请输入要查找的姓名:>");
	scanf("%s", &name);

	pos = FindSign(con, name);

	if (-1 == pos)
	{
		printf("没有您要查找的信息\n");
		return;
	}
	else
	{
		printf("%10s\t%5s\t%5s\t%12s\t%20s\n", "姓名", "性别", "年龄", "电话", "地址");
		
		printf("%10s\t%5s\t%5d\t%12s\t%20s\n", con->data[pos].name, con->data[pos].sex, con->data[pos].age, con->data[pos].tele, con->data[pos].addr);

	}
}

void ChangeContact(Contact* con)
{
	char name[MAX_NAME] = { 0 };
	int pos = 0;

	assert(con != NULL);

	printf("请输入要修改人信息的姓名:>");
	scanf("%s", &name);

	pos = FindSign(con, name);

	if (-1 == pos)
	{
		printf("没有找到您要修改的信息\n");
		return;
	}
	else
	{
		printf("请输入姓名:>");
		scanf("%s", &(con->data[pos].name));

		printf("请输入性别:>");
		scanf("%s", &(con->data[pos].sex));

		printf("请输入年龄:>");
		scanf("%d", &(con->data[pos].age));

		printf("请输入电话:>");
		scanf("%s", &(con->data[pos].tele));

		printf("请输入地址:>");
		scanf("%s", &(con->data[pos].addr));

		printf("修改成功！\n");
	}
}


void SortContact(Contact* con)
{

	int i = 0;
	int j = 0;
	int flag = 1;
	PeoInfo tmp;
	for (i = 0; i < con->sz - 1; i++)
	{
		for (j = 0; j < con->sz - i - 1; j++)
		{
			if (strcmp(con->data[j].name , con->data[j + 1].name) > 0 )
			{
				tmp = con->data[j];
				con->data[j] = con->data[j + 1];
				con->data[j + 1] = tmp;
				flag = 0;
			}
			
		}
		if (flag == 1)
		{
			return;
		}
	}
	printf("排序成功！\n");

}

void DistoryContact(Contact* con)
{
	free(con->data);
	con->data = NULL;
	con->capacity = 0;
	con->sz = 0;
	printf("释放内存成功\n");
}

void SaveContact(Contact* con)
{
	int i = 0;
	FILE* pfOut = fopen("Contact.dat", "wb");
	if (pfOut == NULL)
	{
		perror("File a txt for write ");
		system("pause");
		return;
	}
	for (i = 0; i < con->sz; i++)
	{
		fwrite(con->data + i, sizeof(PeoInfo), 1, pfOut);
		i++;
	}

	fclose(pfOut);
	pfOut = NULL;
	printf("保存成功\n");
}

void LoadContact(Contact* con)
{
	int ret = 0;
	PeoInfo tmp;
	FILE* pfIn = fopen("Contact.dat", "rb");
	if (pfIn == NULL)
	{
		perror("File a txt for read ");
		system("pause");
		return;
	}
	while (fread(&tmp, sizeof(PeoInfo), 1, pfIn))
	{
		
		if (con->sz == con->capacity)
		{
			CheckCapacity(con);
		}
		con->data[con->sz] = tmp;
		con->sz++;
	}

	fclose(pfIn);
	pfIn = NULL;
}