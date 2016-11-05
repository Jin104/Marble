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

LinkedList *NewList();	//연결리스트 생성

Node *NewNode(char *local, int price, int num);	//노드 생성
void HangNode(LinkedList *list, Node *node);	//노드 연결

void PrintList(LinkedList *list);	//리스트 출력
void PrintList2(LinkedList *list);	//테스트용 리스트 출력

Node *FindNode(LinkedList *list, char *local);	//노드 찾기
void deletNode(LinkedList *list, char *local);	//노드 삭제
void modifiNode(LinkedList *list, char *local, int price);	//노드 값 수정
