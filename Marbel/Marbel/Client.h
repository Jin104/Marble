#pragma once

#pragma comment (lib,"ws2_32")

SOCKET NewTCPSocket();
void AccessServerClient(char *ip, int totalNumber);
void NewServer(int totalNumber);

void SendMsg(char* msg, int len, int index);//쓰레드 전송함수