#pragma once

#include "local.h"

typedef struct _Node {
	char local[10];
	int price;
	int num;
	_Node *next;
	_Node *prev;
}Node;

typedef struct _LinkedList {
	int size;
	int size2;
	Node *head;
	Node *tail;
}LinkedList;

LinkedList *NewList();	//���Ḯ��Ʈ ����

Node *NewNode(char *local, int price, int num);	//��� ����
void HangNode(LinkedList *list, Node *node);	//��� ����

void PrintList(LinkedList *list);	//����Ʈ ���
void PrintList2(LinkedList *list);	//�׽�Ʈ�� ����Ʈ ���

Node *FindNode(LinkedList *list, char *local);	//��� ã��
void deletNode(LinkedList *list, char *local);	//��� ����
void modifiNode(LinkedList *list, char *local, int price);	//��� �� ����
