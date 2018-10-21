#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <pthread.h>
#include <netinet/in.h>
#include <errno.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <netdb.h>
#include <openssl/ssl.h>

int main(int argc, char *argv[])
{
    printf("Running Main...\n");

    struct addrinfo hints, *res;

    int socketfd;
    char buf[16384];
    int byte_count;
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = 0;
    getaddrinfo("www.api.github.com", "80", &hints, &res);
    socketfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    printf("Connecting...\n");
    connect(socketfd, res->ai_addr, res->ai_addrlen);
    printf("Connected!\n");
    char *header = "GET http://api.github.com/repos/CygnusSW/style-guide/statuses/master HTTP/1.1\r\n"
                   "Host: api.github.com\r\n"
                   "Accept: application/vnd.github.v3+json\r\n"
                   "ContentType: application/json; charset=utf-8\r\n"
                   "\r\n";
    send(socketfd, header, strlen(header), 0);
    printf("GET request sent...\n");
    byte_count = recv(socketfd, buf, sizeof(buf) - 1, 0);
    buf[byte_count] = 0;
    printf("recv()'d %d bytes of data in buf\n",byte_count);
    printf("%s\n",buf);
    
    printf("Main complete.\n");
    return 0;
}



