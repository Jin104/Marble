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

void gotoxyint(int x, int y, int string);	//Ŀ�� �̵��� �������
void settextcolor(int color, int bgcolor); //�ؽ�Ʈ �� http://thrillfighter.tistory.com/129
void gotoxy(int x, int y); //Ŀ���̵� http://interacting.tistory.com/45
void gotoxytext(int x, int y, char *string);
void cursor_view(char s); //Ŀ�� ���̱� http://interacting.tistory.com/45
