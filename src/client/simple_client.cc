#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <algorithm>
#include <set>
#include <iostream>

char message[] = "  Hello there!";
char buf[sizeof(message)];

int main()
{
    int sock;
    struct sockaddr_in addr;
    struct hostent *server;
    //server = gethostbyname("188.40.161.43");
    server = gethostbyname("127.0.0.1");

    sock = socket(PF_INET, SOCK_STREAM, 0);
    if(sock < 0)
    {
        perror("socket");
        exit(1);
    }

    addr.sin_family = PF_INET;
    addr.sin_port = htons(3425);
    //addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    memcpy((char*)server->h_addr,
          (char*)&addr.sin_addr.s_addr,
          server->h_length);
    //addr.sin_addr = inet_addr("188.40.161.43");

    if(connect(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        perror("connect");
        exit(2);
    }
    char header[2];
    int body_length = strlen(message);
    int header_size = 2;
    memcpy(message, &body_length, sizeof(header));
    //send(sock, header, sizeof(header), 0);
    send(sock, message, sizeof(message), 0);
    recv(sock, buf, sizeof(message), 0);

    std::cout << buf;
    std::cout << "Success recv";
    close(sock);

    return 0;
}