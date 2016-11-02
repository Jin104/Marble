#pragma once

#define boardNum 32

typedef struct {
	char name[10];
	char color[10];
	int price;
	int x;
	int y;

}Local;


extern char *localName[boardNum];
extern int localPrice[boardNum];
extern char *localColor[boardNum];
extern int localX[boardNum];
extern int localY[boardNum];

//void makeLocal();