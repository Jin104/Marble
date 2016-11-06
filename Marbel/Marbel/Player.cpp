#include "Player.h"
#include "Draw.h"


LinkedList *NewList() {

	LinkedList *list = (LinkedList*)malloc(sizeof(LinkedList));
	list->head = NULL;
	list->tail = NULL;
	
	list->size = 0;
	list->size2 = 0;

	return list;
}

Node *NewNode(char *local, int price, int num) {
	Node *node = (Node*)malloc(sizeof(Node));
	strcpy(node->local, local);
	node->price = price;
	node->num = num;
	node->next = NULL;
	node->prev = NULL;
	return node;
}

void HangNode(LinkedList *list, Node *node) {

	if (list->head == NULL) {	//비어있을때
		list->head = node;
		list->tail = node;
		list->size++;
		return;
	}
	
	Node *pos = list->head;
	
	while (pos != NULL && pos->num < node->num) {
		pos = pos->next;
	}
	if (pos) {
		if (list->head == pos) {		//맨앞에 매달때
			node->next = list->head;
			list->head->prev = node;
			list->head = node;
		}
		else {							//중간에 매달때
			node->prev = pos->prev;
			node->next = pos;
			pos->prev->next = node;
			pos->prev = node;

		}
	}else{								//맨뒤에 매달때
		list->tail->next = node;
		node->prev = list->tail;
		list->tail = node;	
	}

	list->size++;

}

void deletNode(LinkedList *list, char *local) {

	Node *node = FindNode(list, local);
	
	if (node == NULL) {		//해당노드가 없을때
		return;
	}

	gotoxy(110, 15);
	printf("%s", node->local);

	if (node->prev != NULL) {
		node->prev->next = node->next;
	}
	else{
		list->head = list->head->next;
	}

	if (node->next != NULL) {
		node->next->prev = node->prev;
	}
	else {
		list->tail = list->tail->prev;
	}

	free(node);
	list->size--;
}

void PrintList(LinkedList *list) {
	Node *prev, *pos;
	prev = pos = list->head;
	int i = 1;
	while (pos != NULL) {
		gotoxy(110, i);
		printf("%d %s %d\n", pos->num, pos->local,pos->price);
		pos = pos->next;
		i++;
	}
}

//테스트용
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
		if (strcmp(temp->local, local) == 0) {		//노드를 발견하면
			gotoxy(110, 15);
			printf("%s", temp->local);
			return temp;
		}
		else {
			temp = temp->next;
		}
	}
	return NULL;
}

void modifiNode(LinkedList *list, char *local, int price) {
	Node *node = FindNode(list, local);
	node->price = price;
	list->size2++;
}

