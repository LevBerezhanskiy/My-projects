#include "transactions.h"
#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <ctype.h>
#include <stdlib.h>

ActionNode* historyHead = NULL;

static int historyCount = 0;

void convert_oem_to_utf8(const char* oemStr, char* utf8Str, size_t utf8StrSize) {
    if (!oemStr || !utf8Str || utf8StrSize == 0) return;
    int utf16Len = MultiByteToWideChar(CP_OEMCP, 0, oemStr, -1, NULL, 0);
    if (utf16Len <= 0) { utf8Str[0] = '\0'; return; }

    wchar_t* utf16Str = (wchar_t*)malloc(utf16Len * sizeof(wchar_t));
    if (!utf16Str) { utf8Str[0] = '\0'; return; }

    MultiByteToWideChar(CP_OEMCP, 0, oemStr, -1, utf16Str, utf16Len);
    int utf8Len = WideCharToMultiByte(CP_UTF8, 0, utf16Str, -1, utf8Str, (int)utf8StrSize, NULL, NULL);
    if (utf8Len <= 0 || (size_t)utf8Len > utf8StrSize) utf8Str[0] = '\0';
    free(utf16Str);
}

void convert_utf8_to_oem(const char* utf8Str, char* oemStr, size_t oemStrSize) {
    if (!utf8Str || !oemStr || oemStrSize == 0) return;
    int utf16Len = MultiByteToWideChar(CP_UTF8, 0, utf8Str, -1, NULL, 0);
    if (utf16Len <= 0) { oemStr[0] = '\0'; return; }

    wchar_t* utf16Str = (wchar_t*)malloc(utf16Len * sizeof(wchar_t));
    if (!utf16Str) { oemStr[0] = '\0'; return; }

    MultiByteToWideChar(CP_UTF8, 0, utf8Str, -1, utf16Str, utf16Len);
    int oemLen = WideCharToMultiByte(CP_OEMCP, 0, utf16Str, -1, oemStr, (int)oemStrSize, NULL, NULL);
    if (oemLen <= 0 || (size_t)oemLen > oemStrSize) oemStr[0] = '\0';
    free(utf16Str);
}

void copy_and_trim_field(char* dest, size_t destSize, const char* start, const char* end) { //Копирует часть строки (поле CSV) в целевой буфер
    if (!dest || destSize == 0 || !start || !end || start >= end) return;
    while (start < end && isspace((unsigned char)*start)) start++;
    while (end > start && isspace((unsigned char)*(end - 1))) end--;
    size_t len = end - start;
    if (len >= destSize) len = destSize - 1;
    memcpy(dest, start, len);
    dest[len] = '\0';
}

void escapeJsonString(const char* input, char* output, size_t outSize) { // Защищает от спец. символов
    size_t outPos = 0;
    output[0] = '\0';
    for (size_t i = 0; input[i] != '\0' && outPos < outSize - 1; i++) {
        char c = input[i];
        if (c == '\"' || c == '\\') {
            if (outPos + 2 < outSize) {
                output[outPos++] = '\\';
                output[outPos++] = c;
            }
        } else {
            output[outPos++] = c;
        }
    }
    output[outPos] = '\0';
}

int get_next_id(const char* dataFilePath) { // Определяет следующий доступный ID
    FILE* file = fopen(dataFilePath, "r");
    if (!file) return 1;
    char line[1024];
    int maxId = 0;
    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, "Id") || strstr(line, "id"))
            continue;
        int id = 0;
        if (sscanf(line, "%d,", &id) == 1 && id > maxId)
            maxId = id;
    }
    fclose(file);
    return maxId + 1;
}

int addTransaction(const char* dataFilePath, const char* type, const char* category,
                   const char* date, double amount, const char* description) { // Добавляет новую транзакцию в файл.
    int needsHeader = 1, needsNewline = 0;
    FILE* file = fopen(dataFilePath, "rb");
    if (file) {
        char line[256];
        if (fgets(line, sizeof(line), file) && strstr(line, "Id")) needsHeader = 0;
        if (fseek(file, -1, SEEK_END) == 0 && fgetc(file) != '\n') needsNewline = 1;
        fclose(file);
    }

    file = fopen(dataFilePath, "a");
    if (!file) return -1;
    if (needsNewline)
        fputc('\n', file);
    if (needsHeader)
        fprintf(file, "Id,Type,Category,Date,Amount,Description\n");
    int newId = get_next_id(dataFilePath);

    char safeDesc[2048]; int pos = 0;
    for (int i = 0; description[i] != '\0' && pos < sizeof(safeDesc) - 2; ++i) {
        if (description[i] == '\"' && pos < sizeof(safeDesc) - 2)
            safeDesc[pos++] = '\"';
        safeDesc[pos++] = description[i];
    }
    safeDesc[pos] = '\0';

    fprintf(file, "%d,%s,%s,%s,%.2f,%s\n", newId, type, category, date, amount, safeDesc);
    fclose(file);
    return newId;
}

void getTransactions(const char* dataFilePath, char* jsonBuffer, size_t bufferSize) { // Читает все транзакции из файла и формирует JSON-строку (динамические обновления на сайте)
    if (bufferSize < 3) { if (bufferSize > 0) jsonBuffer[0] = '\0';
        return;
    }
    FILE* file = fopen(dataFilePath, "rb");
    if (!file) { strcpy_s(jsonBuffer, bufferSize, "[]");
        return;
    }

    unsigned char bom[3];
    if (fread(bom, 1, 3, file) != 3 || !(bom[0] == 0xEF && bom[1] == 0xBB && bom[2] == 0xBF))
        fseek(file, 0, SEEK_SET);

    size_t offset = 1;
    jsonBuffer[0] = '['; jsonBuffer[1] = '\0';
    int first = 1;
    char line[2048];

    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\r\n")] = '\0';
        if (strlen(line) == 0)
            continue;

        char id_str[20], type[50], category[200], date[30], amount[100], desc[1024];
        char* parts[] = { id_str, type, category, date, amount, desc };
        size_t sizes[] = { 20, 50, 200, 30, 100, 1024 };
        char* context = NULL;
        char* token = strtok_s(line, ",", &context);
        int field_index = 0;

        while (token && field_index < 6) {
            copy_and_trim_field(parts[field_index], sizes[field_index], token, token + strlen(token));
            field_index++;
            token = strtok_s(NULL, ",", &context);
        }
        if (field_index != 6) continue;

        int is_numeric = 1;
        for (size_t i = 0; id_str[i]; ++i) if (!isdigit((unsigned char)id_str[i])) is_numeric = 0;
        if (!is_numeric) continue;

        int id = atoi(id_str);
        char escType[100], escCat[400], escDate[60], escAmount[200], escDesc[2048];
        escapeJsonString(type, escType, sizeof(escType));
        escapeJsonString(category, escCat, sizeof(escCat));
        escapeJsonString(date, escDate, sizeof(escDate));
        escapeJsonString(amount, escAmount, sizeof(escAmount));
        escapeJsonString(desc, escDesc, sizeof(escDesc));

        size_t required = strlen(escType) + strlen(escCat) + strlen(escDate) + strlen(escAmount) + strlen(escDesc) + 100;
        if (bufferSize - offset < required + 2) break;

        if (!first) jsonBuffer[offset++] = ','; else first = 0;
        offset += snprintf(jsonBuffer + offset, bufferSize - offset,
                           "{\"id\":%d,\"type\":\"%s\",\"category\":\"%s\",\"date\":\"%s\",\"amount\":\"%s\",\"description\":\"%s\"}",
                           id, escType, escCat, escDate, escAmount, escDesc);
    }

    if (bufferSize > offset + 1) {
        jsonBuffer[offset++] = ']';
        jsonBuffer[offset] = '\0';
    }
    fclose(file);
}

int findTransactionById(const char* dataFilePath, int idToFind,
                        char* outType, size_t typeSize,
                        char* outCategory, size_t catSize,
                        char* outDate, size_t dateSize,
                        double* outAmount, char* outDesc, size_t descSize) { //Ищет транзакцию в файле по ее ID
    FILE* file = fopen(dataFilePath, "r");
    if (!file) return 0;
    char line[2048];
    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, "Id")) continue;
        int id = 0;
        char type[100] = "", category[200] = "", date[30] = "", amountStr[100] = "", desc[300] = "";
        char* context = NULL;
        char* token = strtok_s(line, ",", &context);
        int field = 0;
        while (token) {
            switch (field) {
            case 0: id = atoi(token);
                break;
            case 1: strncpy(type, token, sizeof(type));
                break;
            case 2: strncpy(category, token, sizeof(category));
                break;
            case 3: strncpy(date, token, sizeof(date));
                break;
            case 4: strncpy(amountStr, token, sizeof(amountStr));
                break;
            case 5: strncpy(desc, token, sizeof(desc));
                break;
            }
            field++;
            token = strtok_s(NULL, ",", &context);
        }
        if (id == idToFind) {
            strncpy(outType, type, typeSize);
            strncpy(outCategory, category, catSize);
            strncpy(outDate, date, dateSize);
            *outAmount = atof(amountStr);
            strncpy(outDesc, desc, descSize);
            fclose(file);
            return 1;
        }
    }
    fclose(file);
    return 0;
}

int editTransaction(const char* dataFilePath, int id,
                    const char* type, const char* category,
                    const char* date, double amount,
                    const char* description) { //Редактирует транзакцию в файле
    FILE* input = fopen(dataFilePath, "r");
    if (!input) return 0;
    FILE* temp = fopen("temp.csv", "w");
    if (!temp) {
        fclose(input);
        return 0;
    }

    char line[1024];
    int updated = 0;
    while (fgets(line, sizeof(line), input)) {
        if (strstr(line, "Id")) { fputs(line, temp);
            continue;
        }
        int currId = 0;
        sscanf(line, "%d,", &currId);
        if (currId == id) {
            fprintf(temp, "%d,%s,%s,%s,%.2f,%s\n", id, type, category, date, amount, description);
            updated = 1;
        } else
            fputs(line, temp);
    }

    fclose(input);
    fclose(temp);
    remove(dataFilePath);
    rename("temp.csv", dataFilePath);
    return updated;
}

int deleteTransaction(const char* dataFilePath, int targetId) { //Удаляет транзу из файла по ее ID и переиндексирует ID
    FILE* file = fopen(dataFilePath, "r");
    if (!file) return 0;
    char line[1024];
    char** lines = NULL;
    int count = 0;

    unsigned char bom[3];
    if (fread(bom, 1, 3, file) != 3 || !(bom[0] == 0xEF && bom[1] == 0xBB && bom[2] == 0xBF))
        fseek(file, 0, SEEK_SET);

    while (fgets(line, sizeof(line), file)) {
        lines = realloc(lines, sizeof(char*) * (count + 1));
        lines[count++] = _strdup(line);
    }
    fclose(file);

    file = fopen(dataFilePath, "w");
    if (!file)
        return 0;

    fprintf(file, "Id,Type,Category,Date,Amount,Description\n");
    int newId = 1;
    for (int i = 1; i < count; ++i) {
        int id; char tmp[1024];
        strcpy(tmp, lines[i]);
        if (sscanf(tmp, "%d,", &id) == 1 && id != targetId) {
            char* rest = strchr(lines[i], ',');
            if (rest)
                fprintf(file, "%d%s", newId++, rest);
        }
        free(lines[i]);
    }
    free(lines[0]);
    free(lines);
    fclose(file);
    return 1;
}

// Списки
void addActionToHistory(const char* action) {
    if (!action)
        return;

    ActionNode* newNode = (ActionNode*)malloc(sizeof(ActionNode));

    if (!newNode)
        return;

    strncpy(newNode->message, action, sizeof(newNode->message) - 1);

    newNode->message[sizeof(newNode->message) - 1] = '\0';
    newNode->next = historyHead;

    historyHead = newNode;

    historyCount++;
    if (historyCount > MAX_HISTORY) {
        ActionNode* current = historyHead;
        while (current->next && current->next->next) {
            current = current->next;
        }
        free(current->next);
        current->next = NULL;
        historyCount--;
    }
}

void getHistory(char* buffer, size_t bufferSize) {

    if (!buffer || bufferSize == 0) return;

    buffer[0] = '\0';
    ActionNode* current = historyHead;

    while (current && strlen(buffer) + strlen(current->message) + 2 < bufferSize) {
        strcat(buffer, current->message);
        strcat(buffer, "\n");
        current = current->next;
    }
}

void clearActionHistory(const char* filePath) {

    saveHistoryToFile(filePath);

    while (historyHead) {
        ActionNode* temp = historyHead;
        historyHead = historyHead->next;
        free(temp);
    }
}

void saveHistoryToFile(const char* filePath) {
    FILE* file = fopen(filePath, "w");

    if (!file)
        return;

    ActionNode* current = historyHead;

    while (current) {
        fprintf(file, "%s\n", current->message);
        current = current->next;
    }

    fclose(file);
}

void loadHistoryFromFile(const char* filePath) { // Загружает историю действий из указанного файла в список в ОП

    FILE* file = fopen(filePath, "r");
    if (!file)
        return;

    char line[300];
    while (fgets(line, sizeof(line), file)) {

        line[strcspn(line, "\n")] = '\0';

        addActionToHistory(line);
    }

    fclose(file);
}
