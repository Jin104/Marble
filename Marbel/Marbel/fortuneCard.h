#pragma once

#include "Player.h"
void FortuneCard(int turn, int board, int playerTurn, void *socks, bool isServer, LinkedList *list);	//����ī�� �������� �����ؼ� ����
void DrawFortuneCard();	//ī�� �׸�1
void DrawFortuneCard2();	//ī�� �׸�2

void HalfAngelCard(int turn, int playerTurn, void *socks, bool isServer);	//��õ�� ī��
void AngelCard(int turn, int playerTurn, void *socks, bool isServer);	//õ�� ī��
void InviteTravel(int turn, int playerTurn);	//���迩���ʴ� ī��
void GoStart(int turn, int board, int playerTurn, void *socks, bool isServer, LinkedList *list);	//������ΰ��� ī��
void GoIsland(int turn);	//���ε��ΰ��� ī��
void HoldOlympic(int turn, int playerTurn, void *socks, bool isServer, LinkedList *list);	//�ø����� �����ϴ� ī��
void CompelSale(int turn, int playerTurn, void *socks, bool isServer);	//�����Ű� ī��

int DoAngel(int turn, int price, int playerTurn, void *socks, bool isServer);	//��õ��,õ��ī�尡 ������ ���
