#pragma once

#include "graphics.h"

/*�ֻ��� �� �ֻ����� ��, ���� ��*/
typedef struct {
	int dice1;
	int dice2;
	int equal = 0;
	int sum;
}Dice;

Dice GameDice(int i);	//�ֻ��� ������
void DoubleDice();	//�ֻ��� ������ �������� ���
void GameBoard();	//������
void DiceShape(int dice);	//�ֻ��� �׸�1
void DiceShape2(int dice2);	//�ֻ��� �׸�2
void DrawPlayer(int totalNumber);	//�÷��̾� â
void PlayerState(int tNum);	//�÷��̾� �������

void Menu();	//�޴�
void Explain();	//����
void Loading();	//�ε�ȭ��
void Loading2();
void clrText();	//�ؽ�Ʈ ��� �����
void clrList();	//��������Ʈ ��� �����
void clrCard();	//ī�� ��� �����
void clrDice();
void SetDrawColor(int turn);