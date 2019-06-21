#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <WinSock2.h>
#include <stdio.h>
#pragma comment(lib, "ws2_32.lib")
void ERRMSG(const char* msg)
{
	void* IpMsgBuf;
	FormatMessageA(
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(char*)&IpMsgBuf, 0, NULL
	);
	MessageBoxA(NULL, (char*)IpMsgBuf, msg, MB_OK);
	return;
}
