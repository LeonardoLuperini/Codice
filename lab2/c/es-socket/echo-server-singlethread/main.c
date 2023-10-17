#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <sys/socket.h>

#define SERVERIP "192.168.86.215"

int main() {
    int server = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(9999);
    serverAddr.sin_addr.s_addr = inet_addr(SERVERIP);

    bind(server, (const struct sockaddr *)&serverAddr, sizeof(serverAddr));
    listen(server, 10);

    fd_set allFDs, readFDs;
    FD_ZERO(&allFDs);
    FD_SET(server, &allFDs);
    size_t fdMax = server;

    while (1) {
        readFDs = allFDs;
        select(fdMax + 1, &readFDs, NULL, NULL, NULL);
        for (size_t i = 0; i < fdMax; i++) {
        }
    }

    return EXIT_SUCCESS;
}
