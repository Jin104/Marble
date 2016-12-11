#include <stdlib.h>
#include <string.h>
#include <process.h>
#include <WinSock2.h>
#include "start.h"
#include "Client.h"
#include "Player.h"

#define BUF_SIZE 100
#define MAX_CLNT 256

int serverNumber;
extern Player player[4];
unsigned WINAPI HandleClient(void* arg);//������ �Լ�
void ErrorHandling2(char* msg);

int clientCount = 0;
int total = 0;
char playerName[4][10];
char inputName[10];
char naam[4][10];
SOCKET clientSocks[MAX_CLNT];//Ŭ���̾�Ʈ ���� ������ �迭
HANDLE hMutex;//���ؽ�
SOCKET serverSock, clientSock;

void NewServer(int totalNumber) {	//���� �ο��� �޾ƿ�~
	
	WSADATA wsaData;
	SOCKADDR_IN serverAddr, clientAddr;
	int clientAddrSize;
	HANDLE hThread, sThread, rThread;
	struct hostent *h;
	total = totalNumber;
	
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) //������ ������ ����ϰڴٴ� ����� �ü���� ����
		ErrorHandling2("WSAStartup() error!");

	hMutex = CreateMutex(NULL, FALSE, NULL);//�ϳ��� ���ؽ��� �����Ѵ�.
	serverSock = socket(PF_INET, SOCK_STREAM, 0); //�ϳ��� ������ �����Ѵ�.

	memset(&serverAddr, 0, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	//serverAddr.sin_addr.S_un.S_addr = inet_addr("192.168.0.26");
	serverAddr.sin_port = htons(10201);

	if (bind(serverSock, (SOCKADDR*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) //������ ������ ��ġ�Ѵ�.
		ErrorHandling2("bind() error");
	if (listen(serverSock, totalNumber) == SOCKET_ERROR)//������ �غ���¿� �д�.	//��α�ť ������ �޴���
		ErrorHandling2("listen() error");

	clientSocks[clientCount++] = serverSock;

	printf("listening...\n");

	for (int i = 1; i < totalNumber; i++) {
		clientAddrSize = sizeof(clientAddr);
		clientSock = accept(serverSock, (SOCKADDR*)&clientAddr, &clientAddrSize);//�������� ���޵� Ŭ���̾�Ʈ ������ clientSock�� ����
		WaitForSingleObject(hMutex, INFINITE);//���ؽ� ����
		clientSocks[clientCount++] = clientSock;//Ŭ���̾�Ʈ ���Ϲ迭�� ��� ������ ���� �ּҸ� ����
		recv(clientSocks[i], inputName, sizeof(inputName), 0); //Ŭ���̾�Ʈ�κ��� �̸� �޾ƿ�
		strcpy(naam[i], inputName);
		ReleaseMutex(hMutex);//���ؽ� ����
		printf("Connected Client IP : %s\n", inet_ntoa(clientAddr.sin_addr));
	}

	hThread = (HANDLE)_beginthreadex(NULL, 0, HandleClient, (void*)&clientSock, 0, NULL);//HandleClient ������ ����, clientSock�� �Ű������� ����

	while (1)
	{

	}
	closesocket(serverSock);//������ ������ ����.
	WSACleanup();//������ ������ �����ϰڴٴ� ����� �ü���� ����
}

unsigned WINAPI HandleClient(void* arg) {
	int n, tmp;
	int num[4] = { 0,1,2,3 };
	char number[4][2];
	char mastername[10];
	char name[10];

	/*num[0] = 0;
	num[1] = 1;
	num[2] = 2;
	num[3] = 3;*/

	for (int i = 0; i < total; i++) {
		printf("num[%d]=%d\t", i, num[i]);
		itoa(num[i], number[i], 10);
		printf("number[%d]=%s\n", i, number[i]);
	}

	printf("\n\n����������������������������������������������");
	printf("\n������ �ο��� �� á���!                    ��");
	printf("\n�������� �̸��� �Է��ϸ� ������ ���۵˴ϴ�! ��");
	printf("\n����������������������������������������������");
	printf("\n\n Input your name : ");
	gets_s(mastername); //������ �̸� �Է�

	if (clientSocks[total-1] != NULL) {
		printf("���۽���\n");
		for (int i = 0; i < total; i++) {
			printf("���۽�ȣ����\n");
			send(clientSocks[i], "9", sizeof("9"), 0);	//���۸޼���
			for (int j = 0; j < total; j++) {
				send(clientSocks[i], number[j], sizeof(number[j]), 0);	//����
				send(clientSocks[i], naam[j], sizeof(naam[j]), 0); //��� Ŭ���̾�Ʈ������ �̸� ����
				send(clientSocks[i], mastername, sizeof(mastername), 0); //��� Ŭ���̾�Ʈ������ ���� �̸� ����
			}
			send(clientSocks[i], number[i], sizeof(number[i]), 0);	//����
			strcpy(player[0].name, mastername);
			strcpy(player[i].name, naam[i]);
		}
		serverNumber = num[0];
		StartGame(total, serverNumber, name, (void *)clientSocks, true);
	}

	return 0;
}

void SendMsg(char* msg, int len, int index) { //�޽����� ��� Ŭ���̾�Ʈ���� ������.
	int i;
	WaitForSingleObject(hMutex, INFINITE);//���ؽ� ����
	for (i = 0; i < clientCount; i++)//Ŭ���̾�Ʈ ������ŭ
	{
		if (i == index)
		{
			continue;
		}
		send(clientSocks[i], msg, len, 0);//Ŭ���̾�Ʈ�鿡�� �޽����� �����Ѵ�.
	}
	ReleaseMutex(hMutex);//���ؽ� ����
}

void ErrorHandling2(char* msg) {
	fputs(msg, stderr);
	fputc('\n', stderr);
	exit(1);
}