#include "Player.h"
#include "BuildEvent.h"
#include "Start.h"
#include "Client.h"

extern LinkedList *list1, *list2, *list3, *list4;   //�÷��̾�1,2�� �������� ���Ḯ��Ʈ
extern Player player[4];
extern Local local[32];
extern int tNum;

/*�ǹ� �Ű�*/
int SellBuilding(int turn, int price, int playerTurn, void *socks, bool isServer, LinkedList *list) {
	
	int select, select1;
	char name[10];
	char data[2];

	/*���ұݾ��� �÷��̾��� ���������� ū���*/
	while (price > player[turn].marble) {

		clrText();
		clrList();
		if (turn == playerTurn) {
			gotoxytext(37, 27, "�Ű����� �����Դϴ�.");
			PrintList(list);
			gotoxy(65, 27);
			printf("%d ������ �����մϴ�.", price - player[turn].marble);
			gotoxy(37, 29); printf("�Ű��� �����̸��� �Է����ּ���.");
			gotoxytext(37, 30, "�Է� �� ");
			cursor_view(1);
			gotoxy(53, 30); scanf("%s", name);
			cursor_view(0);
			if (isServer)
			{
				SendMsg(name, sizeof(name), 0);
			}
			else
			{
				send((SOCKET)socks, name, sizeof(name), 0);
			}
		}
		else
		{
			if (isServer)
			{
				SOCKET *sockArr = (SOCKET *)socks;
				while (recv(sockArr[turn], name, sizeof(name), 0) <= 0);
				SendMsg(name, sizeof(name), turn);
			}
			else
			{
				while (recv((SOCKET)socks, name, sizeof(name), 0) <= 0);
			}
		}
		
		Node *node = FindNode(list, name);	//����Ʈ���� �Է��������� �ִ��� Ȯ��
		int cnt = 0;
		if (node != NULL) {	//������

			int money = node->price / 2;	//�Ű����� ������ ����

			local[node->num].state = -1;	//�ǹ��� ���¸� �⺻����
			gotoxytext(local[node->num].x, local[node->num].y - 2, "      ");	//�ǹ��׸� �����
			deletNode(list, name);	//������
			player[turn].marble += money;	//�������� �Ű��� ���ϱ�
			PlayerState(tNum);

			/*����� ������ 0�϶�*/
			if (list->size < 1) {
				if(turn==playerTurn)
					gotoxytext(37, 32, "���̻� �Ű��Ұǹ��� �����ϴ�.");
				Sleep(900);
				return -1;
			};
		}
		else {
			if (turn == playerTurn)
				gotoxytext(37, 32, "�ٽ� �Է����ּ���.");
			Sleep(500);
			gotoxytext(37, 32, "                  ");
		}
	}

	/*�Ű��� ������ ���濡�� ���� ����*/
	player[turn].marble -= price;
	player[1 - turn].marble += price;
	PlayerState(tNum);
	return 0;

}

/*�Ļ�*/
void Bankrupt(int turn, int price, int playerTurn, void *socks, bool isServer, LinkedList *list) {
	
	int select, select1;
	char data[2];

	if (turn == playerTurn) {
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
		clrText();
		itoa(select, data, 10);

		if (isServer)
		{
			SendMsg(data, sizeof(data), 0);
		}
		else
		{
			send((SOCKET)socks, data, sizeof(data), 0);
		}
		select1 = atoi(data);
	}
	else
	{
		if (isServer)
		{
			SOCKET *sockArr = (SOCKET *)socks;
			while (recv(sockArr[turn], data, sizeof(data), 0) <= 0);
			SendMsg(data, sizeof(data), turn);
		}
		else
		{
			while (recv((SOCKET)socks, data, sizeof(data), 0) <= 0);
		}
		select1 = atoi(data);
	}

	if (select1 == 1) { 
		/*��� �ǹ��� �Ű��ص� ����ᰡ �����Ҷ�*/
		if (SellBuilding(turn, price, playerTurn, socks, isServer, list) == -1) {
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
void TouristMonop(int turn, int playerTurn) {
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
		if (turn == playerTurn) {
			sndPlaySoundA("..\\sound\\WinRule_A01.wav", SND_ASYNC | SND_NODEFAULT);
			printf("�����մϴ�! %s���� ���������� �¸�!", player[turn].name);
		}
		else {
			printf("%s���� �������������� �й�!", player[turn].name);
		}
		gotoxytext(37, 29, "EnterŰ�� ������ ������ ����˴ϴ�!");
		getch();
		system("pause>null");
		exit(1);
	}
}

//����
//Ʈ���� ���� �¸�
void ColorMonop(int turn, int playerTurn) {

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
	if (color == 3) { //�÷����� 3���̸� �¸�
		clrText();
		gotoxy(42, 27); 
		if (turn == playerTurn) {
			sndPlaySoundA("..\\sound\\WinRule_A01.wav", SND_ASYNC | SND_NODEFAULT);
			printf("�����մϴ�! %s���� Ʈ���õ��� �¸�!", player[turn].name);
		}
		else {
			printf("%s���� Ʈ���õ������� �й�!", player[turn].name);
		}
		gotoxytext(42, 29, "EnterŰ�� ������ ������ ����˴ϴ�!");
		gotoxy(42, 31);
		exit(1);
	}
}

void LineMonop(int turn, int playerTurn) {

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
		
		if (turn == playerTurn) {
			sndPlaySoundA("..\\sound\\WinRule_A01.wav", SND_ASYNC | SND_NODEFAULT);
			printf("�����մϴ�! %s���� ���ε��� �¸�!", player[turn].name);
		}
		else {
			printf("%s���� ���ε������� �й�!", player[turn].name);
		}
		gotoxytext(37, 29, "EnterŰ�� ������ ������ ����˴ϴ�!");
		getch();
		system("pause>null");
		exit(1);
	}


}

void CheckGameOver(int turn, int playerTurn) {
	TouristMonop(turn, playerTurn);
	ColorMonop(turn, playerTurn);
	LineMonop(turn, playerTurn);
}