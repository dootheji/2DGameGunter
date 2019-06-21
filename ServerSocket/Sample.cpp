#include "syServerStd.h"

void main()
{
	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa);

	SOCKET listensock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	SOCKADDR_IN sa;
	ZeroMemory(&sa, sizeof(sa));
	sa.sin_family = AF_INET;
	sa.sin_port = htons(10000);	//포트번호 host to network short
	sa.sin_addr.s_addr = htonl(INADDR_ANY); //지정된 아이피로만 받고싶으면 지정해줘야 함
	//sa.sin_zero[8];
	int ret = bind(listensock, (SOCKADDR*)&sa, sizeof(sa));
	if (ret == SOCKET_ERROR)
	{
		ERRMSG("bind");
		return;
	}

	ret = listen(listensock, SOMAXCONN);
	if (ret == SOCKET_ERROR)
	{
		ERRMSG("listen");
		return;
	}

	SOCKADDR_IN clientaddr;
	int addlen = sizeof(SOCKADDR_IN);
	SOCKET clientsock;
	while (1)
	{
		printf("\nExit : enter\n");
		clientsock = accept(listensock, (SOCKADDR*)&clientaddr, &addlen);
		if (clientsock == INVALID_SOCKET)
		{
			ERRMSG("ACCEPT");
			break;
		}
		printf("\n접속[%s][%d]", 
			inet_ntoa(clientaddr.sin_addr),
			ntohs(clientaddr.sin_port));

		char recvbuf[256] = { 0, };
		int iRecvByte = recv(clientsock, recvbuf, 256, 0);
		if (iRecvByte == 0 )
		{
			printf("\n접속종료 [%s][%d]",
				inet_ntoa(clientaddr.sin_addr),
				ntohs(clientaddr.sin_port));
			break;
		}

		if (iRecvByte == SOCKET_ERROR)
		{
			ERRMSG("receive");
			break;
		}


		printf("\n%s", recvbuf);

		int SendByte = send(clientsock, recvbuf, strlen(recvbuf), 0);
		if (SendByte == 0 || SendByte == SOCKET_ERROR)
		{
			ERRMSG("send");
			break;
		}		
		closesocket(clientsock);
	}

	closesocket(listensock);
	

	WSACleanup();
}