#include "transactionswindow.h"
#include <QVBoxLayout>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QTableWidgetItem>

TransactionsWindow::TransactionsWindow(QWidget *parent)
    : QDialog(parent), table(new QTableWidget(this))
{
    setWindowTitle("Все транзакции");
    resize(700, 500);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(table);

    table->setColumnCount(6);
    table->setHorizontalHeaderLabels({"ID", "Тип", "Категория", "Дата", "Сумма", "Описание"});
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setSelectionMode(QAbstractItemView::SingleSelection);
    table->verticalHeader()->setVisible(false);
    table->setStyleSheet(
        "QHeaderView::section { background-color: #f0f0f0; font-weight: bold; padding: 4px; }"
        "QTableWidget::item:selected { background-color: #cceeff; color: black; }"
        );
}

void TransactionsWindow::setJson(const QByteArray &json)
{
    populateTable(json);
}

void TransactionsWindow::populateTable(const QByteArray &json)
{
    QJsonDocument doc = QJsonDocument::fromJson(json);
    if (!doc.isArray()) return;

    QJsonArray arr = doc.array();
    table->setRowCount(arr.size());

    for (int i = 0; i < arr.size(); ++i) {
        QJsonObject obj = arr[i].toObject();
        table->setItem(i, 0, new QTableWidgetItem(QString::number(obj["id"].toInt())));
        table->setItem(i, 1, new QTableWidgetItem(obj["type"].toString()));
        table->setItem(i, 2, new QTableWidgetItem(obj["category"].toString()));
        table->setItem(i, 3, new QTableWidgetItem(obj["date"].toString()));
        table->setItem(i, 4, new QTableWidgetItem(QString::number(obj["amount"].toDouble(), 'f', 2)));
        table->setItem(i, 5, new QTableWidgetItem(obj["description"].toString()));
    }

    table->resizeColumnsToContents();
}
