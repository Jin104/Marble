#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include <process.h>
#include "Room.h"

#pragma comment (lib,"ws2_32")

LinkedList *list = NewList();

void ErrorHandling(char* msg);   //에러메세지 출력
void DoIt(void *param);
int client_number = 0; //접속자 수

void main()
{
	/*윈속 초기화*/
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		ErrorHandling("WSAStartup() error!");

	/*소켓 생성*/
	SOCKET serverSock;
	serverSock = socket(PF_INET, SOCK_STREAM, 0);

	/*초기화*/
	//생성한 소켓이랑 내부 로컬 네트워크 인터페이스와 결합
	SOCKADDR_IN serverAddr;
	memset(&serverAddr, 0, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	//serverAddr.sin_addr.S_un.S_addr = inet_addr("192.168.0.26");
	serverAddr.sin_port = htons(10200);

	/*생성한 소켓 배치*/
	if (bind(serverSock, (SOCKADDR*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) //생성한 소켓을 배치한다.
		ErrorHandling("bind() error");

	/*백로그 큐 크기 설정*/   //동시에 몇명까지 받느냐
	if (listen(serverSock, 50) == SOCKET_ERROR)
		ErrorHandling("listen() error");

	/*연결*/
	printf("listening...\n");

	SOCKET clientSock;   //클라이언트와 송수신 하기 위한 소켓
	SOCKADDR_IN clientAddr; //접속 요청한 클라이언트의 소켓 주소를 담을 변수
	int clientLen = sizeof(clientAddr);   //소켓 주소 버퍼 크기

										  //printf("ip: %ld\n", serverAddr.sin_addr.S_un.S_addr);

	while (1) {

		/*서버에게 전달된 클라이언트 소켓*/
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

	char select[2];   //클라이언트의 선택
	char roomNum[5];
	char roomName[256];   //방 이름
	char message[256];
	int roomCount;   //방 개수
	char ip[20];
	Node *pos, *node;

	SOCKET sock = (SOCKET)param;
	SOCKADDR_IN sockAddr;
	int len = sizeof(sockAddr);

	//플레이어가 퇴장 할때마다 예외처리
	if (recv(sock, select, sizeof(select), 0) == -1) {
		printf("플레이어가 퇴장하였습니다.\n");
		client_number--;
	}

	pos = list->head;
	while (pos != NULL) {
		if (atoi(pos->allNum) == pos->num) { //총인원수와 현재 인원수가 같으면
			DeletNode(list, pos); //방 삭제
			modiNum(list); //방 삭제될때마다 방 번호 수정
			break;
		}
		pos = pos->next;
	}

	switch (atoi(select)) {
	case 1:
		getpeername(sock, (SOCKADDR*)&sockAddr, &len);
		//몇인용 방 인지 받아옴
		if (recv(sock, select, sizeof(select), 0) == -1) {
			printf("플레이어가 퇴장하였습니다.\n");
			client_number--;
			break;
		}

		printf("\n%d인용 방 생성...\n", atoi(select));
		printf("방을 만든 클라이언트의 IP [%s]\n", inet_ntoa(sockAddr.sin_addr));
		if (recv(sock, roomName, sizeof(roomName), 0) == -1) {
			printf("플레이어가 퇴장하였습니다.\n");
			client_number--;
			break;
		}
		recv(sock, ip, sizeof(ip), 0);	//내부ip
		node = NewNode(roomName, select, 1, inet_ntoa(sockAddr.sin_addr), ip);            //현재 인원은 아직 구현x
		HangNode(list, node);
		printf("sockAddr : %s\n", node->ip);	//외부ip
		sprintf(message, "방을 생성했습니다.");
		send(sock, message, sizeof(message), 0);

		break;
	case 2:
		roomCount = list->size;
		sprintf(select, "%d", roomCount);
		send(sock, select, sizeof(select), 0);
		pos = list->head;
		printf("\n=========== 방 목록 ===========\n");
		while (pos != NULL) {
			send(sock, pos->name, sizeof(pos->name), 0);
			sprintf(roomNum, "%d", pos->num);
			send(sock, roomNum, sizeof(roomNum), 0);
			send(sock, pos->allNum, sizeof(pos->allNum), 0);
			printf("%d번째 방 [방 이름: %s\t현재 인원수: %d\t총인원수: %s]\n", pos->number, pos->name, pos->num, pos->allNum);
			pos = pos->next;
		}

		if (recv(sock, select, sizeof(select), 0) == -1) {
			printf("플레이어가 퇴장하였습니다.\n");
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