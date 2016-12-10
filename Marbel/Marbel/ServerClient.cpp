#include <stdlib.h>
#include <string.h>
#include <process.h>
#include <WinSock2.h>
#include "start.h"
#include "Client.h"
#define BUF_SIZE 100
#define MAX_CLNT 256

int serverNumber;

unsigned WINAPI HandleClient(void* arg);//������ �Լ�
void ErrorHandling2(char* msg);

int clientCount = 0;
int total = 0;
char playerName[4][10];
SOCKET clientSocks[MAX_CLNT];//Ŭ���̾�Ʈ ���� ������ �迭
HANDLE hMutex;//���ؽ�
SOCKET serverSock, clientSock;

void NewServer(int totalNumber) {	//���� �ο��� �޾ƿ�~
	
	WSADATA wsaData;
	SOCKADDR_IN serverAddr, clientAddr;
	int clientAddrSize;
	HANDLE hThread, sThread, rThread;
	
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
	int num[4];// = { 0,1,2,3 };
	char number[4][2];

	//srand(time(NULL));
	//for (int i = total - 1; i > 0; i--) {
	//	n = rand() % total;
	//	tmp = num[i];
	//	num[i] = num[n];
	//	num[n] = tmp;
	//}

	num[0] = 0;
	num[1] = 1;
	num[2] = 2;
	num[3] = 3;

	for (int i = 0; i < total; i++) {
		printf("num[%d]=%d\t", i, num[i]);
		itoa(num[i], number[i], 10);
		printf("number[%d]=%s\n", i, number[i]);
	}

	if (clientSocks[total-1] != NULL) {
		printf("���۽���\n");
		for (int i = 0; i < total; i++) {
			printf("���۽�ȣ����\n");
			send(clientSocks[i], "9", sizeof("9"), 0);	//���۸޼���
			for (int j = 0; j < total; j++) {
				send(clientSocks[i], number[j], sizeof(number[j]), 0);	//����
				//send(clientSocks[i], playerName[j], sizeof(playerName[j]), 0);	//����
			}
			send(clientSocks[i], number[i], sizeof(number[i]), 0);	//����
		}
		serverNumber = num[0];
		StartGame(total, serverNumber, "0", (void *)clientSocks, true);
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