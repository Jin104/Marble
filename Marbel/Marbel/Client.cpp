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

void AccessServerClient(char *ip,int totalNumber) {
	WSADATA wsaData;
	
	SOCKADDR_IN serverAddr;
	HANDLE sendThread, recvThread;

	char start[2];
	char myIp[20];
	char port[100];
	char inputName[10];
	int turn;
	char name[10];
	//sprintf(myIp, "%s", ip);
	//printf("ip: %s\n", myIp);
	printf("Input IP : ");
	gets_s(myIp);

	printf("Input your name : ");
	gets_s(inputName);

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)// 윈도우 소켓을 사용한다고 운영체제에 알림
		ErrorHandling("WSAStartup() error!");

	sprintf(name, "%s", inputName);

	sock = socket(PF_INET, SOCK_STREAM, 0);//소켓을 하나 생성한다.

	memset(&serverAddr, 0, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = inet_addr(myIp);
	//serverAddr.sin_addr.S_un.S_addr = inet_addr("110.15.82.167");
	//serverAddr.sin_addr.S_un.S_addr = inet_addr("192.168.0.2");
	serverAddr.sin_port = htons(10201);
	if (connect(sock, (SOCKADDR*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)//서버에 접속한다.
		ErrorHandling("connect() error");

	printf("대기중입니다...\n");
	//send(sock, name, sizeof(name), 0);		//이름보내기
	recv(sock, start, sizeof(start), 0);
	if (atoi(start) == 9) {
		for (int i = 0; i < totalNumber; i++) {
			recv(sock, start, sizeof(start), 0);
			turn = atoi(start);
			player[i].myTurn = turn;
			printf("player[%d]의 turn: %d\n", i, player[i].myTurn);
			}
		recv(sock, start, sizeof(start), 0);
		turn = atoi(start);
		printf("게임을 시작합니다.\n");
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