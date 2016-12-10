#include <stdlib.h>
#include <string.h>
#include <process.h>
#include <WinSock2.h>
#include "start.h"
#include "Client.h"
#define BUF_SIZE 100
#define MAX_CLNT 256

int serverNumber;

unsigned WINAPI HandleClient(void* arg);//쓰레드 함수
void ErrorHandling2(char* msg);

int clientCount = 0;
int total = 0;
char playerName[4][10];
SOCKET clientSocks[MAX_CLNT];//클라이언트 소켓 보관용 배열
HANDLE hMutex;//뮤텍스
SOCKET serverSock, clientSock;

void NewServer(int totalNumber) {	//방의 인원수 받아옴~
	
	WSADATA wsaData;
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

	clientSocks[clientCount++] = serverSock;

	printf("listening...\n");

	for (int i = 1; i < totalNumber; i++) {
		clientAddrSize = sizeof(clientAddr);
		clientSock = accept(serverSock, (SOCKADDR*)&clientAddr, &clientAddrSize);//서버에게 전달된 클라이언트 소켓을 clientSock에 전달
		WaitForSingleObject(hMutex, INFINITE);//뮤텍스 실행
		clientSocks[clientCount++] = clientSock;//클라이언트 소켓배열에 방금 가져온 소켓 주소를 전달
		ReleaseMutex(hMutex);//뮤텍스 중지
		printf("Connected Client IP : %s\n", inet_ntoa(clientAddr.sin_addr));
	}

	hThread = (HANDLE)_beginthreadex(NULL, 0, HandleClient, (void*)&clientSock, 0, NULL);//HandleClient 쓰레드 실행, clientSock을 매개변수로 전달

	while (1)
	{

	}
	closesocket(serverSock);//생성한 소켓을 끈다.
	WSACleanup();//윈도우 소켓을 종료하겠다는 사실을 운영체제에 전달
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
		serverNumber = num[0];
		StartGame(total, serverNumber, "0", (void *)clientSocks, true);
	}

	return 0;
}

void SendMsg(char* msg, int len, int index) { //메시지를 모든 클라이언트에게 보낸다.
	int i;
	WaitForSingleObject(hMutex, INFINITE);//뮤텍스 실행
	for (i = 0; i < clientCount; i++)//클라이언트 개수만큼
	{
		if (i == index)
		{
			continue;
		}
		send(clientSocks[i], msg, len, 0);//클라이언트들에게 메시지를 전달한다.
	}
	ReleaseMutex(hMutex);//뮤텍스 중지
}

void ErrorHandling2(char* msg) {
	fputs(msg, stderr);
	fputc('\n', stderr);
	exit(1);
}