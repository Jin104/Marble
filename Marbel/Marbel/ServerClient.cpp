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

unsigned WINAPI HandleClient(void* arg);//쓰레드 함수
void SendMsg(char* msg, int len);//메시지 보내는 함수
void ErrorHandling2(char* msg);

int clientCount = 0;
int total = 0;
char playerName[4][10];
SOCKET clientSocks[MAX_CLNT];//클라이언트 소켓 보관용 배열
HANDLE hMutex;//뮤텍스

void NewServer(int totalNumber) {	//방의 인원수 받아옴~
	
	WSADATA wsaData;
	SOCKET serverSock, clientSock;
	SOCKADDR_IN serverAddr, clientAddr;
	int clientAddrSize;
	HANDLE hThread, sThread, rThread;
	
	
	total = totalNumber;
	
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) //윈도우 소켓을 사용하겠다는 사실을 운영체제에 전달
		ErrorHandling2("WSAStartup() error!");

	hMutex = CreateMutex(NULL, FALSE, NULL);//하나의 뮤텍스를 생성한다.
	serverSock = socket(PF_INET, SOCK_STREAM, 0); //하나의 소켓을 생성한다.

	memset(&serverAddr, 0, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	//serverAddr.sin_addr.S_un.S_addr = inet_addr("192.168.0.26");
	serverAddr.sin_port = htons(10201);

	if (bind(serverSock, (SOCKADDR*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) //생성한 소켓을 배치한다.
		ErrorHandling2("bind() error");
	if (listen(serverSock, totalNumber) == SOCKET_ERROR)//소켓을 준비상태에 둔다.	//백로그큐 몇명까지 받느냐
		ErrorHandling2("listen() error");

	printf("listening...\n");

	//while (1) {
	//	clientAddrSize = sizeof(clientAddr);
	//	clientSock = accept(serverSock, (SOCKADDR*)&clientAddr, &clientAddrSize);//서버에게 전달된 클라이언트 소켓을 clientSock에 전달
	//	WaitForSingleObject(hMutex, INFINITE);//뮤텍스 실행
	//	clientSocks[clientCount++] = clientSock;//클라이언트 소켓배열에 방금 가져온 소켓 주소를 전달
	//	ReleaseMutex(hMutex);//뮤텍스 중지
	//	//_beginthread(DoIt, 0, (void*)clientSock);
	//	//hThread = (HANDLE)_beginthreadex(NULL, 0, HandleClient, (void*)&clientSock, 0, NULL);//HandleClient 쓰레드 실행, clientSock을 매개변수로 전달
	//	hThread = (HANDLE)_beginthreadex(NULL, 0, HandleClient, (void*)&clientSock, 0, NULL);//HandleClient 쓰레드 실행, clientSock을 매개변수로 전달
	//	_beginthread(DoIt, 0, (void*)clientSock);
	//	printf("Connected Client IP : %s\n", inet_ntoa(clientAddr.sin_addr));
	//	
	//}


	for (int i = 0; i < totalNumber; i++) {
		clientAddrSize = sizeof(clientAddr);
		clientSock = accept(serverSock, (SOCKADDR*)&clientAddr, &clientAddrSize);//서버에게 전달된 클라이언트 소켓을 clientSock에 전달
		WaitForSingleObject(hMutex, INFINITE);//뮤텍스 실행
		clientSocks[clientCount++] = clientSock;//클라이언트 소켓배열에 방금 가져온 소켓 주소를 전달
		ReleaseMutex(hMutex);//뮤텍스 중지
		hThread = (HANDLE)_beginthreadex(NULL, 0, HandleClient, (void*)&clientSock, 0, NULL);//HandleClient 쓰레드 실행, clientSock을 매개변수로 전달
		printf("Connected Client IP : %s\n", inet_ntoa(clientAddr.sin_addr));
	}

	char msg[2];
	int strLen = 0;
	while ((strLen = recv(clientSock, msg, sizeof(msg), 0)) != 0) {
		SendMsg(msg, strLen);
	}

	closesocket(serverSock);//생성한 소켓을 끈다.
	WSACleanup();//윈도우 소켓을 종료하겠다는 사실을 운영체제에 전달
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
		printf("전송시작\n");
		for (int i = 0; i < total; i++) {
			printf("시작신호보냄\n");
			send(clientSocks[i], "9", sizeof("9"), 0);	//시작메세지
			for (int j = 0; j < total; j++) {
				send(clientSocks[i], number[j], sizeof(number[j]), 0);	//순서
				//send(clientSocks[i], playerName[j], sizeof(playerName[j]), 0);	//순서
			}
			send(clientSocks[i], number[i], sizeof(number[i]), 0);	//순서
		}
	}
	return 0;
}

//unsigned WINAPI HandleClient(void* arg) {
//	SOCKET clientSock = *((SOCKET*)arg); //매개변수로받은 클라이언트 소켓을 전달
//	int strLen = 0, i;
//	char msg[BUF_SIZE];
//
//	while ((strLen = recv(clientSock, msg, sizeof(msg), 0)) != 0) { //클라이언트로부터 메시지를 받을때까지 기다린다.
//		if (!strcmp(msg, "q")) {
//			send(clientSock, "q", 1, 0);
//			break;
//		}
//		SendMsg(msg, strLen);//SendMsg에 받은 메시지를 전달한다.
//	}
//
//	printf("client left the chat\n");
//	//이 줄을 실행한다는 것은 해당 클라이언트가 나갔다는 사실임 따라서 해당 클라이언트를 배열에서 제거해줘야함
//	WaitForSingleObject(hMutex, INFINITE);//뮤텍스 실행
//	for (i = 0; i<clientCount; i++) {//배열의 갯수만큼
//		if (clientSock == clientSocks[i]) {//만약 현재 clientSock값이 배열의 값과 같다면
//			while (i++<clientCount - 1)//클라이언트 개수 만큼
//				clientSocks[i] = clientSocks[i + 1];//앞으로 땡긴다.
//			break;
//		}
//	}
//	clientCount--;//클라이언트 개수 하나 감소
//	ReleaseMutex(hMutex);//뮤텍스 중지
//	closesocket(clientSock);//소켓을 종료한다.
//	return 0;
//}

void SendMsg(char* msg, int len) { //메시지를 모든 클라이언트에게 보낸다.
	int i;
	WaitForSingleObject(hMutex, INFINITE);//뮤텍스 실행
	for (i = 0; i<clientCount; i++)//클라이언트 개수만큼
		send(clientSocks[i], msg, len, 0);//클라이언트들에게 메시지를 전달한다.
	ReleaseMutex(hMutex);//뮤텍스 중지
}

void ErrorHandling2(char* msg) {
	fputs(msg, stderr);
	fputc('\n', stderr);
	exit(1);
}