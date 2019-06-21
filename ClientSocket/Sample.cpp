#include "syServerStd.h"
#include <conio.h>
void main()
{
	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa);

	SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	unsigned long iMode = 0;
	ioctlsocket(sock, FIONBIO, &iMode);	//ioctl 입출력컨트롤
	SOCKADDR_IN sa;
	ZeroMemory(&sa, sizeof(sa));
	sa.sin_family = AF_INET;
	sa.sin_port = htons(10000);	//포트번호 host to network short
	sa.sin_addr.s_addr = inet_addr("192.168.0.8");	//inet_addr : 문자열을 4byte로 바꿔줌
	sa.sin_zero[8];

	int ret = connect(sock, (SOCKADDR*)&sa, sizeof(sa));
	if (ret == SOCKET_ERROR)
	{

		ERRMSG("connect");
		return;

	}
	iMode = 1;
	ioctlsocket(sock, FIONBIO, &iMode);	//ioctl 입출력컨트롤

	char buf[256] = { 0, };
	int iEnd = 0;
	while (1)
	{
		printf("Exit : enter\n");
		if (_kbhit() == 1)
		{ 
			//if (buf[0] == '\n') break;
			int iValue = _getche();
			if (strlen(buf) ==0 && iValue == '\r') 
				break;
			if (iValue == '\r')
			{
				int iMsgSize = strlen(buf);
				int iSendByte = send(sock, buf, iMsgSize, 0);
				if (iSendByte == SOCKET_ERROR)
				{
					if (WSAGetLastError() != WSAEWOULDBLOCK)		//논블록소켓이라
					{
						ERRMSG("send");
						break;
					}
				}
				ZeroMemory(buf, sizeof(char) * 256);
				iEnd = 0;
			}
			else
			{
				if (iEnd < 255)
				{
					buf[iEnd++] = iValue;
				}
			}
		}
	
		else
		{
			char recvbuf[256] = { 0, };
			int iRecvByte = recv(sock, recvbuf, 256, 0);
			if (iRecvByte == 0)
			{
				break;
			}
			if ( iRecvByte == SOCKET_ERROR)
			{
				if (WSAGetLastError() != WSAEWOULDBLOCK)		//논블록소켓이라
				{
					printf("서버 종료!");
					break;
				}
				continue;
			}
		//	recvbuf[iRecvByte] = '\n';
			printf("%s", recvbuf);
		}
	}
	closesocket(sock);


	WSACleanup();
}