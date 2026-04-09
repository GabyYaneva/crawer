#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

void parse_and_print_links(char* response) {
    char* html = strstr(response, "\r\n\r\n");
    if (html == NULL) {
        html = response;
    }
    else {
        html += 4; 
    }

    char* p = html;
    char* tag = "<a href=\"";

    int found = 0;

    while ((p = strstr(p, tag)) != NULL) {
        p += strlen(tag);
        char* end = strchr(p, '\"');
        if (end) {
            printf("Found URL: %.*s\n", (int)(end - p), p);
            p = end;
            found++;
        }
    }

    if (found == 0) {
        printf("File not found\n");
    }
}

int main() {
    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) return 1;

    char* host = "crawlertest.cs.tu-varna.bg";
    char* path = "/TestIIR.html";

    struct hostent* server = gethostbyname(host);
    if (server == NULL) {
        int err = WSAGetLastError();
        printf("Error :gethostbyname: %d\n", err);

        if (err == 11001) {
            printf("host not found\n");
        }

        WSACleanup();
        return 1;
    }
    SOCKET s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(80);
    memcpy(&addr.sin_addr.s_addr, server->h_addr, server->h_length);

    if (connect(s, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        printf("CAnt connect 2\n");
        return 1;
    }

    char request[512];
    sprintf_s(request, sizeof(request),
        "GET %s HTTP/1.1\r\n"
        "Host: %s\r\n"
        "Connection: close\r\n\r\n",
        path, host);

    send(s, request, (int)strlen(request), 0);

    char response[30000];
    int total_received = 0, n;

    while ((n = recv(s, response + total_received, sizeof(response) - total_received - 1, 0)) > 0) {
        total_received += n;
        if (total_received >= sizeof(response) - 1) break;
    }
    response[total_received] = '\0';

    printf("\n%s\n", response);
    parse_and_print_links(response);

    closesocket(s);
    WSACleanup();
    getchar();
    return 0;
}