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

const int NMAX = 10000;

char message[] = "Hello there!\n";
char buf[sizeof(message)];

int main()
{
    int sock[NMAX];
    struct sockaddr_in addr;
    struct hostent *server;
    //server = gethostbyname("188.40.161.43");
    server = gethostbyname("127.0.0.1");
    addr.sin_family = PF_INET;
    addr.sin_port = htons(3425);
    //addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    memcpy((char*)server->h_addr,
          (char*)&addr.sin_addr.s_addr,
          server->h_length);

    for (size_t i = 0; i < NMAX; ++i) {
        sock[i] = socket(PF_INET, SOCK_STREAM, 0);
        std::cout << i << std::endl;

        if(sock[i] < 0)
        {
            perror("socket");
            exit(1);
        }

        if(connect(sock[i], (struct sockaddr *)&addr, sizeof(addr)) < 0)
        {
            perror("connect");
            exit(2);
        }
    }
    //sleep(5000);
    for (size_t i = 0; i < NMAX; ++i) {
        send(sock[i], message, sizeof(message), 0);
    }
    for (size_t i = 0; i < NMAX; ++i) {
        recv(sock[i], buf, sizeof(message), 0);
    }
    //std::cout << buf;
    //std::cout << "Success recv";
    for (size_t i = 0; i < NMAX; ++i) {
        close(sock[i]);
    }
    return 0;
}