#pragma once

#define boardNum 32

typedef struct _Local{
	char name[10];
	char color[10];
	int price;
	int x;
	int y;
	int state = -1;	//-1: ������� 0:player1�� ȣ�� 1:player2�� ȣ�� 
	//2:player1�� ���帶ũ 3:player2�� ���帶ũ 4:player1�� ������ 5:player2�� ������

}Local;


extern char *localName[boardNum];
extern int localPrice[boardNum][4];	//0ȣ�ڰǼ�/1�����Ǽ�/2ȣ�������/3���������
extern char *localColor[boardNum];
extern int localX[boardNum];
extern int localY[boardNum];

//void makeLocal();