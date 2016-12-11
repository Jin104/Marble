#include <stdlib.h>
#include <string.h>
#include <process.h>
#include "Start.h"
#include "Client.h"
#include "Player.h"

#define BUF_SIZE 100
#define NAME_SIZE 20

extern LinkedList *list1, *list2, *list3, *list4;
extern Player player[4];
SOCKET sock;
void ErrorHandling(char* msg);

char msg[BUF_SIZE];

void AccessServerClient(char *ip, int totalNumber) {
	WSADATA wsaData;
	
	SOCKADDR_IN serverAddr;
	HANDLE sendThread, recvThread;

	char start[2];
	char myIp[20];
	char port[100];
	char inputName[10];
	char masterName[10];
	int turn;
	char name[10];


	printf("이름을 입력하세요: ");
	scanf("%s", inputName);
	sprintf(name, "s", inputName);


	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)// 윈도우 소켓을 사용한다고 운영체제에 알림
		ErrorHandling("WSAStartup() error!");


	sock = socket(PF_INET, SOCK_STREAM, 0);//소켓을 하나 생성한다.

	memset(&serverAddr, 0, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	//서버에서 받아온 ip
	//serverAddr.sin_addr.s_addr = inet_addr(ip);
	serverAddr.sin_addr.S_un.S_addr = inet_addr("192.168.55.78");
	serverAddr.sin_port = htons(10201);

	if (connect(sock, (SOCKADDR*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)//서버에 접속
	{
		printf("connect() error\n");
		
		//만약 서버에서 받아온 ip로 접속이 안되면, 자신이 직접 입력 (내부ip 외부ip 문제)
		printf("\nInput IP : ");
		getchar();
		gets_s(myIp);		
		serverAddr.sin_addr.s_addr = inet_addr(myIp);
		if (connect(sock, (SOCKADDR*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)
		{
			ErrorHandling("connect() error");
		}
	}

	//클라이언트 이름 입력
	
	printf("대기중입니다...\n");
	send(sock, inputName, sizeof(inputName), 0); //이름 서버로 전송
	
	//시작 신호를 받아옴
	recv(sock, start, sizeof(start), 0);
	if (atoi(start) == 9) {

		//모든 플레이어의 이름, 순서를 받아옴
		for (int i = 0; i < totalNumber; i++) {
			recv(sock, start, sizeof(start), 0);
			recv(sock, inputName, sizeof(inputName), 0); //서버로부터 클라이언트들의 이름 받아옴
			recv(sock, masterName, sizeof(masterName), 0); //방장 서버로부터 방장이름 받아옴
			turn = atoi(start);
			player[i].myTurn = turn;
			strcpy(player[0].name, masterName); //방장이름을 구조체 이름과 일치
			strcpy(player[i].name, inputName); //이름을 구조체 이름과 일치
			printf("player[%d]의 turn: %d\n", i, player[i].myTurn);
			printf("%s\n", player[i].name);
			}
		//자신의 순서를 받아옴
		recv(sock, start, sizeof(start), 0);
		turn = atoi(start);
		printf("게임을 시작합니다.\n");
		//게임 시작
		StartGame(totalNumber, turn, inputName, (void *)sock, false);
	}									  
	closesocket(sock);//소켓을 종료한다.
	WSACleanup();//윈도우 소켓 사용중지를 운영체제에 알린다.
	return;
}

void ErrorHandling(char* msg) {
	fputs(msg, stderr);
	fputc('\n', stderr);
	exit(1);
}