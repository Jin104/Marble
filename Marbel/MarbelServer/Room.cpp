#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "Room.h"

int count = 1;
LinkedList *NewList() {

	LinkedList *list = (LinkedList*)malloc(sizeof(LinkedList));
	list->head = NULL;
	list->tail = NULL;

	list->size = 0;
	return list;
}

Node *NewNode(char *name, char *allNum, int num, char *ip, char *innerIp) {

	Node *node = (Node*)malloc(sizeof(Node));
	strcpy(node->name, name);
	strcpy(node->allNum, allNum);
	node->num = num;
	strcpy(node->ip, ip);
	strcpy(node->innerIp, innerIp);
	node->number = count++;
	node->next = NULL;
	node->prev = NULL;

	return node;
}

void HangNode(LinkedList *list, Node *node) {

	if (list->head == NULL) {
		list->head = node;
		list->tail = node;
		list->size++;
		return;
	}

	Node *pos;
	pos = list->head;

	while (pos->next != NULL) {
		pos = pos->next;
	}

	pos->next = node;
	node->prev = pos;
	list->tail = node;

	/*if (pos!=0) {
	if (list->head == pos) {
	node->next = list->head;
	list->head->prev = node;
	list->head = node;
	}
	else {
	node->prev = pos->prev;
	node->next = pos;
	pos->prev->next = node;
	pos->prev = node;
	}
	}
	else {
	list->tail->next = node;
	node->prev = list->tail;
	list->tail = node;
	}*/
	list->size++;

}

/*노드 삭제*/
void DeletNode(LinkedList *list, Node *node) {

	//Node *node = FindNode(list, pos);

	if (node == NULL) {      //해당노드가 없을때
		return;
	}

	/*노드의 전노드가 없을때*/
	if (node->prev != NULL) {
		node->prev->next = node->next;
	}
	else {
		list->head = list->head->next;
	}

	/*노드의 다음노드가 없을때*/
	if (node->next != NULL) {
		node->next->prev = node->prev;
	}
	else {
		list->tail = list->tail->prev;
	}

	free(node);
	count--;
	list->size--;
}

/*리스트 출력*/
void PrintList(LinkedList *list) {
	Node *prev, *pos;
	prev = pos = list->head;
	while (pos != NULL) {
		printf("%s인용\t방 이름: %s\n", pos->allNum, pos->name);
		pos = pos->next;
	}
}

/*노드 검색*/
Node *FindNode(LinkedList *list, int num) {
	Node *temp;
	temp = list->head;
	while (temp != NULL) {
		if (temp->number == num) {      //노드를 발견하면
			return temp;
		}
		else {
			temp = temp->next;
		}
	}
	return NULL;
}

void modiNode(LinkedList *list, Node *node) {

	node->num++;

}

void modiNum(LinkedList *list) {

	Node *pos = list->head;
	while (pos != NULL) {
		pos->number--;
		pos = pos->next;
	}

}