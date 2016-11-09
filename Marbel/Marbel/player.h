#pragma once

#include "local.h"

typedef struct _Player {
	int turn = 0;	//playerTurn���� Turn�����ٶ�
	int board = 0;	//
	int playerX = 21;	//��ġX��ǥ
	int playerY = 45;	//��ġY��ǥ
	char name[10];	//�̸�
	int marble = 10000;	//��������
	int state = 0;	//���� 0: �⺻ 1:���ε� 2:���迩��
	int card = 0;	//����ī�� 0: �⺻ 1:õ��ī�� 2:��õ��ī��
	int count = 0;	//���ε��� �������� ���� �ֻ��� �� ��
	int color = 0;
}Player;

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
