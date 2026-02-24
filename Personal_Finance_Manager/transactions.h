#ifndef TRANSACTIONS_H
#define TRANSACTIONS_H

#define MAX_HISTORY 100

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>

typedef struct ActionNode {
    char message[300];
    struct ActionNode* next;
} ActionNode;

extern ActionNode* historyHead;

void addActionToHistory(const char* action);
void getHistory(char* buffer, size_t bufferSize);
void clearActionHistory(const char* filePath);
void saveHistoryToFile(const char* filePath);
void loadHistoryFromFile(const char* filePath);

int addTransaction(const char* dataFilePath, const char* type, const char* category, const char* date, double amount, const char* description);
void getTransactions(const char* dataFilePath, char* jsonBuffer, size_t bufferSize);
int findTransactionById(const char* dataFilePath, int idToFind, char* outType, size_t typeSize, char* outCategory, size_t catSize, char* outDate, size_t dateSize, double* outAmount, char* outDesc, size_t descSize);
int editTransaction(const char* dataFilePath, int id, const char* type, const char* category, const char* date, double amount, const char* description);
int deleteTransaction(const char* dataFilePath, int targetId);

#ifdef __cplusplus
}
#endif

#endif // TRANSACTIONS_H
