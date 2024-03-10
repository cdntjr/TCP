#include <winsock2.h>
#include <stdlib.h>
#include <stdio.h>

#pragma comment(lib, "ws2_32.lib")

#define PORT (7777)

#pragma warning(disable:4996)


/* 구조체 분석 정보
sockaddr_in = SOCKADDR_IN

struct sockaddr_in
{
	sa_family_t    sin_family;  주소체계(Address Family)
	uint16_t       sin_port;    16비트 TCP/UDP PORT번호
	struct in_addr sin_addr;    32비트의 IP주소
	char           sin_zero[8]; 사용되지 않음 -> ??
}


struct sockaddr = SOCKADDR

struct sockaddr
{
	sa_family_t sin_family    주소체계(Address Family)
	char        sa_data[14];  주소정보
}
*/


int main() {

	WSADATA wsadata; // wsadata 변수 선언
	SOCKET hServer_Sock, hClient_sock;
	SOCKADDR_IN serv_addr, client_Addr;

	char read_message[1024];


	// 라이브러리 사용 확인 (이후 해당 변수로 초기화 된 라이브러리의 정보가 채워짐)
	WSAStartup(MAKEWORD(2, 2), &wsadata); // 사용할 원속의 버전 정보, WSADATA 구조체 변수의 주소값


	//서버 소켓 생성 (어떤 프로토콜을 가진 소켓으로 통신할 것인지)
	if ((hServer_Sock = socket(PF_INET, SOCK_STREAM, 0)) < 0) { // 프로토콜 체계(IPv4), 전송 방식(TCP), 프로토콜 정보 (소켓 핸들)
		printf("socket failed\n");
		return -1;
	}


	// 구조체 주소 정보 초기화
	memset(&serv_addr, 0, sizeof(serv_addr)); // 메모리 초기화
	serv_addr.sin_family = AF_INET; // 주소 체계
	// sa_data를 3개로 분리 
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY); // 현재 이 pc의 ip 정보를 사용
	serv_addr.sin_port = htons(PORT);
	// sin_zero[8] 바이트 열 맞추기 위해 0으로 채워짐


	// bind (주소 정보를 소켓에 할당)
	if (bind(hServer_Sock, (SOCKADDR*)&serv_addr, sizeof(serv_addr)) < 0) { // 소켓 핸들, sockaddr 구조체로 캐스팅(형 변한) 된 정의한 sockaddr_in 구조체 주소, 구조체 변수 길이정보
		printf("bind failed.\n");
		return -2;
	}


	//listen (연결 요청 대기 상태)
	if (listen(hServer_Sock, 10) < 0) { // 서버 소켓이 될 소켓 핸들, 최대 몇 개의 클라이언트를 대기상태로 둘 것인지
		printf("listen failed\n");
		return -3;
	}

	else {
		printf("server started.\n");
	}


	// 클라이언트 주소 구조체 크기변수 정의
	int size_client_Addr = sizeof(client_Addr);

	// accept (대기 상태의 클라이언트를 수락)
	while (1)
	{
		hClient_sock = accept(hServer_Sock, (SOCKADDR*)&client_Addr, &size_client_Addr); // 서버 소켓의 소켓 핸들, 클라이언트의 주소 정보를 담는 변수 (SOCKADDR_IN으로 정의해서 (struct sockaddr*)로 캐스팅 함), 구조체의 길이 정보(미리 변수에 길이 정보 저장 필수)
		if (hClient_sock > 0) {
			break;
		}
	}
	printf("Client is connected.\n");


	// recv
	recv(hClient_sock, read_message, sizeof(read_message) - 1, 0); // 클라이언트의 소켓, 패킷을 담아올 버퍼, 버퍼의 사이즈
	printf("Recv Data : %s\n", read_message);


	// 소켓닫기
	closesocket(hClient_sock);
	closesocket(hServer_Sock);
	printf("End.\n");

	// 원속 라이브러리 반환
	WSACleanup();

	return 0;

}