#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#include <ws2tcpip.h> 

#pragma comment(lib, "ws2_32.lib")

#define PORT (7777)
#define IP ("127.0.0.1")

#define _WINSOCK_DEPRECATED_NO_WARNINGS

int main() {

	WSADATA wsadata; // wsadata ���� ����
	SOCKET hSock;
	SOCKADDR_IN serv_addr;

	char send_message[1024] = "Hello!";


	// ���̺귯�� ��� Ȯ�� (���� �ش� ������ �ʱ�ȭ �� ���̺귯���� ������ ä����)
	WSAStartup(MAKEWORD(2, 2), &wsadata); // ����� ������ ���� ����, WSADATA ����ü ������ �ּҰ�


	//���� ���� (� ���������� ���� �������� ����� ������)
	if ((hSock = socket(PF_INET, SOCK_DGRAM, 0)) < 0) { // �������� ü��(IPv4), ���� ���(UDP), �������� ���� (���� �ڵ�)
		printf("socket failed\n");
		return -1;
	}


	// ����ü �ּ� ���� �ʱ�ȭ
	memset(&serv_addr, 0, sizeof(serv_addr)); // �޸� �ʱ�ȭ
	serv_addr.sin_family = AF_INET; // �ּ� ü��
	// sa_data�� 3���� �и� 
	serv_addr.sin_port = htons(PORT);
	inet_pton(AF_INET, IP, &(serv_addr.sin_addr));
	// sin_zero[8] ����Ʈ �� ���߱� ���� 0���� ä����


	printf("�Է� : ");
	gets(send_message);


	// send
	if (sendto(hSock, send_message, sizeof(send_message), 0, (SOCKADDR*)&serv_addr, sizeof(serv_addr)) < 0) {	
		printf("send failed.\n");
		return -3;
	}


	// ���ϴݱ�
	closesocket(hSock);

	// ���̺귯�� ��� ������ ��ȯ
	WSACleanup();


	return 0;
}