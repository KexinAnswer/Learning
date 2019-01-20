//力扣第二题 求两个数的和（链表问题）

//definition for singly - linked list.
//struct listnode {
//    int val;
//    struct listnode *next;
//};
// 
//
//int length(struct listnode *list)
//{
//	int count = 0;
//	while (list != null)
//	{
//		count++;
//		list = list->next;
//	}
//	return count;
//}
//
//struct listnode* addtwonumbers(struct listnode* l1, struct listnode* l2) {
//
//	int length = length(l1);
//	struct listnode *l3 = (struct listnode*) malloc(sizeof(struct listnode)*length);
//	struct listnode *cur1 = l1;
//	struct listnode *cur2 = l2;
//	struct listnode *ret = l3;
//
//	while (cur1 != null || cur2 != null)
//	{
//		l3 = (cur1->val + cur2->val) % 10;
//
//		cur1 = cur1->next;
//		cur2 = cur2->next;
//		l3 = l3->next;
//	}
//
//	l3->next = null;
//
//	return ret;
//}