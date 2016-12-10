#include "Start.h"
#include "Graphics.h"
#include "Client.h"

#pragma warning(disable:4996)

void main()
{
	char select[2];
	char roomNum[5];
	char roomAllNum[5];
	char roomName[256];
	char message[256];
	char roomIp[20];

	/*소켓 생성*/
	SOCKET sock = NewTCPSocket();

	printf("1. 방 생성\n");
	printf("2. 방 입장\n");
	scanf("%s", select);
	send(sock, select, sizeof(select), 0);

	switch (atoi(select)) {
	case 1:
		system("cls");
		printf("2~4인 중, 몇 인용 방을 만드실 건가요? 숫자만 입력해주세요.\n");
		scanf("%s", select);
		send(sock, select, sizeof(select), 0);
		printf("방 이름을 입력해주세요.\n");
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
			printf("%d번째 방 [방 이름: %s\t", i + 1, roomName);
			recv(sock, roomNum, sizeof(roomNum), 0);
			printf("현재 인원수: %s\t", roomNum);
			recv(sock, roomAllNum, sizeof(roomAllNum), 0);
			printf("총인원수: %s]\n", roomAllNum);
		}

		printf("입장하실방의 번호를 입력해주세요 :   ");
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