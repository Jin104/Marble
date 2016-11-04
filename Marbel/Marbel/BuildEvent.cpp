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
	int answer, answer2;
	int state = local[board].state;
	switch (board)
	{
	case 0:
		break;
	case 2:
		bonusEvent(turn);
		PlayerState();
		break;
	case 8:
		//player[turn].state = 2;
		gotoxytext(34, 30, "���ε� ��÷");
		Sleep(500);
		gotoxytext(34, 30, "           ");
		break;
	case 12: case 20: case 28:
		break;
	case 16:
		//OlympicEvent(turn);
		PlayerState();
		break;
	case 24:
		printf("���迩��~~ �����Ͽ� ���ϴ°����� �̵��Ҽ��־��.");
		player[turn].state = 3;
		break;
	case 30:
		break;
	default:

		switch (state)
		{
		case -1:   //������ ���������
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
			break;
		case 0:   //ȣ���� �������ִ°��
			if (turn == 0) {
				BuildRandmark(turn, board);
			}
			if (turn == 1) {
				if (local[board].state == 0) {
					gotoxy(34, 30);
					printf("������ %d���� �Դϴ�.", localPrice[board][2]);

					if (player[turn].marble < localPrice[board][2]) {
						Bankrupt(turn, localPrice[board][2]);
					}
					else {
						player[turn].marble -= localPrice[board][2];
					}
					Takeover(turn, board);

					Sleep(300);

				}
				if (local[board].state == 2) {   //���帶ũ�϶��� �μ��� �Ұ���
					gotoxy(34, 30);
					printf("������ %d���� �Դϴ�.", localPrice[board][3]);
					player[turn].marble -= localPrice[board][3];
					Sleep(300);
				}
			}
			break;
		case 1:
			if (turn == 1) {
				BuildRandmark(turn, board);
			}
			if (turn == 0) {
				if (local[board].state == 1) {
					gotoxy(34, 30);
					printf("������ %d���� �Դϴ�.", localPrice[board][2]);
					player[turn].marble -= localPrice[board][2];

					Takeover(turn, board);

					Sleep(300);

				}
				if (local[board].state == 3) {
					gotoxy(34, 30);
					printf("������ %d���� �Դϴ�.", localPrice[board][3]);
					player[turn].marble -= localPrice[board][3];
					Sleep(300);
				}
			}
			break;
		case 2:

			break;
		case 3:

			break;
		case 4:
			if (turn == 1) {
				gotoxy(34, 30);
				printf("������ %d���� �Դϴ�.", localPrice[board][0]);
				player[turn].marble -= localPrice[board][0];
				Sleep(300);
			}
			break;
		case 5:
			if (turn == 0) {
				gotoxy(34, 30);
				printf("������ %d���� �Դϴ�.", localPrice[board][0]);
				player[turn].marble -= localPrice[board][0];
				Sleep(300);
			}
			break;
		default:
			break;
		}

		Sleep(500);
		PlayerState();
		PrintList(list1);
		//clrList();
		PrintList2(list2);
		clrText();

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
		local[board].state = turn + 1;      //������ ���º���
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

//void PayMarble(int turn, int price) {
//
//	int answer,answer2;
//	char name[10];
//
//	gotoxytext(34, 30, "����ᰡ �����մϴ�.\n");
//	gotoxy(70, 30); printf("������ ����: %d", price - player[turn].marble);
//	gotoxy(48, 31);
//	printf("1) �Ű�  2) �Ļ�  (����) �� ");
//	answer = _getch() - 48;
//	gotoxy(80, 31); printf("%d", answer);
//	clrText();
//	if (answer == 1) {
//		gotoxytext(48, 30, "������ ���� ����Ʈ �Դϴ�.\n");
//		if (turn == 0) {
//			PrintList(list1);
//			while (1) {
//				clrText();
//				gotoxytext(48, 31, "�Ű��� ������ �̸��� �Է��ϼ���: ");
//				gotoxy(48, 32); scanf("%s", name);
//				if (FindNode == NULL) {
//					gotoxy(48, 33);  printf("�������� �ʴ� �����Դϴ�.");
//				}
//				else {
//					int marble = deletNode(list1, name);
//					player[turn].marble += marble;
//					gotoxy(70, 30); printf("������ ����: %d", price - player[turn].marble);
//					if (list1->size < 1) {
//						gotoxytext(34, 33, "���̻� �Ű��� ������ �����ϴ�.");
//						Sleep(500);
//						clrText();
//						return;
//					}
//					gotoxytext(34, 33, "�� �Ű��Ͻðڽ��ϱ�?");
//					gotoxy(34, 34);
//					printf("1) YES  2) NO  (����) �� ");
//					answer = _getch() - 48;
//					gotoxy(80, 34); printf("%d", answer);
//					if (answer == 2) {
//						break;
//					}
//				}
//				gotoxytext(34, 33, "�Ļ�!!!");
//				Sleep(500);
//				clrText();
//				return;
//			}
//		}
//	}
//	else if(answer == 2) {
//	
//	}
//}