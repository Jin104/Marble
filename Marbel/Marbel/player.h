#pragma once

#include "local.h"

typedef struct _Player {
	int turn = 0;	//playerTurn에서 Turn정해줄때
	int board = 0;	//
	int playerX = 21;	//위치X좌표
	int playerY = 45;	//위치Y좌표
	char name[10];	//이름
	int marble = 10000;	//보유마블
	int state = 0;	//상태 0: 기본 1:무인도 2:세계여행
	int card = 0;	//소유카드 0: 기본 1:천사카드 2:반천사카드
	int count = 0;	//무인도에 갇혔을때 던진 주사위 턴 수
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

LinkedList *NewList();	//연결리스트 생성

Node *NewNode(char *local, int price, int num);	//노드 생성
void HangNode(LinkedList *list, Node *node);	//노드 연결

void PrintList(LinkedList *list);	//리스트 출력
void PrintList2(LinkedList *list);	//테스트용 리스트 출력

Node *FindNode(LinkedList *list, char *local);	//노드 찾기
void deletNode(LinkedList *list, char *local);	//노드 삭제
void modifiNode(LinkedList *list, char *local, int price);	//노드 값 수정
