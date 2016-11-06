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
0 검정
1 어두운파랑
2 어두운 초록
3 어두운 하늘
4 어두운 빨강
5 어두운 보라
6 어두운 노랑
7 회색
8 어두운 회색
9 파랑
10 초록
11 하늘
12 빨강
13 보라
14 노랑
15 하양
*/

void gotoxyint(int x, int y, int string);
void settextcolor(int color, int bgcolor); //http://thrillfighter.tistory.com/129
void gotoxy(int x, int y); //http://interacting.tistory.com/45
void gotoxytext(int x, int y, char *string);
void cursor_view(char s); //http://interacting.tistory.com/45


void SetColor(int color, int bkcolor);