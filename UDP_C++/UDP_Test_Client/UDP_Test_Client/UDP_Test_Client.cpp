#include<WINSOCK2.H>
#include <WS2tcpip.h>
#include<iostream>
#pragma comment(lib,"WS2_32.lib")
using namespace std;
int main()
{
	WSADATA wsaData;//��ʼ��
	SOCKET SendSocket;
	sockaddr_in RecvAddr;//��������ַ
	int Port = 4000;//������������ַ
	char SendBuf[1024]="hello";//�������ݵĻ�����
	int BufLen = 1024;//��������С
	//��ʼ��Socket
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	//����Socket����
	SendSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	//���÷�������ַ
	RecvAddr.sin_family = AF_INET;
	RecvAddr.sin_port = htons(Port);
	RecvAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	//��������������ݱ�
	printf("Sending a datagram to the receiver...\n");
	sendto(SendSocket, SendBuf, BufLen, 0, (SOCKADDR*)& RecvAddr, sizeof(RecvAddr));
	//������ɣ��ر�Socket
	printf("finished sending,close socket.\n");
	closesocket(SendSocket);
	printf("Exting.\n");
	WSACleanup();
	return 0;
}