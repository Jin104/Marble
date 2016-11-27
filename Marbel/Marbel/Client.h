#pragma once

//#include <WinSock2.h>
#pragma comment (lib,"ws2_32")

SOCKET NewTCPSocket();
void AccessServerClient(char *ip);
void NewServer();