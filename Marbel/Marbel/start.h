#pragma once

#include "Draw.h"

void StartGame(int totalNumber);	//���ӽ���
void initLocal();	//�����ʱ�ȭ
void initPlayerCoord(int totalNumber);	//�÷��̾��ʱ�ȭ
void MovePlayer(int i, int turn);	//�÷��̾� �̵�
void PlayerTurn(int totalNumber);	//�÷��̾� ���� ���ϱ�
