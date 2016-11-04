#include "player.h"
#include "draw.h"


LinkedList *NewList() {

	LinkedList *list = (LinkedList*)malloc(sizeof(LinkedList));
	//list->head = NULL;
	//list->tail = list->head->next;

	list->head->next = list->tail;
	list->tail->prev = list->head;


	list->size = 0;

	return list;
}

Node *NewNode(char *local, int price, int num) {
	Node *node = (Node*)malloc(sizeof(Node));
	strcpy(node->local, local);
	node->price = price;
	node->num = num;
	node->next = NULL;
	return node;
}

void HangNode(LinkedList *list, Node *node) {

	if (list->head == NULL) {
		list->head = node;
		list->tail = node;
		list->size++;
		return;
	}
	
	Node *pos = list->head;

	while (pos->next != NULL) {
		pos = pos->next;
	}

	node->prev = pos;
	node->next = pos->next;

	pos->next = node;
	pos->next->prev = node;

	list->size++;

	//while (pos->next != NULL && pos->num < node->num) {
	//	pos = pos->next;
	//}
	//if (list->head == pos) {
	//	node->next = pos;
	//	pos->prev = node;
	//	list->head = node;
	//}/*
	//else if (pos->next == NULL) {
	//	node->prev = pos->prev;
	//	pos->prev->next = node;
	//	list->tail = node;
	//
	//}*/
	//else {
	//	node->prev = pos;
	//	node->next = pos->next;
	//	pos->next = node;
	//	pos->next->prev = node;
	//}
}

void deletNode(LinkedList *list, char *local) {
	Node *node = FindNode(list, local);
	
	if (node == NULL) {		//존재x
		return;
	}

	gotoxy(110, 15);
	printf("%s", node->local);

	if (node->next == NULL) {
		list->head = NULL;
		return;
	}

	/*if (node->prev == NULL) {
		node->next = NULL;
		return;
	}*/
	node->prev->next = node->next;
	node->next->prev = node->prev;
		
	free(node);
	list->size--;
}

void PrintList(LinkedList *list) {
	Node *prev, *pos;
	prev = pos = list->head;
	int i = 1;
	while (pos != NULL) {
		gotoxy(110, i);
		printf("%d %s %d\n", pos->num, pos->local,pos->price/2);
		pos = pos->next;
		i++;
	}
}

void PrintList2(LinkedList *list) {
	Node *prev, *pos;
	prev = pos = list->head;
	int i = 20;
	while (pos != NULL) {
		gotoxy(110, i);
		printf("%d %s %d", pos->num, pos->local, pos->price);
		pos = pos->next;
		i++;
	}
}

Node *FindNode(LinkedList *list, char *local) {
	Node *temp;
	temp = list->head;
	while (temp != NULL) {
		if (strcmp(temp->local, local) == 0) {
			return temp;
		}
		else {
			temp = temp->next;
		}
	}
	//printf("존재하지 않습니다.\n");
	return NULL;
}

void modifiNode(LinkedList *list, char *local, int price) {
	Node *node = FindNode(list, local);
	node->price = price;
}