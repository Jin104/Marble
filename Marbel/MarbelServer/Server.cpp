#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include <process.h>
#include "Room.h"

#pragma comment (lib,"ws2_32")

LinkedList *list = NewList();

void ErrorHandling(char* msg);   //�����޼��� ���
void DoIt(void *param);
int client_number = 0; //������ ��

void main()
{
	/*���� �ʱ�ȭ*/
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		ErrorHandling("WSAStartup() error!");

	/*���� ����*/
	SOCKET serverSock;
	serverSock = socket(PF_INET, SOCK_STREAM, 0);

	/*�ʱ�ȭ*/
	//������ �����̶� ���� ���� ��Ʈ��ũ �������̽��� ����
	SOCKADDR_IN serverAddr;
	memset(&serverAddr, 0, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	//serverAddr.sin_addr.S_un.S_addr = inet_addr("192.168.0.26");
	serverAddr.sin_port = htons(10200);

	/*������ ���� ��ġ*/
	if (bind(serverSock, (SOCKADDR*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) //������ ������ ��ġ�Ѵ�.
		ErrorHandling("bind() error");

	/*��α� ť ũ�� ����*/   //���ÿ� ������ �޴���
	if (listen(serverSock, 50) == SOCKET_ERROR)
		ErrorHandling("listen() error");

	/*����*/
	printf("listening...\n");

	SOCKET clientSock;   //Ŭ���̾�Ʈ�� �ۼ��� �ϱ� ���� ����
	SOCKADDR_IN clientAddr; //���� ��û�� Ŭ���̾�Ʈ�� ���� �ּҸ� ���� ����
	int clientLen = sizeof(clientAddr);   //���� �ּ� ���� ũ��

										  //printf("ip: %ld\n", serverAddr.sin_addr.S_un.S_addr);

	while (1) {

		/*�������� ���޵� Ŭ���̾�Ʈ ����*/
		clientSock = accept(serverSock, (SOCKADDR*)&clientAddr, &clientLen);
		printf("Connected Client IP : %s\n", inet_ntoa(clientAddr.sin_addr));
		_beginthread(DoIt, 0, (void*)clientSock);
	}

}

void ErrorHandling(char* msg) {
	fputs(msg, stderr);
	fputc('\n', stderr);
	exit(1);
}

void DoIt(void *param) {

	char select[2];   //Ŭ���̾�Ʈ�� ����
	char roomNum[5];
	char roomName[256];   //�� �̸�
	char message[256];
	int roomCount;   //�� ����
	char ip[20];
	Node *pos, *node;

	SOCKET sock = (SOCKET)param;
	SOCKADDR_IN sockAddr;
	int len = sizeof(sockAddr);

	//�÷��̾ ���� �Ҷ����� ����ó��
	if (recv(sock, select, sizeof(select), 0) == -1) {
		printf("�÷��̾ �����Ͽ����ϴ�.\n");
		client_number--;
	}

	pos = list->head;
	while (pos != NULL) {
		if (atoi(pos->allNum) == pos->num) { //���ο����� ���� �ο����� ������
			DeletNode(list, pos); //�� ����
			modiNum(list); //�� �����ɶ����� �� ��ȣ ����
			break;
		}
		pos = pos->next;
	}

	switch (atoi(select)) {
	case 1:
		getpeername(sock, (SOCKADDR*)&sockAddr, &len);
		//���ο� �� ���� �޾ƿ�
		if (recv(sock, select, sizeof(select), 0) == -1) {
			printf("�÷��̾ �����Ͽ����ϴ�.\n");
			client_number--;
			break;
		}

		printf("\n%d�ο� �� ����...\n", atoi(select));
		printf("���� ���� Ŭ���̾�Ʈ�� IP [%s]\n", inet_ntoa(sockAddr.sin_addr));
		if (recv(sock, roomName, sizeof(roomName), 0) == -1) {
			printf("�÷��̾ �����Ͽ����ϴ�.\n");
			client_number--;
			break;
		}
		recv(sock, ip, sizeof(ip), 0);	//����ip
		node = NewNode(roomName, select, 1, inet_ntoa(sockAddr.sin_addr), ip);            //���� �ο��� ���� ����x
		HangNode(list, node);
		printf("sockAddr : %s\n", node->ip);	//�ܺ�ip
		sprintf(message, "���� �����߽��ϴ�.");
		send(sock, message, sizeof(message), 0);

		break;
	case 2:
		roomCount = list->size;
		sprintf(select, "%d", roomCount);
		send(sock, select, sizeof(select), 0);
		pos = list->head;
		printf("\n=========== �� ��� ===========\n");
		while (pos != NULL) {
			send(sock, pos->name, sizeof(pos->name), 0);
			sprintf(roomNum, "%d", pos->num);
			send(sock, roomNum, sizeof(roomNum), 0);
			send(sock, pos->allNum, sizeof(pos->allNum), 0);
			printf("%d��° �� [�� �̸�: %s\t���� �ο���: %d\t���ο���: %s]\n", pos->number, pos->name, pos->num, pos->allNum);
			pos = pos->next;
		}

		if (recv(sock, select, sizeof(select), 0) == -1) {
			printf("�÷��̾ �����Ͽ����ϴ�.\n");
			client_number--;
			break;
		}
		node = FindNode(list, atoi(select));
		send(sock, node->ip, sizeof(node->ip), 0);
		send(sock, node->innerIp, sizeof(node->innerIp), 0);
		modiNode(list, node);

		break;
	default:
		break;
	}

	closesocket(sock);
}