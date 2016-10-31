#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _Local {
	int localNum;
	char color[10];
	char localName[10];
	int hotel;	//호텔 건설 가격 = 인수비용
	int landmark;	//랜드마크 건설 가격
	struct _Local *next;
}Local;

typedef struct _Node {
	Local *data;
	_Node *next;
}Node;

typedef struct _LinkedList {
	Local *head;
	Local *tail;
}LinkedList;

LinkedList *creatList() {
	LinkedList *list;
	list = (LinkedList*)malloc(sizeof(LinkedList));
	list->head = NULL;
	list->tail = NULL;
	return list;
}

Local *NewLocal(int num, char *color, char *name, int hotel, int landmark) {
	Local *local = (Local*)malloc(sizeof(Local));
	local->localNum = num;
	strcpy(local->color, color);
	strcpy(local->localName, name);
	local->hotel = hotel;
	local->landmark = landmark;

	return local;
}

Node *NewNode(Local *data) {
	Node *node = (Node*)malloc(sizeof(Node));
	node->data = data;
	node->next = NULL;
	return node;
}

void HangNode(LinkedList *list, Node *node) {

	if (list->head == NULL) {
		//list->head = node;
	}
}