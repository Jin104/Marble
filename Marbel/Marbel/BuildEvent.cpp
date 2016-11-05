#include "player.h"
#include "buildEvent.h"
#include "start.h"
#include "draw.h"

extern LinkedList *list1, *list2;   //�÷��̾�1,2�� �������� ���Ḯ��Ʈ
extern Player player[2];
extern Local local[32];

void buildBuilding(int turn, int board) {

	//turn=> �÷��̾��ȣ 0:player1  1:player2
	//borad=> �÷��̾�ִ� ������ȣ
	//state=> ������ ���Ż��� -1: ������� 0:player1�� ȣ�� 1:player2�� ȣ�� 2:player1�� ���帶ũ 3:player2�� ���帶ũ 4:player1�� ������ 5:player2�� ������
	//board=> ������ Ư����   0���� 2���ʽ����� 4,9,14,18,25������ 8���ε� 12,20,28����ī�� 16�ø��� 24���迩�� 30����û
	int answer;
	int state = local[board].state;
	switch (board)
	{
	
	case 0:	//�����   ���帶ũ�Ǽ� �ʿ�
		StartEvent(turn);
		break;
	case 2:	//���ʽ�����
		BonusEvent(turn);
		PlayerState();
		break;
	case 8:	//���ε�
		gotoxytext(34, 30, "���ε� ��÷");
		Sleep(1500);
		gotoxytext(34, 30, "           ");
		player[turn].state = 2;
		break;
	case 12: case 20: case 28:	//
		FortuneCard(turn);
		break;
	case 16:
		OlympicEvent(turn);
		PlayerState();
		break;
	case 24:
		gotoxytext(34, 30, "���迩�� �����Ͽ� ���ϴ°����� �̵�����");
		Sleep(1500);
		gotoxytext(34, 30, "           ");
		player[turn].state = 3;
		break;
	case 30:
		TaxEvent(turn);
		break;
	default:

		switch (state)
		{
		case -1:   //������ ���������
			if (player[turn].marble >= local[board].price) {	//�����ҵ��� ������
				gotoxytext(34, 30, "����ִ� �����Դϴ�. �����Ͻðڽ��ϱ�?");
				gotoxy(48, 31);
				printf("1) YES  2) NO  (����) �� ");
				answer = _getch() - 48;
				gotoxy(80, 31); printf("%d", answer);
				if (answer == 1) {
					if (board != 4 && board != 9 && board != 14 && board != 18 && board != 25) {   //�������� ����
						gotoxytext(48, 32, "ȣ���� �Ǽ��߽��ϴ�.");
						local[board].state = turn;   //������ ���¸� �ٲ���
					}
					else {
						gotoxytext(48, 32, "�������� �����߽��ϴ�.");
						local[board].state = turn + 4;   //������ ���¸� �ٲ���
					}

					player[turn].marble -= localPrice[board][0];   //���� ���� ����

					Node *node = NewNode(local[board].name, local[board].price, player[turn].board);   //���ο� ����������
					if (turn == 0) {
						gotoxytext(local[board].x, local[board].y - 2, "����");   //�ǹ��׸� ���
						HangNode(list1, node);   //�÷��̾��� ����Ʈ�� ������带 ��������
					}
					else {
						gotoxytext(local[board].x, local[board].y - 2, "����");
						HangNode(list2, node);
					}
				}
			}
			else{
				gotoxy(34, 31);
				printf("������ ���� �����մϴ�.\n");
			}
			break;
		case 0:   //player1�� ȣ���� �������ִ°��
			if (turn == 0) {
				BuildRandmark(turn, board);
			}
			if (turn == 1) {
				gotoxy(34, 30);

				int toll = localPrice[board][2];

				if (local[board].olystate == 1) {
					toll = toll * 2;
					local[board].olystate = 0;
				}
				
				printf("������ %d���� �Դϴ�.", toll);

				int price = toll;

				if (player[turn].card == 1 || player[turn].card == 2) {
					price -= DoAngel(turn, toll);
					gotoxy(34, 30); 
					printf("������ %d���� �Դϴ�.", price);
				}

				if (player[turn].marble < toll) {
					Bankrupt(turn, toll);
				}
				else {
					player[turn].marble -= price;
				}
				Takeover(turn, board);

				Sleep(300);

			}
			break;
		case 1:	//player2�� ȣ���� �������ִ°��
			if (turn == 1) {
				BuildRandmark(turn, board);
			}
			if (turn == 0) {
				gotoxy(34, 30);

				int toll = localPrice[board][2];

				if (local[board].olystate == 1) {
					toll = toll * 2;
					local[board].olystate = 0;
				}

				printf("������ %d���� �Դϴ�.", toll);
				
				int price = toll;

				if (player[turn].card == 1 || player[turn].card == 2) {
					price -= DoAngel(turn, toll);
					gotoxy(34, 30);
					printf("������ %d���� �Դϴ�.", price);
				}

				if (player[turn].marble < toll) {
					Bankrupt(turn, toll);
				}
				else {
					player[turn].marble -= price;
				}
				Takeover(turn, board);

				Sleep(300);

			}
			break;
		case 2:	//player1�� ���帶ũ�� �������ִ°��
			if (turn == 1) {
				gotoxy(34, 30);

				int toll = localPrice[board][3];

				if (local[board].olystate == 1) {
					toll = toll * 2;
					local[board].olystate = 0;
				}

				printf("������ %d���� �Դϴ�.", toll);

				int price = toll;

				if (player[turn].card == 1 || player[turn].card == 2) {
					price -= DoAngel(turn, toll);
					gotoxy(34, 30);
					printf("������ %d���� �Դϴ�.", price);
				}

				player[turn].marble -= price;
				Sleep(300);
			}
			break;
		case 3:	//player2�� ���帶ũ�� �������ִ°��
			if (turn == 0) {
				gotoxy(34, 30);

				int toll = localPrice[board][3];

				if (local[board].olystate == 1) {
					toll = toll * 2;
					local[board].olystate = 0;
				}

				printf("������ %d���� �Դϴ�.", toll);

				int price = toll;

				if (player[turn].card == 1 || player[turn].card == 2) {
					price -= DoAngel(turn, toll);
					gotoxy(34, 30);
					printf("������ %d���� �Դϴ�.", price);
				}

				player[turn].marble -= price;
				Sleep(300);
			}
			break;
		case 4:
			if (turn == 1) {
				gotoxy(34, 30);

				int toll = localPrice[board][2];

				if (local[board].olystate == 1) {
					toll = toll * 2;
					local[board].olystate = 0;
				}
				printf("������ %d���� �Դϴ�.", toll);
				player[turn].marble -= toll;
				Sleep(300);
			}
			break;
		case 5:
			if (turn == 0) {
				gotoxy(34, 30);

				int toll = localPrice[board][2];

				if (local[board].olystate == 1) {
					toll = toll * 2;
					local[board].olystate = 0;
				}
				
				printf("������ %d���� �Դϴ�.", toll);
				player[turn].marble -= toll;
				Sleep(300);
			}
			break;
		default:
			break;
		}

		Sleep(500);
		PlayerState();
		clrList();
		//PrintList(list1);
		//PrintList2(list2);
		clrText();
		CheckGameOver(turn);
		break;
	}
}

void BuildRandmark(int turn, int board) {
	int answer;
	gotoxytext(34, 30, "���帶ũ�� �Ǽ��Ͻðڽ��ϱ�?");
	gotoxy(48, 31);
	printf("1) YES  2) NO  (����) �� ");
	answer = _getch() - 48;
	gotoxy(80, 31); printf("%d", answer);
	if (answer == 1) {
		gotoxytext(48, 32, "���帶ũ�� �Ǽ��߽��ϴ�.");
		local[board].state = turn + 2;      //������ ���º���
		local[board].price = localPrice[board][3];   //������ ���ݺ���
		if (turn == 0) {
			gotoxytext(local[board].x, local[board].y - 2, "������");   //���帶ũ ������� ����
			player[turn].marble -= localPrice[board][1];   //�������� ����
			modifiNode(list1, local[board].name, localPrice[board][3]);
		}
		else {
			gotoxytext(local[board].x, local[board].y - 2, "������");
			player[turn].marble -= localPrice[board][1];
			modifiNode(list2, local[board].name, localPrice[board][3]);
		}
	}
}

void Takeover(int turn, int board) {
	int answer;
	if (player[turn].marble > localPrice[board][0]) {   //�μ��� ���� ������
		gotoxy(34, 31);
		printf("�μ��Ͻðڽ��ϱ�? �μ���� %d�Դϴ�.\n", localPrice[board][0]);
		gotoxy(34, 32);
		printf("1) YES  2) NO  (����) �� ");
		answer = _getch() - 48;
		gotoxy(80, 32); printf("%d", answer);
		if (answer == 1) {
			gotoxytext(34, 33, "�μ��� �Ϸ��߽��ϴ�.\n");
			player[turn].marble -= localPrice[board][0];   //�������� ����
			player[1 - turn].marble += localPrice[board][0];
			local[board].state = turn;   //������ ���� ����
			Node *node = NewNode(local[board].name, local[board].price, player[turn].board);   //������� ����
			if (turn == 0) {
				deletNode(list2, local[board].name);   //������ ���Ḯ��Ʈ���� ������� ����
				HangNode(list1, node);   //�ڽ��� ���Ḯ��Ʈ�� ������� ����
				gotoxytext(local[board].x, local[board].y - 2, "����");   //�ǹ��׸� ����
			}
			else {
				deletNode(list1, local[board].name);
				HangNode(list2, node);
				gotoxytext(local[board].x, local[board].y - 2, "����");
			}
			return;
		}
	}
	else {
		gotoxy(34, 31);
		printf("�μ��� ���� �����մϴ�.\n");
	}
}
