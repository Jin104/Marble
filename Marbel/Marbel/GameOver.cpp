#include "Player.h"
#include "BuildEvent.h"
#include "Start.h"

extern LinkedList *list1, *list2;   //�÷��̾�1,2�� �������� ���Ḯ��Ʈ
extern Player player[2];
extern Local local[32];

/*�ǹ� �Ű�*/
int SellBuilding(int turn, int price) {

	LinkedList *list;
	if (turn == 0)
		list = list1;
	else
		list = list2;

	char name[10];

	/*���ұݾ��� �÷��̾��� ���������� ū���*/
	while (price > player[turn].marble) {

		clrText();
		clrList();
		gotoxytext(37, 27, "�Ű����� �����Դϴ�.");
		PrintList(list);
		gotoxy(65, 27);
		printf("%d ������ �����մϴ�.", price - player[turn].marble);
		gotoxy(37, 29); printf("�Ű��� �����̸��� �Է����ּ���.");
		gotoxytext(37, 30, "�Է� �� ");
		cursor_view(1);
		gotoxy(53, 30); scanf("%s", name);
		cursor_view(0);

		Node *node = FindNode(list, name);	//����Ʈ���� �Է��������� �ִ��� Ȯ��
		int cnt = 0;
		if (node != NULL) {	//������

			int money = node->price / 2;	//�Ű����� ������ ����

			local[node->num].state = -1;	//�ǹ��� ���¸� �⺻����
			gotoxytext(local[node->num].x, local[node->num].y - 2, "      ");	//�ǹ��׸� �����
			deletNode(list, name);	//������
			player[turn].marble += money;	//�������� �Ű��� ���ϱ�
			PlayerState();

			/*����� ������ 0�϶�*/
			if (list->size < 1) {
				gotoxytext(37, 32, "���̻� �Ű��Ұǹ��� �����ϴ�.");
				Sleep(900);
				return -1;
			};
		}
		else {
			gotoxytext(37, 32, "�ٽ� �Է����ּ���.");
			Sleep(500);
			gotoxytext(37, 32, "                  ");
		}
	}

	/*�Ű��� ������ ���濡�� ���� ����*/
	player[turn].marble -= price;
	player[1 - turn].marble += price;
	PlayerState();
	return 0;

}

/*�Ļ�*/
void Bankrupt(int turn, int price) {
	LinkedList *list;
	if (turn == 0)
		list = list1;
	else
		list = list2;

	int select;
	gotoxytext(37, 27, "����ᰡ �����մϴ�.\n");
	gotoxy(37, 28);
	printf("1) �Ű�  2) �Ļ�  (����) �� ");

	gotoxy(70, 28);
	cursor_view(1);
	do {
		select = _getch() - 48;
		gotoxyint(70, 28, select);
		gotoxytext(70, 28, "      ");

	} while (select != 1 && select != 2);
	cursor_view(0);
	gotoxyint(70, 28, select);

	if (select == 1) {
		if (SellBuilding(turn, price) == -1) {
			clrText();
			gotoxytext(37, 27, "��� �ǹ��� �Ű��ص� �����մϴ�..");
			Sleep(700);
			clrText();
			gotoxy(45, 30);
			printf("%s���� �Ļ�¸�!", player[1 - turn].name);

			gotoxytext(37, 33, "EnterŰ�� ������ ������ ����˴ϴ�!");
			getch();
			system("pause>null");
			exit(1);
		}
		else {
			gotoxytext(37, 27, "�Ű��� �Ϸ��߽��ϴ�.");
		}
	}
	else {
		clrText();
		gotoxytext(37, 27, "�Ļ�!!");

		Sleep(700);
		clrText();
		gotoxy(45, 30);
		printf("%s���� �Ļ�¸�!", player[1 - turn].name);

		gotoxytext(37, 29, "EnterŰ�� ������ ������ ����˴ϴ�!");
		getch();
		system("pause>null");
		exit(1);
	}
}

/*���������� �¸�*/
void TouristMonop(int turn) {
	int cnt = 0;

	/*������ ���°� �������� cnt����*/
	for (int i = 0; i < boardNum; i++) {
		if (local[i].state == turn + 4) {
			cnt++;
		}
	}
	if (cnt == 5) {
		clrText();
		gotoxy(37, 27);
		sndPlaySoundA("..\\sound\\WinRule_A03.wav", SND_ASYNC | SND_NODEFAULT);
		printf("�����մϴ�! %s���� ���������� �¸�!", player[turn].name);

		gotoxytext(37, 29, "EnterŰ�� ������ ������ ����˴ϴ�!");
		getch();
		system("pause>null");
		exit(1);
	}
}

//����
//Ʈ���� ���� �¸�
void ColorMonop(int turn) {

	int cnt1 = 0, cnt2 = 0, cnt3 = 0, cnt4 = 0, cnt5 = 0, cnt6 = 0, cnt7 = 0, cnt8 = 0; //�÷�����
	int color = 0; //�÷����� ��

	if ((local[1].state == turn || local[1].state == turn + 2) && (local[3].state == turn || local[3].state == turn + 2)) {
		cnt1++; //���� ����¡
	}
	if ((local[5].state == turn || local[5].state == turn + 2) && (local[6].state == turn || local[6].state == turn + 2) && (local[7].state == turn || local[7].state == turn + 2)) {
		cnt2++; //Ÿ������ �ι��� ī�̷�
	}
	if ((local[10].state == turn || local[10].state == turn + 2) && (local[11].state == turn || local[11].state == turn + 2)) {
		cnt3++; //���� �õ��
	}
	if ((local[13].state == turn || local[13].state == turn + 2) && (local[15].state == turn || local[15].state == turn + 2)) {
		cnt4++; //���� ���Ŀ��
	}
	if ((local[17].state == turn || local[17].state == turn + 2) && (local[19].state == turn || local[19].state == turn + 2)) {
		cnt5++; //������ ������
	}
	if ((local[21].state == turn || local[21].state == turn + 2) && (local[22].state == turn || local[22].state == turn + 2) && (local[23].state == turn || local[23].state == turn + 2)) {
		cnt6++; //��ũ�� ���׹� �θ�
	}
	if ((local[26].state == turn || local[26].state == turn + 2) && (local[27].state == turn || local[27].state == turn + 2)) {
		cnt7++; //���� �ĸ�
	}
	if ((local[29].state == turn || local[29].state == turn + 2) && (local[31].state == turn || local[31].state == turn + 2)) {
		cnt8++; //���� ����
	}

	color = cnt1 + cnt2 + cnt3 + cnt4 + cnt5 + cnt6 + cnt7 + cnt8;
	if (color >= 3) { //�÷����� 3���̸� �¸�
		sndPlaySoundA("..\\sound\\WinRule_A01.wav", SND_ASYNC | SND_NODEFAULT);
		clrText();
		gotoxy(42, 27); printf("�����մϴ�! %s���� Ʈ���õ��� �¸�!", player[turn].name);
		gotoxytext(42, 29, "EnterŰ�� ������ ������ ����˴ϴ�!");
		gotoxy(42, 31);
		exit(1);
	}
}

void LineMonop(int turn) {

	int cnt1 = 0, cnt2 = 0, cnt3 = 0, cnt4 = 0;

	/*���κ��� �������¸� üũ�ؼ� ī��Ʈ*/
	for (int i = 1; i < 8; i++) {
		if (local[i].state == turn || local[i].state == turn + 2 || local[i].state == turn + 4) {
			cnt1++;
		}
	}

	for (int i = 9; i < 16; i++) {
		if (local[i].state == turn || local[i].state == turn + 2 || local[i].state == turn + 4) {
			cnt2++;
		}
	}

	for (int i = 17; i < 24; i++) {
		if (local[i].state == turn || local[i].state == turn + 2 || local[i].state == turn + 4) {
			cnt3++;
		}
	}

	for (int i = 25; i < 32; i++) {
		if (local[i].state == turn || local[i].state == turn + 2 || local[i].state == turn + 4) {
			cnt4++;
		}
	}
	if (cnt1 == 6 || cnt2 == 6 || cnt3 == 6 || cnt4 == 5) {
		clrText();
		gotoxy(37, 27);
		sndPlaySoundA("..\\sound\\WinRule_A01.wav", SND_ASYNC | SND_NODEFAULT);
		printf("�����մϴ�! %s���� ���ε��� �¸�!", player[turn].name);

		gotoxytext(37, 29, "EnterŰ�� ������ ������ ����˴ϴ�!");
		getch();
		system("pause>null");
		exit(1);
	}


}

void CheckGameOver(int turn) {
	TouristMonop(turn);
	ColorMonop(turn);
	LineMonop(turn);
}	