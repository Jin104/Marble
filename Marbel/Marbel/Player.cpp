#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "player.h"
#include "local.h"


LinkedList *NewList() {
	LinkedList *list = (LinkedList*)malloc(sizeof(LinkedList));
	list->head = NewNode("");
	list->tail = NewNode("");

	list->head->next = list->tail;
	list->tail->prev = list->head;

	list->size = 0;

	return list;
}


Node *NewNode(char *local) {
	Node *node = (Node*)malloc(sizeof(Node));
	strcpy(node->local, local);
	node->next = 0;
	node->prev = 0;
	return node;
}

void insert(LinkedList *list, Node *pos, char *local) {
	Node *node = NewNode(local);
	HangNode(node, pos);
	list->size++;
}

void HangNode(Node *now, Node *pos) {
	now->prev = pos->prev;
	now->next = pos;

	pos->prev->next = now;
	pos->prev = now;
}

void PushBack(LinkedList *list, char *local) {
	insert(list, list->tail, local);
}

void Erase(LinkedList *list, Node *pos) {
	DisconnectNode(pos);
	free(pos);
	list->size--;
}

void DisconnectNode(Node *pos) {
	if (pos == NULL) {
		return;
	}
	pos->prev->next = pos->next;
	pos->next->prev = pos->prev;
}

void printList(LinkedList *list) {
	Node *prev, *pos;
	prev = pos = list->head;
	while (pos != NULL) {
		printf("%s ", pos->local);
		pos = pos->next;
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
	printf("존재하지 않습니다.\n");
	return temp;
}