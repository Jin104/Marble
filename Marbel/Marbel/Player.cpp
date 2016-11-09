#include "Player.h"
#include "Draw.h"

/*새로운 리스트 생성*/
LinkedList *NewList() {

	LinkedList *list = (LinkedList*)malloc(sizeof(LinkedList));
	list->head = NULL;
	list->tail = NULL;

	list->size = 0;
	list->size2 = 0;

	return list;
}

/*새로운 노드 생성*/
Node *NewNode(char *local, int price, int num) {
	Node *node = (Node*)malloc(sizeof(Node));
	strcpy(node->local, local);
	node->price = price;
	node->num = num;
	node->next = NULL;
	node->prev = NULL;
	return node;
}

/*노드를 오름차순으로(지역번호기준) 리스트에 달아줌*/
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
	}
	else {								//맨뒤에 매달때
		list->tail->next = node;
		node->prev = list->tail;
		list->tail = node;
	}

	list->size++;

}

/*노드 삭제*/
void deletNode(LinkedList *list, char *local) {

	Node *node = FindNode(list, local);

	if (node == NULL) {		//해당노드가 없을때
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
	list->size--;
}

/*리스트 출력*/
void PrintList(LinkedList *list) {
	Node *prev, *pos;
	prev = pos = list->head;
	int i = 2;
	while (pos != NULL) {
		gotoxy(110, i);
		printf("%d %s %d\n", pos->num, pos->local, pos->price);
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

/*노드 검색*/
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

/*노드값 변경*/
void modifiNode(LinkedList *list, char *local, int price) {
	Node *node = FindNode(list, local);
	node->price = price;
	list->size2++;
}

