#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define SERVERIPPROF "192.168.112.250"
#define SERVERIP "192.168.86.215"
#define N 100

int main(void) {
    int server = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(1111);
    serverAddr.sin_addr.s_addr = inet_addr(SERVERIPPROF);

    int conn = 0;
    while ((conn = connect(server, (const struct sockaddr *)&serverAddr,
                           sizeof(serverAddr))) == -1) {
        if (errno == ENOENT) {
            printf("Retry\n");
            sleep(1);
        } else
            break;
    }

    if (conn == -1) {
        perror("Error connect");
        exit(EXIT_FAILURE);
    }

    char buff[N];
    printf("messaggio:");
    scanf("%s", buff);
    write(server, buff, strlen(buff) + 1);
    printf("il server ha risposto: %s\n", buff);
    close(server);
    return 0;
}
