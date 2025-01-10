/* Assignment: 4
Authors: Maor Atar, ID: 318301231
		  Guy Ezra, ID: 207329509
*/
#define _CRT_SECURE_NO_WARNINGS
#include "LinkedList.h"

/*=================================================================*/
void PrintList(LinkedList* list)
/* Function to print a Linked List */
{
	LinkedList* temp = list;
	while (temp != NULL) {
		printf("\t%s\n", temp->data);
		temp = temp->next;
	}
}
/*=================================================================*/
LinkedList* BuildNode(char* data)
/* Function to create a Linked List*/
{
	LinkedList* newList = (LinkedList*)malloc(sizeof(LinkedList));
	if (newList == NULL) { // Condition for failed allocated memory attempt
		printf("Memory allocation failed");
		exit(1);
	}
	newList->data = (char*)malloc((strlen(data) + 1) * sizeof(char));
	strcpy(newList->data, data);
	newList->next = NULL;
	return newList;
}
/*=================================================================*/
LinkedList* addToStart(LinkedList* list, char* data)
/* Function to add a new element into the head of the list */
{
	LinkedList* newList = BuildNode(data);
	newList->next = list;
	return newList;
}
/*=================================================================*/
LinkedList* addToEND(LinkedList* list, char* data)
/* Function to add a new element into the tail of the list */
{
	if (list == NULL) {
		return BuildNode(data);
	}
	LinkedList* tempList = list;
	while (tempList->next != NULL) {
		tempList = tempList->next;
	}
	tempList->next = BuildNode(data);
	return list;
}
/*=================================================================*/
LinkedList* FreeList(LinkedList* list)
/* Function to free memory of a given list*/
{
	if (list == NULL) { return NULL; }
	LinkedList* tempList;
	while (list != NULL) {
		tempList = list;
		list = list->next;
		free(tempList);
	}
	printf("List Freed Successfully");
	return NULL;
}
/*=================================================================*/
LinkedList* DeleteElement(LinkedList* list, char* data)
/* Function to delete a given element from a given list */
{
	LinkedList* prev = list, *curr = list->next;
	if (list == NULL || data == NULL)
		return NULL;
	if (strcmp(list->data, data) == 0)
	{
		LinkedList* tempList = list;
		list = list->next;
		free(tempList);
		printf("'%s' Deleted Successfully From The List\n", data);
		return list;
	}
	while (prev != NULL)
	{
		if (strcmp(prev->data, data) == 0)
			break;
		curr = prev;
		prev = prev->next;
	}
	if (prev != NULL)
		curr->next = prev->next;
	free(prev);
	printf("'%s' Deleted Successfully From The List\n", data);
	return list;
}
/*=================================================================*/
int isInList(LinkedList* list, char* data)
/* Function to check if a given element is in the given list */
{
	LinkedList* tempList = list;
	int flag = 0;
	while (flag == 0 && tempList != NULL) {
		if (strcmp(data, tempList->data) == 0)
			flag = 1;
		tempList = tempList->next;
	}
	return flag;
}