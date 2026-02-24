#ifndef TRANSACTIONSWINDOW_H
#define TRANSACTIONSWINDOW_H

#include <QDialog>
#include <QTableWidget>

class TransactionsWindow : public QDialog
{
    Q_OBJECT

public:
    explicit TransactionsWindow(QWidget *parent = nullptr);
    void setJson(const QByteArray &json);

private:
    QTableWidget *table;
    void populateTable(const QByteArray &json);
};

#endif // TRANSACTIONSWINDOW_H
