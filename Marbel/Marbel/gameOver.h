#pragma once

void Bankrupt(int turn, int price, int playerTurn, void *socks, bool isServer, LinkedList *list);	//�Ļ�
int SellBuilding(int turn, int price, int playerTurn, void *socks, bool isServer, LinkedList *list);	//�Ű�

void TouristMonop(int turn, int playerTurn);	//����������
void ColorMonop(int turn, int playerTurn);	//Ʈ���� ����(�÷�����3��)
void LineMonop(int turn, int playerTurn);	//���ε���

void CheckGameOver(int turn, int playerTurn);	//�����Լ� 3���� ��Ƴ���