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
	
	/*소켓 생성*/
	SOCKET sock = NewTCPSocket();
	sndPlaySoundA("..\\sound\\Modoo Marble Zion-T AR new_44k_16b.wav", SND_ASYNC | SND_NODEFAULT);
	Loading();
	while (1) {
		Loading2();
		Menu();
		gotoxytext(55, 34, "☞ ");
		gotoxy(60, 34);
		scanf("%s", select);

		//선택값 서버에게 전송
		if (atoi(select) != 3) {
			send(sock, select, sizeof(select), 0);
		}
		switch (atoi(select)) {
		case 1:	//방 만들기
			system("cls");
			printf("\n2 ~ 4인 중, 몇 인용 방을 만드실 건가요? 숫자만 입력해주세요\n\n");
			printf("☞ ");

			do {
				gotoxy(4, 3);
				scanf("%s", select);
				gotoxytext(4, 3, "      ");
			} while (atoi(select) != 4 && atoi(select) != 2 && atoi(select) != 3);
			gotoxy(4, 3);
			printf("%s", select);
			send(sock, select, sizeof(select), 0);	//인원수를 서버에게 전송
			printf("\n방 이름을 입력해주세요\n\n");
			printf("☞ ");
			getchar();
			gets_s(roomName);
			send(sock, roomName, sizeof(roomName), 0);	//방 이름을 서버에게 전송
			recv(sock, message, sizeof(message), 0);	//서버에게 메세지를 받음
			printf("\nserver: %s\n", message);
			NewServer(atoi(select));	//새로운 tcp서버(방 서버) 생성
			break;
		case 2:	//방 들어가기
			system("cls");
			recv(sock, select, sizeof(select), 0);	//총 방의 개수 받아옴
			printf("\n### %d ###\n\n", atoi(select));
			for (int i = 0; i < atoi(select); i++) {	//방 리스트 받아옴
				recv(sock, roomName, sizeof(roomName), 0);
				printf("%d번째 방 [방 이름: %s\t", i + 1, roomName);
				recv(sock, roomNum, sizeof(roomNum), 0);
				printf("현재 인원수: %s\t", roomNum);
				recv(sock, roomAllNum, sizeof(roomAllNum), 0);
				printf("총인원수: %s]\n", roomAllNum);
			}

			printf("입장하실방의 번호를 입력해주세요 :   ");
			getchar();
			gets_s(select);
			send(sock, select, sizeof(select), 0);	//선택결과를 서버에 보냄
			recv(sock, roomIp, sizeof(roomIp), 0);	//ip를 받아옴
			AccessServerClient(roomIp, atoi(roomAllNum));	//받아온 ip로 접속
			break;
		case 3:
			Explain();
			break;
		default:
			break;
		}
	}
}