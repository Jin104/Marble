#pragma once

#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#include <time.h>
#include <mmsystem.h>
#pragma comment(lib,"Winmm.lib")

#define COL GetStdHandle(STD_OUTPUT_HANDLE)
#define PLAYER1 SetConsoleTextAttribute(COL, 13);
#define PLAYER2 SetConsoleTextAttribute(COL, 11);
#define DARK_SKY_BLUE SetConsoleTextAttribute(COL, 3);
#define GRAY SetConsoleTextAttribute(COL, 7);

void gotoxyint(int x, int y, int string);	//커서 이동후 숫자출력
void settextcolor(int color, int bgcolor); //텍스트 색 http://thrillfighter.tistory.com/129
void gotoxy(int x, int y); //커서이동 http://interacting.tistory.com/45
void gotoxytext(int x, int y, char *string);
void cursor_view(char s); //커서 보이기 http://interacting.tistory.com/45
