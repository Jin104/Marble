#include "Player.h"
#include "Draw.h"

/*���ο� ����Ʈ ����*/
LinkedList *NewList() {

	LinkedList *list = (LinkedList*)malloc(sizeof(LinkedList));
	list->head = NULL;
	list->tail = NULL;

	list->size = 0;
	list->size2 = 0;

	return list;
}

/*���ο� ��� ����*/
Node *NewNode(char *local, int price, int num) {
	Node *node = (Node*)malloc(sizeof(Node));
	strcpy(node->local, local);
	node->price = price;
	node->num = num;
	node->next = NULL;
	node->prev = NULL;
	return node;
}

/*��带 ������������(������ȣ����) ����Ʈ�� �޾���*/
void HangNode(LinkedList *list, Node *node) {

	if (list->head == NULL) {	//���������
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
		if (list->head == pos) {		//�Ǿտ� �Ŵ޶�
			node->next = list->head;
			list->head->prev = node;
			list->head = node;
		}
		else {							//�߰��� �Ŵ޶�
			node->prev = pos->prev;
			node->next = pos;
			pos->prev->next = node;
			pos->prev = node;

		}
	}
	else {								//�ǵڿ� �Ŵ޶�
		list->tail->next = node;
		node->prev = list->tail;
		list->tail = node;
	}

	list->size++;

}

/*��� ����*/
void deletNode(LinkedList *list, char *local) {

	Node *node = FindNode(list, local);

	if (node == NULL) {		//�ش��尡 ������
		return;
	}

	/*����� ����尡 ������*/
	if (node->prev != NULL) {
		node->prev->next = node->next;
	}
	else {
		list->head = list->head->next;
	}

	/*����� ������尡 ������*/
	if (node->next != NULL) {
		node->next->prev = node->prev;
	}
	else {
		list->tail = list->tail->prev;
	}

	free(node);
	list->size--;
}

/*����Ʈ ���*/
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

//�׽�Ʈ��
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

/*��� �˻�*/
Node *FindNode(LinkedList *list, char *local) {
	Node *temp;
	temp = list->head;
	while (temp != NULL) {
		if (strcmp(temp->local, local) == 0) {		//��带 �߰��ϸ�
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

/*��尪 ����*/
void modifiNode(LinkedList *list, char *local, int price) {
	Node *node = FindNode(list, local);
	node->price = price;
	list->size2++;
}

