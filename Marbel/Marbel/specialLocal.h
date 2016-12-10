#pragma once

#include "Player.h"
void BonusEvent(int turn, int board, int playerTurn, void *socks, bool isServer);	//���ʽ�����
void StartEvent(int turn, int board, int playerTurn, void *socks, bool isServer, LinkedList *list);	//�����
int IslandEvent(int turn, int playerTurn, void *socks, bool isServer);	//���ε�
void OlympicEvent(int turn, int playerTurn, void *socks, bool isServer, LinkedList *list);	//�ø��Ȱ���
int WorldTourEvent(int turn, int playerTurn, void *socks, bool isServer);	//�����̵�
void TaxEvent(int turn, int playerTurn, void *socks, bool isServer, LinkedList *list);	//����û