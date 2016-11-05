#pragma once

typedef struct _Player{
	int turn = 0;	//playerTurn���� Turn�����ٶ�
	int board=0;	//
	int playerX=21;	//��ġX��ǥ
	int playerY=45;	//��ġY��ǥ
	char name[10];	//�̸�
	int marble = 1000;	//��������
	int state = 0;	//���� 0: �⺻ 1:����� 2:���ε� 3:���迩��
	int card = 0;	//����ī�� 0: �⺻ 1:õ��ī�� 2:��õ��ī��
	int count = 0;	//���ε��� �������� ���� �ֻ��� �� ��
}Player;

void StartGame();
void initLocal();
void initPlayerCoord();
void movePlayer(int i, int turn);
void playerTurn();
