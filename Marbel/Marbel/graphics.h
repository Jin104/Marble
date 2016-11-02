#pragma once

#include <stdio.h>
#include <conio.h>
#include <Windows.h>

#define COL GetStdHandle(STD_OUTPUT_HANDLE)
#define BLUE_GREEN SetConsoleTextAttribute(COL, 0x003);
#define ORIGINAL SetConsoleTextAttribute(COL, 0x0007);

void settextcolor(int color, int bgcolor); //http://thrillfighter.tistory.com/129
void gotoxy(int x, int y); //http://interacting.tistory.com/45
void gotoxytext(int x, int y, char *string);
void cursor_view(char s); //http://interacting.tistory.com/45