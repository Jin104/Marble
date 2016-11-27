#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include <process.h>
#include "Client.h"

#define BUF_SIZE 100
#define NAME_SIZE 20

unsigned WINAPI SendMsg(void* arg);//������ �����Լ�
unsigned WINAPI RecvMsg(void* arg);//������ �����Լ�
void ErrorHandling(char* msg);

char name[NAME_SIZE] = "[DEFAULT]";
char msg[BUF_SIZE];

void AccessServerClient(char *ip) {
	WSADATA wsaData;
	SOCKET sock;
	SOCKADDR_IN serverAddr;
	HANDLE sendThread, recvThread;

	char myIp[20];
	char port[100];
	char inputName[100];

	//sprintf(myIp, "%s", ip);
	//printf("ip: %s\n", myIp);
	printf("Input IP : ");
	gets_s(myIp);

	printf("Input your name : ");
	gets_s(inputName);

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)// ������ ������ ����Ѵٰ� �ü���� �˸�
		ErrorHandling("WSAStartup() error!");

	sprintf(name, "[%s]", inputName);
	sock = socket(PF_INET, SOCK_STREAM, 0);//������ �ϳ� �����Ѵ�.

	memset(&serverAddr, 0, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = inet_addr(myIp);
	//serverAddr.sin_addr.S_un.S_addr = inet_addr("110.15.82.167");
	//serverAddr.sin_addr.S_un.S_addr = inet_addr("192.168.0.2");
	serverAddr.sin_port = htons(10201);
	if (connect(sock, (SOCKADDR*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)//������ �����Ѵ�.
		ErrorHandling("connect() error");

	//���ӿ� �����ϸ� �� �� �Ʒ��� ����ȴ�.

	sendThread = (HANDLE)_beginthreadex(NULL, 0, SendMsg, (void*)&sock, 0, NULL);//�޽��� ���ۿ� �����尡 ����ȴ�.
	recvThread = (HANDLE)_beginthreadex(NULL, 0, RecvMsg, (void*)&sock, 0, NULL);//�޽��� ���ſ� �����尡 ����ȴ�.

	WaitForSingleObject(sendThread, INFINITE);//���ۿ� �����尡 �����ɶ����� ��ٸ���./
	WaitForSingleObject(recvThread, INFINITE);//���ſ� �����尡 �����ɶ����� ��ٸ���.
											  //Ŭ���̾�Ʈ�� ���Ḧ �õ��Ѵٸ� ���� �Ʒ��� ����ȴ�.
	closesocket(sock);//������ �����Ѵ�.
	WSACleanup();//������ ���� ��������� �ü���� �˸���.
	return;
}

unsigned WINAPI SendMsg(void* arg) {//���ۿ� �������Լ�
	SOCKET sock = *((SOCKET*)arg);//������ ������ �����Ѵ�.
	char nameMsg[NAME_SIZE + BUF_SIZE];
	while (1) {//�ݺ�
		fgets(msg, BUF_SIZE, stdin);//�Է��� �޴´�.
		if (!strcmp(msg, "q\n")) {//q�� �Է��ϸ� �����Ѵ�.
			send(sock, "q", 1, 0);//nameMsg�� �������� �����Ѵ�.
		}
		sprintf(nameMsg, "%s %s", name, msg);//nameMsg�� �޽����� �����Ѵ�.
		send(sock, nameMsg, strlen(nameMsg), 0);//nameMsg�� �������� �����Ѵ�.
	}
	return 0;
}

unsigned WINAPI RecvMsg(void* arg) {
	SOCKET sock = *((SOCKET*)arg);//������ ������ �����Ѵ�.
	char nameMsg[NAME_SIZE + BUF_SIZE];
	int strLen;
	while (1) {//�ݺ�
		strLen = recv(sock, nameMsg, NAME_SIZE + BUF_SIZE - 1, 0);//�����κ��� �޽����� �����Ѵ�.
		if (strLen == -1)
			return -1;
		nameMsg[strLen] = 0;//���ڿ��� ���� �˸��� ���� ����
		if (!strcmp(nameMsg, "q")) {
			printf("left the chat\n");
			closesocket(sock);
			exit(0);
		}
		fputs(nameMsg, stdout);//�ڽ��� �ֿܼ� ���� �޽����� ����Ѵ�.
	}
	return 0;
}

void ErrorHandling(char* msg) {
	fputs(msg, stderr);
	fputc('\n', stderr);
	exit(1);
}