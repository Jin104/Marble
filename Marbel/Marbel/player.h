#pragma once

//typedef Node *Link;	//��ȯ�� ����� ��ġ ����

typedef struct _Node {
	char local[10];
	_Node *next;
	_Node *prev;
}Node;

typedef struct _LinkedList {
	int size;
	Node *head;
	Node *tail;
}LinkedList;

LinkedList *NewList();	//���Ḯ��Ʈ ���� ����

Node *NewNode(char *local);	//��� ����

void PrintList(LinkedList *list);

void PushBack(LinkedList *list, char *local);	//���������� �ڷ� ����
void insert(LinkedList *list, Node *pos, char *local);;	//Ư�� ��� �տ� �ڷ� ����

void HangNode(Node *now, Node *pos);	//Ư�� ��� �տ� ��� ����

void Erase(LinkedList *list, Node *pos);	//Ư�� ��ġ�� ��� ����
void DisconnectNode(Node *pos);	//���Ḯ��Ʈ���� ���� ����

void printList(LinkedList *list);	//����Ʈ ���

Node *FindNode(LinkedList *list, char *local);	//��� ã��


