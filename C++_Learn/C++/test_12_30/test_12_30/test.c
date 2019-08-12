
//ÄæÖÃµ¥Á´±í
ListNode* reverseList(ListNode *head)
{
	ListNode* cur = head;
	ListNodd* ret = NULL;

	for (cur = head; cur != NULL; cur = cur ->next) 
	{
		cur->next = ret;
		ret = cur;
	}
	retrurn ret;
}

ListNode* mergeOrderList(ListNode* headA, ListNode* headB)
{
	ListNode* ret = headA;
	while (headA != NULL)
	{
		headA = headA->next;
	}
	headA = headB;

	retuen ret;
}
typedf struct ListNode {
	int value;
	struct ListNode *next;
}	ListNode;