#include<WINSOCK2.H>
#include<iostream>
#pragma comment(lib,"WS2_32.lib")
using namespace std;
int main()
{
	WSADATA wsaData;//��ʼ��
	SOCKET RecvSocket;
	sockaddr_in RecvAddr;//��������ַ
	int Port = 4000;//������������ַ
	char RecvBuf[1024];//�������ݵĻ�����
	int BufLen = 1024;//��������С
	sockaddr_in SenderAddr;
	int SenderAddrSize = sizeof(SenderAddr);
	printf("receiving datagrams...\n");
	while (1) {
		//��ʼ��Socket
		WSAStartup(MAKEWORD(2, 2), &wsaData);
		//�����������ݱ���socket
		RecvSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
		//��socket���ƶ��˿ں�0.0.0.0��
		RecvAddr.sin_family = AF_INET;
		RecvAddr.sin_port = htons(Port);
		RecvAddr.sin_addr.s_addr = htonl(INADDR_ANY);
		bind(RecvSocket, (SOCKADDR*)& RecvAddr, sizeof(RecvAddr));
		//����Recvfrom�����ڰ󶨵�socket�Ͻ�������
		/*printf("receiving datagrams...\n");*/

		recvfrom(RecvSocket, RecvBuf, BufLen, 0, (SOCKADDR*)& SenderAddr, &SenderAddrSize);
		printf(RecvBuf);
		//�ر�socket��������������
		/*printf("finished receiving,closing socket..\n");*/
		closesocket(RecvSocket);
		//�ͷ���Դ���˳�
		/*printf("Exiting.\n");*/
		WSACleanup();
	}
	return 0;
}