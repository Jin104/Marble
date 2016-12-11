#pragma once

//#include <WinSock2.h>
#pragma comment (lib,"ws2_32")

SOCKET NewTCPSocket();
void AccessServerClient(char *ip, char *innerIp, int totalNumber);
void NewServer(int totalNumber);

void SendMsg(char* msg, int len, int index);//쓰레드 전송함수