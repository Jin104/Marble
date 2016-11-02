#pragma once

#define boardNum 32

typedef struct {
	char localName[10];
	char localColor[10];
	int localPrice;
	int x;
	int y;

}Local;


extern char *localName[boardNum];
extern int localPrice[boardNum];
extern char *localColor[boardNum];
extern int localX[boardNum];
extern int localY[boardNum];

//void makeLocal();