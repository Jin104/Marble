#pragma once

#include "local.h"
//typedef Node *Link;	//반환할 노드의 위치 정보

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

LinkedList *NewList();	//연결리스트 동적 생성

Node *NewNode(char *local, int price, int num);	//노드 생성

void PrintList(LinkedList *list);	//리스트 출력
void PrintList2(LinkedList *list);
Node *FindNode(LinkedList *list, char *local);	//노드 찾기

void HangNode(LinkedList *list, Node *node);
void modifiNode(LinkedList *list, char *local, int price);
void deletNode(LinkedList *list, char *local);
