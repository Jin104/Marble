#include "Start.h"
#include "Graphics.h"
#include "Client.h"

#pragma warning(disable:4996)

int main(int argc, char *argv[])
{
	struct hostent *h;
	char select[2];
	char roomNum[5];
	char roomAllNum[5];
	char roomName[256];
	char message[256];
	char roomIp[20];
	char inputName[10];
	char ip[20];
	
	/*소켓 생성*/
	SOCKET sock = NewTCPSocket();
	h = gethostbyname(argv[1]);
	printf("Host name  : %s\n", h->h_name);
	printf("IP Address : %s\n", inet_ntoa(*((struct in_addr *)h->h_addr)));
	strcpy(ip, inet_ntoa(*((struct in_addr *)h->h_addr)));
	printf("\n1. 방 생성\n");
	printf("2. 방 입장\n\n");
	printf("☞ ");
	scanf("%s", select);
	send(sock, select, sizeof(select), 0);

	switch (atoi(select)) {
	case 1:
		system("cls");
		printf("\n2 ~ 4인 중, 몇 인용 방을 만드실 건가요? 숫자만 입력해주세요\n\n");
		printf("☞ ");
		scanf("%s", select);
		send(sock, select, sizeof(select), 0);
		printf("\n방 이름을 입력해주세요\n\n");
		printf("☞ ");
		getchar();
		gets_s(roomName);
		send(sock, roomName, sizeof(roomName), 0);
		send(sock, ip, sizeof(ip), 0);
		recv(sock, message, sizeof(message), 0);
		printf("\nserver: %s\n", message);
		NewServer(atoi(select));
		break;
	case 2:
		system("cls");
		recv(sock, select, sizeof(select), 0);
		printf("\n### %d ###\n\n", atoi(select));
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
		recv(sock, ip, sizeof(ip), 0);
		AccessServerClient(roomIp,ip,atoi(roomAllNum));
		break;
	default:
		break;
	}
}