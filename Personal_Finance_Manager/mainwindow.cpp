#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QInputDialog>
#include <QDesktopServices>
#include <QProcess>
#include <QUrl>
#include <QDir>
#include <QFileInfo>
#include <QTextStream>
#include <QDate>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QDoubleValidator>

extern "C" {
#include "transactions.h"
}

const int PAGE_MAIN_MENU = 0;
const int PAGE_ADD_TRANSACTION = 1;
const int PAGE_TRANSACTIONS_VIEW = 2;
const int PAGE_HISTORY = 3;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), serverProcess(nullptr), serverOpenedInBrowser(false)
{
    ui->setupUi(this);
    QDate current = QDate::currentDate();
    ui->spinBox_day->setValue(current.day());
    ui->spinBox_month->setValue(current.month());
    ui->spinBox_year->setValue(current.year());

    auto *validator = new QDoubleValidator(0, 1e9, 2, this);
    validator->setNotation(QDoubleValidator::StandardNotation);
    ui->lineEdit_amount->setValidator(validator);

    ui->radioButton_expense->setChecked(true);
    ui->label_addStatusMessage->clear();
    ui->stackedWidget->setCurrentIndex(PAGE_MAIN_MENU);
    setupDirectoryStructure();
}

MainWindow::~MainWindow()
{
    stopServer();
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    stopServer();
    QMainWindow::closeEvent(event);
}

bool MainWindow::setupDirectoryStructure()
{
    QString base = QCoreApplication::applicationDirPath();
    QString www = base + "/www";
    QString data = www + "/data";

    if (!QDir(www).exists()) {
        QMessageBox::critical(this, "Ошибка", "Папка www не найдена");
        return false;
    }
    QDir().mkpath(data);
    return true;
}

void MainWindow::stopServer()
{
    if (serverProcess) {
        if (serverProcess->state() == QProcess::Running) {
            serverProcess->terminate();
            if (!serverProcess->waitForFinished(3000)) {
                serverProcess->kill();
                serverProcess->waitForFinished(1000);
            }
        }
        delete serverProcess;
        serverProcess = nullptr;
    }
}

void MainWindow::on_exitButton_clicked()
{
    close();
}

void MainWindow::on_launchServerButton_clicked()
{
    if (serverProcess && serverProcess->state() == QProcess::Running) {
        QMessageBox::information(this, "Сервер", "Сервер уже запущен.");
        return;
    }

    if (!setupDirectoryStructure()) return;

    QString base = QCoreApplication::applicationDirPath();
    QString serverPath = base + "/server.exe";

    if (!QFileInfo::exists(serverPath)) {
        QMessageBox::critical(this, "Ошибка", "Файл server.exe не найден");
        return;
    }

    QFile config(base + "/server_config.txt");
    if (config.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&config);
        QString www = base + "/www";
        out << www.replace("\\", "/") << "\n"
            << (www + "/data/transactions.csv").replace("\\", "/") << "\n";
        config.close();
    }

    serverProcess = new QProcess(this);
    serverProcess->setWorkingDirectory(base);
    serverProcess->start(serverPath);

    if (!serverProcess->waitForStarted(5000)) {
        QMessageBox::critical(this, "Ошибка", "Сервер не запустился.");
        delete serverProcess;
        serverProcess = nullptr;
        return;
    }

    if (!serverOpenedInBrowser) {
        QDesktopServices::openUrl(QUrl("http://localhost:8080"));
        serverOpenedInBrowser = true;
    }
}

void MainWindow::on_stopServerButton_clicked()
{
    if (serverProcess && serverProcess->state() == QProcess::Running) {
        stopServer();
        QMessageBox::information(this, "Сервер", "Сервер остановлен.");
    } else {
        QMessageBox::information(this, "Сервер", "Сервер уже остановлен.");
    }
}

void MainWindow::on_addTransactionButton_clicked()
{
    editMode = false;
    editId = -1;
    ui->label_addTitle->setText("Новая транзакция");
    ui->radioButton_income->setChecked(true);
    ui->lineEdit_category->clear();
    QDate current = QDate::currentDate();
    ui->spinBox_day->setValue(current.day());
    ui->spinBox_month->setValue(current.month());
    ui->spinBox_year->setValue(current.year());
    ui->lineEdit_amount->clear();
    ui->textEdit_description->clear();
    ui->label_addStatusMessage->clear();
    ui->stackedWidget->setCurrentIndex(PAGE_ADD_TRANSACTION);
}

void MainWindow::on_pushButton_cancelAddTransaction_clicked()
{
    ui->label_addStatusMessage->clear();
    ui->stackedWidget->setCurrentIndex(PAGE_MAIN_MENU);
}

void MainWindow::on_pushButton_saveTransaction_clicked()
{
    QString type = ui->radioButton_income->isChecked() ? "income" : "expense";
    QString category = ui->lineEdit_category->text().trimmed();
    QString desc = ui->textEdit_description->toPlainText().trimmed();

    if (category.isEmpty() || ui->lineEdit_amount->text().trimmed().isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Категория и сумма обязательны.");
        return;
    }

    if (desc.trimmed().isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Введите описание.");
        return;
    }

    int day = ui->spinBox_day->value();
    int month = ui->spinBox_month->value();
    int year = ui->spinBox_year->value();
    QString date = QString("%1-%2-%3").arg(year).arg(month, 2, 10, QChar('0')).arg(day, 2, 10, QChar('0'));
    double amount = ui->lineEdit_amount->text().toDouble();

    QString path = QCoreApplication::applicationDirPath() + "/www/data/transactions.csv";
    QByteArray pathBytes = path.toLocal8Bit();
    const char* dataPath = pathBytes.constData();

    int result = 0;
    if (editMode) {
        result = editTransaction(dataPath, editId, type.toUtf8().constData(), category.toUtf8().constData(),
                                 date.toUtf8().constData(), amount, desc.toUtf8().constData());
        result = result == 1 ? editId : -1;
    } else {
        result = addTransaction(dataPath, type.toUtf8().constData(), category.toUtf8().constData(),
                                date.toUtf8().constData(), amount, desc.toUtf8().constData());
    }

    if (result > 0) {
        QMessageBox::information(this, "Успех", editMode ? "Изменено." : "Добавлено. ID: " + QString::number(result));
        QString msg = editMode
                          ? QString("Изменена транзакция ID %1").arg(editId)
                          : QString("Добавлена транзакция ID %1").arg(result);
        addActionToHistory(msg.toUtf8().constData());
    } else {
        QMessageBox::critical(this, "Ошибка", "Не удалось сохранить.");
    }

    editMode = false;
    editId = -1;
    ui->label_addStatusMessage->clear();
    ui->stackedWidget->setCurrentIndex(PAGE_MAIN_MENU);
    loadTransactionsToTable();
}

void MainWindow::on_editTransactionButton_clicked()
{
    bool ok;
    int id = QInputDialog::getInt(this, "Редактирование", "Введите ID:", 1, 1, 100000, 1, &ok);
    if (!ok) return;

    QString path = QCoreApplication::applicationDirPath() + "/www/data/transactions.csv";
    QByteArray pBytes = path.toLocal8Bit();
    const char* dataFilePath = pBytes.constData();

    char type[100], category[200], date_str[30], desc[300]; // Renamed date to date_str to avoid conflict with QDate
    double amount;

    if (!findTransactionById(dataFilePath, id, type, sizeof(type), category,
                             sizeof(category), date_str, sizeof(date_str), &amount, desc, sizeof(desc))) {
        QMessageBox::warning(this, "Ошибка", "Транзакция не найдена.");
        return;
    }
    ui->label_addTitle->setText("Редактирование транзакции");
    ui->radioButton_income->setChecked(QString::fromUtf8(type) == "income");
    ui->radioButton_expense->setChecked(QString::fromUtf8(type) == "expense");
    ui->lineEdit_category->setText(QString::fromUtf8(category));

    QStringList d = QString::fromUtf8(date_str).split("-");
    if (d.size() == 3) {
        ui->spinBox_year->setValue(d[0].toInt());
        ui->spinBox_month->setValue(d[1].toInt());
        ui->spinBox_day->setValue(d[2].toInt());
    }
    ui->lineEdit_amount->setText(QString::number(amount, 'f', 2));
    ui->textEdit_description->setPlainText(QString::fromUtf8(desc));

    editMode = true;
    editId = id;
    ui->label_addStatusMessage->clear();
    ui->stackedWidget->setCurrentIndex(PAGE_ADD_TRANSACTION);
}

void MainWindow::on_showAllButton_clicked()
{
    loadTransactionsToTable();
    ui->stackedWidget->setCurrentIndex(PAGE_TRANSACTIONS_VIEW);
}

void MainWindow::on_pushButton_backToMenu_clicked()
{
    ui->stackedWidget->setCurrentIndex(PAGE_MAIN_MENU);
}

void MainWindow::on_deleteTransactionButton_clicked()
{
    bool ok;
    int id = QInputDialog::getInt(this, "Удаление", "Введите ID:", 1, 1, 100000, 1, &ok);
    if (!ok) return;

    QString path = QCoreApplication::applicationDirPath() + "/www/data/transactions.csv";
    QByteArray pBytes = path.toLocal8Bit();
    const char* dataPath = pBytes.constData();

    if (deleteTransaction(dataPath, id)) {
        QMessageBox::information(this, "Удаление", QString("Удалена транзакция ID %1").arg(id));
        QString msg = QString("Удалена транзакция ID %1").arg(id);
        addActionToHistory(msg.toUtf8().constData());
        loadTransactionsToTable();
    } else {
        QMessageBox::critical(this, "Ошибка", "Не удалось удалить.");
    }
}

void MainWindow::loadTransactionsToTable()
{
    QString path = QCoreApplication::applicationDirPath() + "/www/data/transactions.csv";
    QByteArray pBytes = path.toLocal8Bit();
    const char* dataFilePath = pBytes.constData();
    char buffer[65536] = {};
    getTransactions(dataFilePath, buffer, sizeof(buffer));

    QJsonDocument doc = QJsonDocument::fromJson(QByteArray(buffer));
    if (!doc.isArray()) return;

    QJsonArray arr = doc.array();
    ui->tableWidget_transactions->setRowCount(arr.size());
    ui->tableWidget_transactions->setColumnCount(6);
    ui->tableWidget_transactions->setHorizontalHeaderLabels({"ID", "Тип", "Категория", "Дата", "Сумма", "Описание"});

    for (int i = 0; i < arr.size(); ++i) {
        QJsonObject o = arr[i].toObject();
        ui->tableWidget_transactions->setItem(i, 0, new QTableWidgetItem(QString::number(o["id"].toInt())));
        ui->tableWidget_transactions->setItem(i, 1, new QTableWidgetItem(o["type"].toString()));
        ui->tableWidget_transactions->setItem(i, 2, new QTableWidgetItem(o["category"].toString()));
        ui->tableWidget_transactions->setItem(i, 3, new QTableWidgetItem(o["date"].toString()));
        ui->tableWidget_transactions->setItem(i, 4, new QTableWidgetItem(QString::number(o["amount"].toString().toDouble(), 'f', 2)));
        ui->tableWidget_transactions->setItem(i, 5, new QTableWidgetItem(o["description"].toString()));
    }
    ui->tableWidget_transactions->resizeColumnsToContents();
}

void MainWindow::loadHistoryToTable() {
    char historyBuffer[MAX_HISTORY * 300] = {0};
    getHistory(historyBuffer, sizeof(historyBuffer));
    QString allActions = QString::fromUtf8(historyBuffer);
    QStringList actions = allActions.split('\n', Qt::SkipEmptyParts);

    ui->tableWidget_history->clear();
    ui->tableWidget_history->setRowCount(actions.size());
    ui->tableWidget_history->setColumnCount(1);
    ui->tableWidget_history->setHorizontalHeaderLabels({"Действие"});

    for (int i = 0; i < actions.size(); ++i) {
        ui->tableWidget_history->setItem(i, 0, new QTableWidgetItem(actions.at(i)));
    }
    ui->tableWidget_history->resizeColumnsToContents();
}

void MainWindow::on_showHistoryButton_clicked() {
    loadHistoryToTable();
    ui->stackedWidget->setCurrentWidget(ui->pageHistory);
}

void MainWindow::on_clearHistoryButton_clicked() {
    QString historyFilePath = QCoreApplication::applicationDirPath() + "/history.txt";
    QByteArray pathBytes = historyFilePath.toLocal8Bit();
    const char* historyPath = pathBytes.constData();
    clearActionHistory(historyPath);
    QMessageBox::information(this, "История", "История действий очищена.");
    loadHistoryToTable();
}

void MainWindow::on_pushButton_backFromHistory_clicked() {
    ui->stackedWidget->setCurrentIndex(PAGE_MAIN_MENU);
}
