#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <process.h>
#include <Windows.h>
#include "Client.h"

void ErrorHandling1(char* msg);

SOCKET NewTCPSocket() {
	
	char myIp[100];
	char inputName[100];

	/*���� �ʱ�ȭ*/
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		ErrorHandling1("WSAStartup() error!");

	/*���� ip �Է�*/
	printf("Input TCP server IP : ");
	gets_s(myIp);

	/*���� ����*/
	SOCKET sock;
	sock = socket(PF_INET, SOCK_STREAM, 0);

	/*�ʱ�ȭ*/
	//������ �����̶� ���� ���� ��Ʈ��ũ �������̽��� ����
	SOCKADDR_IN serverAddr;
	memset(&serverAddr, 0, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = inet_addr(myIp);
	serverAddr.sin_port = htons(10200);

	/*������ �����û*/
	if (connect(sock, (SOCKADDR*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)
		ErrorHandling1("connect() error");

	return sock;
}

void ErrorHandling1(char* msg) {
	fputs(msg, stderr);
	fputc('\n', stderr);
	exit(1);
}