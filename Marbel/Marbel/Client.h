#pragma once

//#include <WinSock2.h>
#pragma comment (lib,"ws2_32")

SOCKET NewTCPSocket();
void AccessServerClient(char *ip, int totalNumber);
void NewServer(int totalNumber);

void SendMsg(char* msg, int len, int index);//������ �����Լ�
unsigned WINAPI RecvMsg(void* arg);//������ �����Լ�