#include "server.h"
#include <stdio.h>

int main() {
    printf("Отдельный server.exe запущен.\n");
    int result = start_server(NULL);
    printf("Сервер завершён с кодом: %d\n", result);
    return result;
}
