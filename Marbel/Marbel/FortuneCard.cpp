#include "graphics.h"
#include "draw.h"
#include "fortuneCard.h"
#include <stdio.h>

void Fortune_Card() {
	gotoxy(112, 16); printf("��������������");
	gotoxy(112, 17); printf("��          ��");
	gotoxy(112, 18); printf("��          ��");
	gotoxy(112, 19); printf("��          ��");
	gotoxy(112, 20); printf("��    ��    ��");
	gotoxy(112, 21); printf("��          ��");
	gotoxy(112, 22); printf("��          ��");
	gotoxy(112, 23); printf("��          ��");
	gotoxy(112, 24); printf("��          ��");
	gotoxy(112, 25); printf("��������������");
}

void Defense_Card() {
	gotoxytext(48, 43, "�� õ��ī�� ��");
	gotoxytext(48, 44, "����� ���� ���� (���� �� ���� �� ��밡��)");

	gotoxytext(48, 43, "�� õ��ī�� ��");
	gotoxytext(48, 44, "����� �ݰ� ���� (���� �� ���� �� ��밡��)");
}

void Order_Card() {
	gotoxytext(48, 43, "�� ���迩�� �ʴ�� ��");
	gotoxytext(48, 44, "������ ������ ~ ���� ��� ���迩������ �̵�!");

	gotoxytext(48, 43, "�� ����� GO ��");
	gotoxytext(48, 44, "�� ���� �� ��� ~ ���� ��� ������� �̵�!");

	gotoxytext(48, 43, "�� ���ε� Ž�� ��");
	gotoxytext(48, 44, "�ʹ� �ռ����׿�.. ���� ��� ���ε��� �̵�!");

	gotoxytext(48, 43, "�� �ø��� ���� ��");
	gotoxytext(48, 44, "�ø��� ��� ����!!! ���ϴ� ���� �ø��� ����");
}

void Attack_Card() {
	gotoxytext(48, 43, "�� ���� ü���� ��");
	gotoxytext(48, 44, "���ϴ� ����� ���ÿ� �� ���ø� �±�ȯ (���帶ũ �Ǽ��� ���� ���ݺҰ�)");

	gotoxytext(48, 43, "�� ���� �Ű� ��");
	gotoxytext(48, 44, "���ϴ� ����� ���ø� ������ �Ű� (���帶ũ �Ǽ��� ���� ���ݺҰ�)");
}