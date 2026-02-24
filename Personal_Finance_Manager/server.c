#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <windows.h>
#include "transactions.h"
#include "server.h"

#pragma comment(lib, "ws2_32.lib")

#define REQUEST_BUFFER_SIZE 4096
#define JSON_BUFFER_SIZE 16384

char WWW_BASE_PATH[512] = "www"; //байт
char DATA_FILE_PATH[512] = "www/data/transactions.csv"; //байт
volatile int keep_running = 1;

BOOL WINAPI ConsoleHandler(DWORD signal) {
    if (signal == CTRL_C_EVENT || signal == CTRL_CLOSE_EVENT ||
        signal == CTRL_BREAK_EVENT || signal == CTRL_SHUTDOWN_EVENT) {
        keep_running = 0;
        return TRUE;
    }
    return FALSE;
}

int send_file(SOCKET client, const char* path, const char* content_type) {
    FILE* f;
    if (fopen_s(&f, path, "rb") != 0 || !f) return -1;

    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    fseek(f, 0, SEEK_SET);
    if (size < 0) { fclose(f); return -1; }

    char header[256];
    snprintf(header, sizeof(header),
             "HTTP/1.1 200 OK\r\nContent-Type: %s\r\nContent-Length: %ld\r\nConnection: close\r\n\r\n",
             content_type, size);
    send(client, header, (int)strlen(header), 0);

    char* buf = malloc(size);
    if (!buf) { fclose(f); return -2; }

    fread(buf, 1, size, f);
    send(client, buf, size, 0);

    free(buf);
    fclose(f);
    return 0;
}

int start_server(const char* unused) { //Основная функция сервера
    FILE* cfg = fopen("server_config.txt", "r");
    if (cfg) {
        fgets(WWW_BASE_PATH, sizeof(WWW_BASE_PATH), cfg);
        fgets(DATA_FILE_PATH, sizeof(DATA_FILE_PATH), cfg);
        fclose(cfg);
        WWW_BASE_PATH[strcspn(WWW_BASE_PATH, "\r\n")] = '\0';
        DATA_FILE_PATH[strcspn(DATA_FILE_PATH, "\r\n")] = '\0';
    }

    SetConsoleCtrlHandler(ConsoleHandler, TRUE);

    WSADATA ws;
    if (WSAStartup(MAKEWORD(2,2), &ws) != 0) return 1;

    SOCKET server = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (server == INVALID_SOCKET) return 1;

    SOCKADDR_IN addr = {0};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(8080); // Порт
    addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(server, (SOCKADDR*)&addr, sizeof(addr)) == SOCKET_ERROR ||
        listen(server, SOMAXCONN) == SOCKET_ERROR) {
        closesocket(server);
        WSACleanup();
        return 1;
    }

    printf("Сервер запущен на порту 8080...\n");

    while (keep_running) {
        fd_set readfds;
        struct timeval tv = {1, 0};
        FD_ZERO(&readfds);
        FD_SET(server, &readfds);
        if (select(0, &readfds, NULL, NULL, &tv) <= 0) continue;

        SOCKET client = accept(server, NULL, NULL);
        if (client == INVALID_SOCKET) continue;

        char req[REQUEST_BUFFER_SIZE] = {};
        if (recv(client, req, sizeof(req)-1, 0) <= 0) {
            closesocket(client);
            continue;
        }

        char method[8], path[256];
        sscanf(req, "%7s %255s", method, path);

        int status = 1;
        char full[512];

        if (strcmp(method, "GET") == 0) {
            if (strcmp(path, "/shutdown") == 0) {
                const char* msg = "HTTP/1.1 200 OK\r\nConnection: close\r\n\r\nСервер завершается.";
                send(client, msg, (int)strlen(msg), 0);
                keep_running = 0;
                status = 0;
            } else if (strcmp(path, "/") == 0 || strcmp(path, "/main.html") == 0) {
                snprintf(full, sizeof(full), "%s/main.html", WWW_BASE_PATH);
                status = send_file(client, full, "text/html; charset=utf-8");
            } else if (strcmp(path, "/transactions") == 0) {
                char* json = malloc(JSON_BUFFER_SIZE);
                if (json) {
                    getTransactions(DATA_FILE_PATH, json, JSON_BUFFER_SIZE);
                    char header[256];
                    snprintf(header, sizeof(header),
                             "HTTP/1.1 200 OK\r\nContent-Type: application/json; charset=utf-8\r\n"
                             "Access-Control-Allow-Origin: *\r\nContent-Length: %zu\r\nConnection: close\r\n\r\n",
                             strlen(json));
                    send(client, header, (int)strlen(header), 0);
                    send(client, json, (int)strlen(json), 0);
                    free(json);
                    status = 0;
                } else status = -2;
            } else {
                const char* type = NULL;
                if (strstr(path, ".css")) type = "text/css";
                else if (strstr(path, ".js")) type = "application/javascript";
                else if (strstr(path, ".png")) type = "image/png";

                if (type) {
                    snprintf(full, sizeof(full), "%s%s", WWW_BASE_PATH, path);
                    status = send_file(client, full, type);
                }
            }
        }

        if (status != 0) {
            const char* err = (status == -2)
            ? "HTTP/1.1 500 Internal Server Error\r\nConnection: close\r\n\r\nОшибка сервера."
            : "HTTP/1.1 404 Not Found\r\nConnection: close\r\n\r\nФайл не найден.";
            send(client, err, (int)strlen(err), 0);
        }

        closesocket(client);
    }

    closesocket(server);
    WSACleanup();
    return 0;
}
