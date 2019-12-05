#include "Header.h"

/*This Function insert new input to end of list*/
void insertDataToEndList(List* lst, Apartment data)
{
	ListNode* newTail;
	newTail = createNewListNode(data, NULL);
	insertNodeToEndList(lst, newTail);
}
/*This Function insert new node to end of list*/
void insertNodeToEndList(List* lst, ListNode * newTail)
{
	if (isEmptyList(*lst))
	{
		lst->head = lst->tail = newTail;
	}
	else
	{
		lst->tail->next = newTail;
		lst->tail = newTail;
	}
}
/*This Function creates new node and insert input*/
ListNode* createNewListNode(Apartment data, ListNode * next)
{
	ListNode* res;
	res = (ListNode*)malloc(sizeof(ListNode));
	res->appData = data;
	res->next = next;
	return res;
}
/*This Function makes empty list*/
void makeEmptyList(List* lst)
{
	lst->head = lst->tail = NULL;
}
/*This Function checks if list is empty*/
bool isEmptyList(List lst)
{
	return (lst.head == NULL);
}
/*This Function deletes node*/
void deleteNode(ListNode *deleteApp)
{
	ListNode *temp;
	temp = deleteApp->next;
	deleteApp->next = temp->next;
	FREE(temp);
}
/*This Function deletes head node*/
void deleteHead(List* apartments)
{
	ListNode *deleteApp = apartments->head;
	apartments->head = deleteApp->next;
	FREE(deleteApp);
	return;
}
/*This Function counts how many nodes does exist*/
int count(List apartments)
{
	ListNode * curr = apartments.head;
	if (curr == NULL)
		return 0;
	int count = 0;
	while (curr != NULL)
	{
		count++;
		curr = curr->next;
	}
	return count;
}
/*This Function gets list and FREE her memory*/
void freeList(List * lst)
{
	freeListRec(lst->head);
	lst->head = NULL;
	lst->tail = NULL;
}
void freeListRec(ListNode * node)
{
	if (node == NULL)
		return;
	freeListRec(node->next);
	FREE(node->appData.andress);
	FREE(node);
}

