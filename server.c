#include <winsock2.h>
#include <stdlib.h>
#include <stdio.h>

#pragma comment(lib, "ws2_32.lib")

#define PORT (7777)

#pragma warning(disable:4996)


/* ����ü �м� ����
sockaddr_in = SOCKADDR_IN

struct sockaddr_in
{
	sa_family_t    sin_family;  �ּ�ü��(Address Family)
	uint16_t       sin_port;    16��Ʈ TCP/UDP PORT��ȣ
	struct in_addr sin_addr;    32��Ʈ�� IP�ּ�
	char           sin_zero[8]; ������ ���� -> ??
}


struct sockaddr = SOCKADDR

struct sockaddr
{
	sa_family_t sin_family    �ּ�ü��(Address Family)
	char        sa_data[14];  �ּ�����
}
*/


int main() {

	WSADATA wsadata; // wsadata ���� ����
	SOCKET hServer_Sock, hClient_sock;
	SOCKADDR_IN serv_addr, client_Addr;

	char read_message[1024];


	// ���̺귯�� ��� Ȯ�� (���� �ش� ������ �ʱ�ȭ �� ���̺귯���� ������ ä����)
	WSAStartup(MAKEWORD(2, 2), &wsadata); // ����� ������ ���� ����, WSADATA ����ü ������ �ּҰ�


	//���� ���� ���� (� ���������� ���� �������� ����� ������)
	if ((hServer_Sock = socket(PF_INET, SOCK_STREAM, 0)) < 0) { // �������� ü��(IPv4), ���� ���(TCP), �������� ���� (���� �ڵ�)
		printf("socket failed\n");
		return -1;
	}


	// ����ü �ּ� ���� �ʱ�ȭ
	memset(&serv_addr, 0, sizeof(serv_addr)); // �޸� �ʱ�ȭ
	serv_addr.sin_family = AF_INET; // �ּ� ü��
	// sa_data�� 3���� �и� 
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY); // ���� �� pc�� ip ������ ���
	serv_addr.sin_port = htons(PORT);
	// sin_zero[8] ����Ʈ �� ���߱� ���� 0���� ä����


	// bind (�ּ� ������ ���Ͽ� �Ҵ�)
	if (bind(hServer_Sock, (SOCKADDR*)&serv_addr, sizeof(serv_addr)) < 0) { // ���� �ڵ�, sockaddr ����ü�� ĳ����(�� ����) �� ������ sockaddr_in ����ü �ּ�, ����ü ���� ��������
		printf("bind failed.\n");
		return -2;
	}


	//listen (���� ��û ��� ����)
	if (listen(hServer_Sock, 10) < 0) { // ���� ������ �� ���� �ڵ�, �ִ� �� ���� Ŭ���̾�Ʈ�� �����·� �� ������
		printf("listen failed\n");
		return -3;
	}

	else {
		printf("server started.\n");
	}


	// Ŭ���̾�Ʈ �ּ� ����ü ũ�⺯�� ����
	int size_client_Addr = sizeof(client_Addr);

	// accept (��� ������ Ŭ���̾�Ʈ�� ����)
	while (1)
	{
		hClient_sock = accept(hServer_Sock, (SOCKADDR*)&client_Addr, &size_client_Addr); // ���� ������ ���� �ڵ�, Ŭ���̾�Ʈ�� �ּ� ������ ��� ���� (SOCKADDR_IN���� �����ؼ� (struct sockaddr*)�� ĳ���� ��), ����ü�� ���� ����(�̸� ������ ���� ���� ���� �ʼ�)
		if (hClient_sock > 0) {
			break;
		}
	}
	printf("Client is connected.\n");


	// recv
	recv(hClient_sock, read_message, sizeof(read_message) - 1, 0); // Ŭ���̾�Ʈ�� ����, ��Ŷ�� ��ƿ� ����, ������ ������
	printf("Recv Data : %s\n", read_message);


	// ���ϴݱ�
	closesocket(hClient_sock);
	closesocket(hServer_Sock);
	printf("End.\n");

	// ���� ���̺귯�� ��ȯ
	WSACleanup();

	return 0;

}