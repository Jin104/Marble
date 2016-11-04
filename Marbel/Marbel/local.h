#pragma once

#define boardNum 32

typedef struct _Local{
	char name[10];
	char color[10];
	int price;
	int x;
	int y;
	int state = -1;	//-1: 비어있음 0:player1의 호텔 1:player2의 호텔 
	//2:player1의 랜드마크 3:player2의 랜드마크 4:player1의 관광지 5:player2의 관광지

}Local;


extern char *localName[boardNum];
extern int localPrice[boardNum][4];	//0호텔건설/1랜마건설/2호텔통행료/3랜마통행료
extern char *localColor[boardNum];
extern int localX[boardNum];
extern int localY[boardNum];

//void makeLocal();