#pragma once

typedef struct _Node {
	char name[256];		//�� �̸�
	char allNum[5];		//���� �� �ο���
						//char num[5];		//���� ���� �ο���
	int num;			//���� ���� �ο���
	int number;			//���� ��ȣ(����Ʈ ��ȣ)
	char ip[20];		//���� ip
	_Node *next;
	_Node *prev;
}Node;

typedef struct _LinkedList {
	Node *head;
	Node *tail;
	int size;
}LinkedList;

LinkedList *NewList();
Node *NewNode(char *name, char *allNum, int num, char *ip);
void HangNode(LinkedList *list, Node *node);

Node *FindNode(LinkedList *list, int num);   //��� ã��
void DeletNode(LinkedList *list, Node *node);   //��� ����

void PrintList(LinkedList *list);

void modiNode(LinkedList *list, Node *node);

void modiNum(LinkedList *list);