#include "Start.h"
#include "Graphics.h"
#include "Client.h"

#pragma warning(disable:4996)
//����
//���� �޴� ����Ű
//void main() {
//
//	//Ŀ�� ����
//	cursor_view(0);
//	sndPlaySoundA("..\\sound\\Modoo Marble Zion-T AR new_44k_16b.wav", SND_ASYNC | SND_NODEFAULT);
//	Loading();
//	Menu();
//
//	int select, num = 1;
//
//	while (1) {
//		select = _getch();
//
//		switch (select) {
//		case 80: //�Ʒ��� Ŀ��Ű
//			num = 2;
//			settextcolor(0x0007, 000000);
//			gotoxytext(50, 28, " ");
//			gotoxytext(50, 30, "��");
//
//			settextcolor(0, 3);
//			gotoxytext(55, 30, "[2] ���� ����");
//
//			settextcolor(0x0007, 000000);
//			gotoxytext(55, 28, "[1] ���� ����");
//			break;
//		case 72: //���� Ŀ��Ű
//			num = 1;
//			settextcolor(0x0007, 000000);
//			gotoxytext(50, 30, " ");
//			gotoxytext(50, 28, "��");
//
//			settextcolor(0, 3);
//			gotoxytext(55, 28, "[1] ���� ����");
//
//			settextcolor(0x0007, 000000);
//			gotoxytext(55, 30, "[2] ���� ����");
//			break;
//		case 13:
//			system("cls");
//			if (num == 1) {
//				StartGame();
//			}
//			else if (num == 2) {
//				Explain();
//			}
//		}
//	}
//}


void main()
{
	char select[2];
	char roomNum[5];
	char roomAllNum[5];
	char roomName[256];
	char message[256];
	char roomIp[20];

	/*���� ����*/
	SOCKET sock = NewTCPSocket();

	printf("1. �� ����\n");
	printf("2. �� ����\n");
	scanf("%s", select);
	send(sock, select, sizeof(select), 0);

	switch (atoi(select)) {
	case 1:
		system("cls");
		printf("2~4�� ��, �� �ο� ���� ����� �ǰ���? ���ڸ� �Է����ּ���.\n");
		scanf("%s", select);
		send(sock, select, sizeof(select), 0);
		printf("�� �̸��� �Է����ּ���.\n");
		getchar();
		gets_s(roomName);
		send(sock, roomName, sizeof(roomName), 0);
		recv(sock, message, sizeof(message), 0);
		printf("server: %s\n", message);
		NewServer(atoi(select));
		break;
	case 2:
		system("cls");
		recv(sock, select, sizeof(select), 0);
		printf("### %d ###\n", atoi(select));
		for (int i = 0; i < atoi(select); i++) {
			recv(sock, roomName, sizeof(roomName), 0);
			printf("%d��° �� [�� �̸�: %s\t", i + 1, roomName);
			recv(sock, roomNum, sizeof(roomNum), 0);
			printf("���� �ο���: %s\t", roomNum);
			recv(sock, roomAllNum, sizeof(roomAllNum), 0);
			printf("���ο���: %s]\n", roomAllNum);
		}

		printf("�����Ͻǹ��� ��ȣ�� �Է����ּ��� :   ");
		getchar();
		gets_s(select);
		send(sock, select, sizeof(select), 0);
		recv(sock, roomIp, sizeof(roomIp), 0);
		AccessServerClient(roomIp,atoi(roomAllNum));
		break;
	default:
		break;
	}
}