#pragma once

#include "Draw.h"

void StartGame(int totalNumber, int playerTurn);	//���ӽ���
void initLocal();	//�����ʱ�ȭ
void initPlayerCoord(int totalNumber);	//�÷��̾��ʱ�ȭ
void MovePlayer(int i, int turn);	//�÷��̾� �̵�
void PlayerTurn(int totalNumber);	//�÷��̾� ���� ���ϱ�
void StartGame2(void* playerturn);