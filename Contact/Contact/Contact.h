#ifndef __CONTACT_H__
#define __CONTACT_H__

//通讯录
//功能（Function）
//1. Add
//2. Delate
//3. Search
//4. Change
//5. Show
//6. Sort
//存储信息
//姓名—char
//性别—char
//年龄—int
//电话—char
//住址—char

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#define MAX_NAME 20
#define MAX_SEX 5
//#define MAX_AGE 4
#define MAX_TELE 12
#define MAX_ADDR 30
//#define MAX 5

enum Function
{
	EXIT,//0
	ADD,//1
	DELATE,//2
	SEARCH,//3
	CHANGE,//4
	SHOW,//5
	SORT//6
};

typedef struct PeoInfo
{
	char name[MAX_NAME];
	char sex[MAX_SEX];
	int age;
	char tele[MAX_TELE];
	char addr[MAX_ADDR];

}PeoInfo;

typedef struct Contact
{
	struct PeoInfo* data;
	int sz;
	int capacity;
}Contact;

void Init(Contact* con);
void AddContact(Contact* con);
void DelContact(Contact* con);
void ShowContact(const Contact* con);
void SearchContact(const Contact* con);
void ChangeContact(Contact* con);
void SortContact(Contact* con);
void DistoryContact(Contact* con);
void SaveContact(Contact* con);
void LoadContact(Contact* con);




#endif __CONTACT_H__