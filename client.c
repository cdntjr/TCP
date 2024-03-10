#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#include <ws2tcpip.h> 

#pragma comment(lib, "ws2_32.lib")

#define PORT (7777)
#define IP ("127.0.0.1")

#define _WINSOCK_DEPRECATED_NO_WARNINGS

int main() {

	WSADATA wsadata; // wsadata 변수 선언
	SOCKET hSock;
	SOCKADDR_IN serv_addr;

	char send_message[1024] = "Hello!";


	// 라이브러리 사용 확인 (이후 해당 변수로 초기화 된 라이브러리의 정보가 채워짐)
	WSAStartup(MAKEWORD(2, 2), &wsadata); // 사용할 원속의 버전 정보, WSADATA 구조체 변수의 주소값


	//소켓 생성 (어떤 프로토콜을 가진 소켓으로 통신할 것인지)
	if ((hSock = socket(PF_INET, SOCK_DGRAM, 0)) < 0) { // 프로토콜 체계(IPv4), 전송 방식(UDP), 프로토콜 정보 (소켓 핸들)
		printf("socket failed\n");
		return -1;
	}


	// 구조체 주소 정보 초기화
	memset(&serv_addr, 0, sizeof(serv_addr)); // 메모리 초기화
	serv_addr.sin_family = AF_INET; // 주소 체계
	// sa_data를 3개로 분리 
	serv_addr.sin_port = htons(PORT);
	inet_pton(AF_INET, IP, &(serv_addr.sin_addr));
	// sin_zero[8] 바이트 열 맞추기 위해 0으로 채워짐


	printf("입력 : ");
	gets(send_message);


	// send
	if (sendto(hSock, send_message, sizeof(send_message), 0, (SOCKADDR*)&serv_addr, sizeof(serv_addr)) < 0) {	
		printf("send failed.\n");
		return -3;
	}


	// 소켓닫기
	closesocket(hSock);

	// 라이브러리 사용 끝나서 반환
	WSACleanup();


	return 0;
}