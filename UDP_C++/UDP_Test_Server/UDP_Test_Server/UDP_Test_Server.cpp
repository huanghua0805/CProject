#include<WINSOCK2.H>
#include<iostream>
#pragma comment(lib,"WS2_32.lib")
using namespace std;
int main()
{
	WSADATA wsaData;//初始化
	SOCKET RecvSocket;
	sockaddr_in RecvAddr;//服务器地址
	int Port = 4000;//服务器监听地址
	char RecvBuf[1024];//发送数据的缓冲区
	int BufLen = 1024;//缓冲区大小
	sockaddr_in SenderAddr;
	int SenderAddrSize = sizeof(SenderAddr);
	printf("receiving datagrams...\n");
	while (1) {
		//初始化Socket
		WSAStartup(MAKEWORD(2, 2), &wsaData);
		//创建接收数据报的socket
		RecvSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
		//将socket与制定端口和0.0.0.0绑定
		RecvAddr.sin_family = AF_INET;
		RecvAddr.sin_port = htons(Port);
		RecvAddr.sin_addr.s_addr = htonl(INADDR_ANY);
		bind(RecvSocket, (SOCKADDR*)& RecvAddr, sizeof(RecvAddr));
		//调用Recvfrom函数在绑定的socket上接收数据
		/*printf("receiving datagrams...\n");*/

		recvfrom(RecvSocket, RecvBuf, BufLen, 0, (SOCKADDR*)& SenderAddr, &SenderAddrSize);
		printf(RecvBuf);
		//关闭socket，结束接收数据
		/*printf("finished receiving,closing socket..\n");*/
		closesocket(RecvSocket);
		//释放资源，退出
		/*printf("Exiting.\n");*/
		WSACleanup();
	}
	return 0;
}