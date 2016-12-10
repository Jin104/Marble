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
	char masterName[10];
	int turn;
	char name[10];
	//sprintf(myIp, "%s", ip);
	//printf("ip: %s\n", myIp);
	printf("\nInput IP : ");
	gets_s(myIp);

	printf("Input your name : ");
	gets_s(inputName);

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)// ������ ������ ����Ѵٰ� �ü���� �˸�
		ErrorHandling("WSAStartup() error!");

	sprintf(name, "%s", inputName);

	sock = socket(PF_INET, SOCK_STREAM, 0);//������ �ϳ� �����Ѵ�.

	memset(&serverAddr, 0, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = inet_addr(myIp);
	//serverAddr.sin_addr.S_un.S_addr = inet_addr("110.15.82.167");
	//serverAddr.sin_addr.S_un.S_addr = inet_addr("192.168.0.2");
	serverAddr.sin_port = htons(10201);
	if (connect(sock, (SOCKADDR*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)//������ �����Ѵ�.
		ErrorHandling("connect() error");

	printf("������Դϴ�...\n");
	send(sock, inputName, sizeof(inputName), 0); //�̸� ������ ����
	recv(sock, start, sizeof(start), 0);
	if (atoi(start) == 9) {
		for (int i = 0; i < totalNumber; i++) {
			recv(sock, start, sizeof(start), 0);
			recv(sock, inputName, sizeof(inputName), 0); //�����κ��� Ŭ���̾�Ʈ���� �̸� �޾ƿ�
			recv(sock, masterName, sizeof(masterName), 0); //���� �����κ��� �����̸� �޾ƿ�
			turn = atoi(start);
			player[i].myTurn = turn;
			strcpy(player[0].name, masterName); //�����̸��� ����ü �̸��� ��ġ
			strcpy(player[i].name, inputName); //�̸��� ����ü �̸��� ��ġ
			printf("player[%d]�� turn: %d\n", i, player[i].myTurn);
			printf("%s\n", player[i].name);
			}
		recv(sock, start, sizeof(start), 0);
		turn = atoi(start);
		printf("������ �����մϴ�.\n");
		StartGame(totalNumber, turn, inputName, (void *)sock, false);
	}									  
	closesocket(sock);//������ �����Ѵ�.
	WSACleanup();//������ ���� ��������� �ü���� �˸���.
	return;
}

void ErrorHandling(char* msg) {
	fputs(msg, stderr);
	fputc('\n', stderr);
	exit(1);
}