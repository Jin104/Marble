#pragma once

//typedef Node *Link;	//반환할 노드의 위치 정보

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

LinkedList *NewList();	//연결리스트 동적 생성

Node *NewNode(char *local);	//노드 생성

void PrintList(LinkedList *list);

void PushBack(LinkedList *list, char *local);	//순차적으로 자료 보관
void insert(LinkedList *list, Node *pos, char *local);;	//특정 노드 앞에 자료 보관

void HangNode(Node *now, Node *pos);	//특정 노드 앞에 노드 연결

void Erase(LinkedList *list, Node *pos);	//특정 위치의 노드 제거
void DisconnectNode(Node *pos);	//연결리스트에서 연결 끊음

void printList(LinkedList *list);	//리스트 출력

Node *FindNode(LinkedList *list, char *local);	//노드 찾기


