#include "graphics.h"
#include "draw.h"
#include "fortuneCard.h"
#include <stdio.h>

void Fortune_Card() {
	gotoxy(112, 16); printf("┏━━━━━┓");
	gotoxy(112, 17); printf("┃          ┃");
	gotoxy(112, 18); printf("┃          ┃");
	gotoxy(112, 19); printf("┃          ┃");
	gotoxy(112, 20); printf("┃    ★    ┃");
	gotoxy(112, 21); printf("┃          ┃");
	gotoxy(112, 22); printf("┃          ┃");
	gotoxy(112, 23); printf("┃          ┃");
	gotoxy(112, 24); printf("┃          ┃");
	gotoxy(112, 25); printf("┗━━━━━┛");
}

void Defense_Card() {
	gotoxytext(48, 43, "★ 천사카드 ★");
	gotoxytext(48, 44, "통행료 전부 면제 (보관 후 원할 때 사용가능)");

	gotoxytext(48, 43, "★ 천사카드 ★");
	gotoxytext(48, 44, "통행료 반값 할인 (보관 후 원할 때 사용가능)");
}

void Order_Card() {
	gotoxytext(48, 43, "★ 세계여행 초대권 ★");
	gotoxytext(48, 44, "여행을 떠나요 ~ 지금 즉시 세계여행으로 이동!");

	gotoxytext(48, 43, "★ 출발지 GO ★");
	gotoxytext(48, 44, "새 마음 새 출발 ~ 지금 즉시 출발지로 이동!");

	gotoxytext(48, 43, "★ 무인도 탐험 ★");
	gotoxytext(48, 44, "너무 앞서갔네요.. 지금 즉시 무인도로 이동!");

	gotoxytext(48, 43, "★ 올림픽 개최 ★");
	gotoxytext(48, 44, "올림픽 즉시 개최!!! 원하는 곳에 올림픽 개최");
}

void Attack_Card() {
	gotoxytext(48, 43, "★ 도시 체인지 ★");
	gotoxytext(48, 44, "원하는 상대의 도시와 내 도시를 맞교환 (랜드마크 건설된 도시 공격불가)");

	gotoxytext(48, 43, "★ 강제 매각 ★");
	gotoxytext(48, 44, "원하는 상대의 도시를 강제로 매각 (랜드마크 건설된 도시 공격불가)");
}