#pragma once

#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#include <time.h>

#define COL GetStdHandle(STD_OUTPUT_HANDLE)

#define PLAYER1 SetConsoleTextAttribute(COL, 13);
#define PLAYER2 SetConsoleTextAttribute(COL, 11);

#define BlACK SetConsoleTextAttribute(COL, 0);
#define DARK_BLUE SetConsoleTextAttribute(COL, 1);
#define DARK_GREEN SetConsoleTextAttribute(COL, 2);
#define DARK_SKY_BLUE SetConsoleTextAttribute(COL, 3);
#define DARK_RED SetConsoleTextAttribute(COL, 4);
#define DARK_VOILET SetConsoleTextAttribute(COL, 5);
#define DARK_YELLOW SetConsoleTextAttribute(COL, 6);
#define GRAY SetConsoleTextAttribute(COL, 7);
#define DARK_GRAY SetConsoleTextAttribute(COL, 8);
#define BLUE SetConsoleTextAttribute(COL, 9);
#define GREEN SetConsoleTextAttribute(COL, 10);
#define SKY_BLUE SetConsoleTextAttribute(COL, 11);
#define RED SetConsoleTextAttribute(COL, 12);
#define VOILET SetConsoleTextAttribute(COL, 13);
#define YELLOW SetConsoleTextAttribute(COL, 14);
#define WHITE SetConsoleTextAttribute(COL, 15);


/*
0 ����
1 ��ο��Ķ�
2 ��ο� �ʷ�
3 ��ο� �ϴ�
4 ��ο� ����
5 ��ο� ����
6 ��ο� ���
7 ȸ��
8 ��ο� ȸ��
9 �Ķ�
10 �ʷ�
11 �ϴ�
12 ����
13 ����
14 ���
15 �Ͼ�
*/

void gotoxyint(int x, int y, int string);
void settextcolor(int color, int bgcolor); //http://thrillfighter.tistory.com/129
void gotoxy(int x, int y); //http://interacting.tistory.com/45
void gotoxytext(int x, int y, char *string);
void cursor_view(char s); //http://interacting.tistory.com/45


void SetColor(int color, int bkcolor);