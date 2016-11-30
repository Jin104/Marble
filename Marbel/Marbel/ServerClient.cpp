#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <process.h>
#include <time.h>
#include <WinSock2.h>
#include <Windows.h>
#include "Client.h"

#define BUF_SIZE 100
#define MAX_CLNT 256


void DoIt(void *param);

unsigned WINAPI HandleClient(void* arg);//������ �Լ�
void SendMsg(char* msg, int len);//�޽��� ������ �Լ�
void ErrorHandling2(char* msg);

int clientCount = 0;
int total = 0;
char playerName[4][10];
SOCKET clientSocks[MAX_CLNT];//Ŭ���̾�Ʈ ���� ������ �迭
HANDLE hMutex;//���ؽ�

void NewServer(int totalNumber) {	//���� �ο��� �޾ƿ�~
	
	WSADATA wsaData;
	SOCKET serverSock, clientSock;
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

	printf("listening...\n");

	//while (1) {
	//	clientAddrSize = sizeof(clientAddr);
	//	clientSock = accept(serverSock, (SOCKADDR*)&clientAddr, &clientAddrSize);//�������� ���޵� Ŭ���̾�Ʈ ������ clientSock�� ����
	//	WaitForSingleObject(hMutex, INFINITE);//���ؽ� ����
	//	clientSocks[clientCount++] = clientSock;//Ŭ���̾�Ʈ ���Ϲ迭�� ��� ������ ���� �ּҸ� ����
	//	ReleaseMutex(hMutex);//���ؽ� ����
	//	//_beginthread(DoIt, 0, (void*)clientSock);
	//	//hThread = (HANDLE)_beginthreadex(NULL, 0, HandleClient, (void*)&clientSock, 0, NULL);//HandleClient ������ ����, clientSock�� �Ű������� ����
	//	hThread = (HANDLE)_beginthreadex(NULL, 0, HandleClient, (void*)&clientSock, 0, NULL);//HandleClient ������ ����, clientSock�� �Ű������� ����
	//	_beginthread(DoIt, 0, (void*)clientSock);
	//	printf("Connected Client IP : %s\n", inet_ntoa(clientAddr.sin_addr));
	//	
	//}


	for (int i = 0; i < totalNumber; i++) {
		clientAddrSize = sizeof(clientAddr);
		clientSock = accept(serverSock, (SOCKADDR*)&clientAddr, &clientAddrSize);//�������� ���޵� Ŭ���̾�Ʈ ������ clientSock�� ����
		WaitForSingleObject(hMutex, INFINITE);//���ؽ� ����
		clientSocks[clientCount++] = clientSock;//Ŭ���̾�Ʈ ���Ϲ迭�� ��� ������ ���� �ּҸ� ����
		ReleaseMutex(hMutex);//���ؽ� ����
		hThread = (HANDLE)_beginthreadex(NULL, 0, HandleClient, (void*)&clientSock, 0, NULL);//HandleClient ������ ����, clientSock�� �Ű������� ����
		printf("Connected Client IP : %s\n", inet_ntoa(clientAddr.sin_addr));
	}

	char msg[2];
	int strLen = 0;
	while ((strLen = recv(clientSock, msg, sizeof(msg), 0)) != 0) {
		SendMsg(msg, strLen);
	}

	closesocket(serverSock);//������ ������ ����.
	WSACleanup();//������ ������ �����ϰڴٴ� ����� �ü���� ����
}

void DoIt(void *param)
{
	char name[10];
	SOCKET sock = (SOCKET)param;
	recv(clientSocks[clientCount], name, sizeof(name), 0);
	sprintf(playerName[clientCount], "%s", name);
}

unsigned WINAPI HandleClient(void* arg) {
	int n, tmp;
	int num[4] = { 0,1,2,3 };
	char number[4][2];

	srand(time(NULL));
	for (int i = total - 1; i > 0; i--) {
		n = rand() % total;
		tmp = num[i];
		num[i] = num[n];
		num[n] = tmp;
	}

	for (int i = 0; i < total; i++) {
		printf("num[%d]=%d\t", i, num[i]);
		itoa(num[i], number[i], 10);
		printf("number[%d]=%s\n", i, number[i]);
	}

	if (clientSocks[total-2] != NULL) {
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
	}
	return 0;
}

//unsigned WINAPI HandleClient(void* arg) {
//	SOCKET clientSock = *((SOCKET*)arg); //�Ű������ι��� Ŭ���̾�Ʈ ������ ����
//	int strLen = 0, i;
//	char msg[BUF_SIZE];
//
//	while ((strLen = recv(clientSock, msg, sizeof(msg), 0)) != 0) { //Ŭ���̾�Ʈ�κ��� �޽����� ���������� ��ٸ���.
//		if (!strcmp(msg, "q")) {
//			send(clientSock, "q", 1, 0);
//			break;
//		}
//		SendMsg(msg, strLen);//SendMsg�� ���� �޽����� �����Ѵ�.
//	}
//
//	printf("client left the chat\n");
//	//�� ���� �����Ѵٴ� ���� �ش� Ŭ���̾�Ʈ�� �����ٴ� ����� ���� �ش� Ŭ���̾�Ʈ�� �迭���� �����������
//	WaitForSingleObject(hMutex, INFINITE);//���ؽ� ����
//	for (i = 0; i<clientCount; i++) {//�迭�� ������ŭ
//		if (clientSock == clientSocks[i]) {//���� ���� clientSock���� �迭�� ���� ���ٸ�
//			while (i++<clientCount - 1)//Ŭ���̾�Ʈ ���� ��ŭ
//				clientSocks[i] = clientSocks[i + 1];//������ �����.
//			break;
//		}
//	}
//	clientCount--;//Ŭ���̾�Ʈ ���� �ϳ� ����
//	ReleaseMutex(hMutex);//���ؽ� ����
//	closesocket(clientSock);//������ �����Ѵ�.
//	return 0;
//}

void SendMsg(char* msg, int len) { //�޽����� ��� Ŭ���̾�Ʈ���� ������.
	int i;
	WaitForSingleObject(hMutex, INFINITE);//���ؽ� ����
	for (i = 0; i<clientCount; i++)//Ŭ���̾�Ʈ ������ŭ
		send(clientSocks[i], msg, len, 0);//Ŭ���̾�Ʈ�鿡�� �޽����� �����Ѵ�.
	ReleaseMutex(hMutex);//���ؽ� ����
}

void ErrorHandling2(char* msg) {
	fputs(msg, stderr);
	fputc('\n', stderr);
	exit(1);
}