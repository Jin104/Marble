#pragma once

//#include <WinSock2.h>
#pragma comment (lib,"ws2_32")

SOCKET NewTCPSocket();
void AccessServerClient(char *ip, int totalNumber);
void AccessServerClient2(void* totalNumber);
void NewServer(int totalNumber);
void NewServer2(void* totalNumber);

unsigned WINAPI SendMsg(void* arg);//쓰레드 전송함수
unsigned WINAPI RecvMsg(void* arg);//쓰레드 수신함수