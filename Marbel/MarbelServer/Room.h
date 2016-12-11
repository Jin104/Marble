#pragma once

typedef struct _Node {
	char name[256];		//방 이름
	char allNum[5];		//방의 총 인원수
						//char num[5];		//방의 현재 인원수
	int num;			//방의 현재 인원수
	int number;			//방의 번호(리스트 번호)
	char ip[20];		//방의 ip
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

Node *FindNode(LinkedList *list, int num);   //노드 찾기
void DeletNode(LinkedList *list, Node *node);   //노드 삭제

void PrintList(LinkedList *list);

void modiNode(LinkedList *list, Node *node);

void modiNum(LinkedList *list);