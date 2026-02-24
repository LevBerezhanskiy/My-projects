#include <QApplication>
#include "mainwindow.h"
#include <QDebug>
#include "transactions.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow w;
    QString historyFilePath = QCoreApplication::applicationDirPath() + "/history.txt";
    QByteArray pathBytes = historyFilePath.toLocal8Bit();
    const char* historyPath = pathBytes.constData();

    loadHistoryFromFile(historyPath);
    w.show();
    int result = a.exec();
    saveHistoryToFile(historyPath);
    return result;
}
