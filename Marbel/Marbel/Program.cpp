#include "Start.h"
#include "Graphics.h"
#include "Client.h"

#pragma warning(disable:4996)

void main()
{
	struct hostent *h;
	char select[2];
	char roomNum[5];
	char roomAllNum[5];
	char roomName[256];
	char message[256];
	char roomIp[20];
	char inputName[10];
	
	/*���� ����*/
	SOCKET sock = NewTCPSocket();
	sndPlaySoundA("..\\sound\\Modoo Marble Zion-T AR new_44k_16b.wav", SND_ASYNC | SND_NODEFAULT);
	Loading();
	while (1) {
		Loading2();
		Menu();
		gotoxytext(55, 34, "�� ");
		gotoxy(60, 34);
		scanf("%s", select);

		//���ð� �������� ����
		if (atoi(select) != 3) {
			send(sock, select, sizeof(select), 0);
		}
		switch (atoi(select)) {
		case 1:	//�� �����
			system("cls");
			printf("\n2 ~ 4�� ��, �� �ο� ���� ����� �ǰ���? ���ڸ� �Է����ּ���\n\n");
			printf("�� ");

			do {
				gotoxy(4, 3);
				scanf("%s", select);
				gotoxytext(4, 3, "      ");
			} while (atoi(select) != 4 && atoi(select) != 2 && atoi(select) != 3);
			gotoxy(4, 3);
			printf("%s", select);
			send(sock, select, sizeof(select), 0);	//�ο����� �������� ����
			printf("\n�� �̸��� �Է����ּ���\n\n");
			printf("�� ");
			getchar();
			gets_s(roomName);
			send(sock, roomName, sizeof(roomName), 0);	//�� �̸��� �������� ����
			recv(sock, message, sizeof(message), 0);	//�������� �޼����� ����
			printf("\nserver: %s\n", message);
			NewServer(atoi(select));	//���ο� tcp����(�� ����) ����
			break;
		case 2:	//�� ����
			system("cls");
			recv(sock, select, sizeof(select), 0);	//�� ���� ���� �޾ƿ�
			printf("\n### %d ###\n\n", atoi(select));
			for (int i = 0; i < atoi(select); i++) {	//�� ����Ʈ �޾ƿ�
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
			send(sock, select, sizeof(select), 0);	//���ð���� ������ ����
			recv(sock, roomIp, sizeof(roomIp), 0);	//ip�� �޾ƿ�
			AccessServerClient(roomIp, atoi(roomAllNum));	//�޾ƿ� ip�� ����
			break;
		case 3:
			Explain();
			break;
		default:
			break;
		}
	}
}