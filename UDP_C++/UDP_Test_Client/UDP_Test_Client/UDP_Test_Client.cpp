#include<WINSOCK2.H>
#include <WS2tcpip.h>
#include<iostream>
#pragma comment(lib,"WS2_32.lib")
using namespace std;
int main()
{
	WSADATA wsaData;//初始化
	SOCKET SendSocket;
	sockaddr_in RecvAddr;//服务器地址
	int Port = 4000;//服务器监听地址
	char SendBuf[1024]="hello";//发送数据的缓冲区
	int BufLen = 1024;//缓冲区大小
	//初始化Socket
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	//创建Socket对象
	SendSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	//设置服务器地址
	RecvAddr.sin_family = AF_INET;
	RecvAddr.sin_port = htons(Port);
	RecvAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	//向服务器发送数据报
	printf("Sending a datagram to the receiver...\n");
	sendto(SendSocket, SendBuf, BufLen, 0, (SOCKADDR*)& RecvAddr, sizeof(RecvAddr));
	//发送完成，关闭Socket
	printf("finished sending,close socket.\n");
	closesocket(SendSocket);
	printf("Exting.\n");
	WSACleanup();
	return 0;
}