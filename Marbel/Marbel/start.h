#pragma once

#include "Draw.h"

void StartGame(int totalNumber, int playerTurn, char *name,void *socks, bool isServer);	//���ӽ���
void initLocal();	//�����ʱ�ȭ
void initPlayerCoord(int totalNumber);	//�÷��̾��ʱ�ȭ
void MovePlayer(int i, int turn);	//�÷��̾� �̵�
void PlayerTurn(int totalNumber);	//�÷��̾� ���� ���ϱ�
