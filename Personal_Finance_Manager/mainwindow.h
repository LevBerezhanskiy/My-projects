#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProcess>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent *event) override;

private slots:
    void on_exitButton_clicked(); // Выйти
    void on_launchServerButton_clicked(); //Запустить сервер
    void on_stopServerButton_clicked(); // Остановить сервер
    void on_addTransactionButton_clicked(); // Добавить транзу
    void on_pushButton_cancelAddTransaction_clicked(); // Назад в добавлении и редаче
    void on_pushButton_saveTransaction_clicked(); // Сохранить в добавлении и редаче
    void on_editTransactionButton_clicked(); //Редачить транзу
    void on_deleteTransactionButton_clicked(); // Удалить
    void on_showAllButton_clicked(); // Показать все транзы
    void on_pushButton_backToMenu_clicked(); // Назад в меню в "Показать все транзы"
    void on_clearHistoryButton_clicked(); // Очистить историю
    void on_showHistoryButton_clicked(); // История действий
    void on_pushButton_backFromHistory_clicked(); // Назад в меню в "История действий"

private:
    Ui::MainWindow *ui;
    QProcess *serverProcess;
    bool serverOpenedInBrowser = false;
    bool editMode = false;
    int editId = -1;
    bool setupDirectoryStructure(); // Проверка www или создание www/data
    void stopServer(); // Остановка сервера
    void loadTransactionsToTable(); // Загрузка, отображение транз
    void loadHistoryToTable(); // Загрузка, отображение истории действий
};
#endif // MAINWINDOW_H
