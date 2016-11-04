#pragma once

#include "local.h"
//typedef Node *Link;	//��ȯ�� ����� ��ġ ����

typedef struct _Node {
	char local[10];
	int price;
	int num;
	_Node *next;
	_Node *prev;
}Node;

typedef struct _LinkedList {
	int size;
	Node *head;
	Node *tail;
}LinkedList;

LinkedList *NewList();	//���Ḯ��Ʈ ���� ����

Node *NewNode(char *local, int price, int num);	//��� ����

void PrintList(LinkedList *list);	//����Ʈ ���
void PrintList2(LinkedList *list);
Node *FindNode(LinkedList *list, char *local);	//��� ã��

void HangNode(LinkedList *list, Node *node);
void modifiNode(LinkedList *list, char *local, int price);
void deletNode(LinkedList *list, char *local);
