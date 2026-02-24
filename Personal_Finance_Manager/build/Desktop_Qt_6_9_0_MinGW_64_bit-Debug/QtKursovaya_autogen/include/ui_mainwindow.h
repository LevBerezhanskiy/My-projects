/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *mainLayout;
    QStackedWidget *stackedWidget;
    QWidget *pageMainMenu;
    QVBoxLayout *verticalLayout_main;
    QSpacerItem *spacerTop;
    QLabel *label_title;
    QGridLayout *buttonsLayout;
    QPushButton *launchServerButton;
    QPushButton *stopServerButton;
    QPushButton *addTransactionButton;
    QPushButton *editTransactionButton;
    QPushButton *deleteTransactionButton;
    QPushButton *showAllButton;
    QPushButton *showHistoryButton;
    QPushButton *clearHistoryButton;
    QPushButton *exitButton;
    QSpacerItem *spacerBottom;
    QWidget *pageAddTransaction;
    QVBoxLayout *verticalLayout;
    QLabel *label_addTitle;
    QFormLayout *formLayout_add;
    QLabel *label;
    QHBoxLayout *horizontalLayout;
    QRadioButton *radioButton_income;
    QRadioButton *radioButton_expense;
    QLabel *label_2;
    QLineEdit *lineEdit_category;
    QLabel *label_3;
    QHBoxLayout *horizontalLayout_2;
    QSpinBox *spinBox_day;
    QSpinBox *spinBox_month;
    QSpinBox *spinBox_year;
    QLabel *label_4;
    QLineEdit *lineEdit_amount;
    QLabel *label_5;
    QTextEdit *textEdit_description;
    QLabel *label_addStatusMessage;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *pushButton_cancelAddTransaction;
    QPushButton *pushButton_saveTransaction;
    QWidget *pageTransactionsView;
    QVBoxLayout *verticalLayout_view;
    QLabel *label_transactionsTitle;
    QTableWidget *tableWidget_transactions;
    QPushButton *pushButton_backToMenu;
    QWidget *pageHistory;
    QVBoxLayout *verticalLayout_history;
    QLabel *label_historyTitle;
    QTableWidget *tableWidget_history;
    QPushButton *pushButton_backFromHistory;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 650);
        MainWindow->setStyleSheet(QString::fromUtf8("\n"
"QWidget {\n"
"    background-color: #2E3440;\n"
"    color: #ECEFF4;\n"
"    font-family: \"Segoe UI\", Arial, sans-serif;\n"
"}\n"
"\n"
"QMainWindow {\n"
"    background-color: #2E3440;\n"
"}\n"
"\n"
"QPushButton {\n"
"    background-color: #4C566A;\n"
"    color: #ECEFF4;\n"
"    border: 1px solid #4C566A;\n"
"    border-radius: 8px;\n"
"    padding: 10px;\n"
"    font-size: 11pt;\n"
"    font-weight: bold;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #5E81AC;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: #81A1C1;\n"
"}\n"
"\n"
"/* Accent button style */\n"
"QPushButton#addTransactionButton, QPushButton#pushButton_saveTransaction {\n"
"    background-color: #88C0D0;\n"
"    color: #2E3440;\n"
"}\n"
"\n"
"QPushButton#addTransactionButton:hover,\n"
"QPushButton#pushButton_saveTransaction:hover {\n"
"    background-color: #8FBCBB;\n"
"}\n"
"\n"
"QPushButton#addTransactionButton:pressed,\n"
"QPushButton#pushButton_saveTransaction:pressed {\n"
"    background-color: #A3BE8C;\n"
""
                        "}\n"
"\n"
"/* Destructive action button style */\n"
"QPushButton#deleteTransactionButton, QPushButton#stopServerButton {\n"
"    background-color: #BF616A;\n"
"    color: #ECEFF4;\n"
"}\n"
"\n"
"QPushButton#deleteTransactionButton:hover,\n"
"QPushButton#stopServerButton:hover {\n"
"    background-color: #D08770;\n"
"}\n"
"\n"
"/* New styles for showAllButton and clearHistoryButton */\n"
"QPushButton#showAllButton {\n"
"    background-color: #88C0D0;\n"
"    color: #2E3440;\n"
"}\n"
"\n"
"QPushButton#showAllButton:hover {\n"
"    background-color: #8FBCBB;\n"
"}\n"
"\n"
"QPushButton#showAllButton:pressed {\n"
"    background-color: #A3BE8C;\n"
"}\n"
"\n"
"QPushButton#clearHistoryButton {\n"
"    background-color: #BF616A;\n"
"    color: #ECEFF4;\n"
"}\n"
"\n"
"QPushButton#clearHistoryButton:hover {\n"
"    background-color: #D08770;\n"
"}\n"
"\n"
"QLineEdit, QTextEdit, QSpinBox {\n"
"    background-color: #3B4252;\n"
"    border: 1px solid #4C566A;\n"
"    border-radius: 5px;\n"
"    padding: 8px;\n"
"    font-"
                        "size: 10pt;\n"
"    color: #ECEFF4;\n"
"}\n"
"\n"
"QLineEdit:focus, QTextEdit:focus, QSpinBox:focus {\n"
"    border-color: #88C0D0;\n"
"}\n"
"\n"
"QLabel {\n"
"    background-color: transparent;\n"
"    color: #ECEFF4;\n"
"    font-size: 10pt;\n"
"}\n"
"\n"
"QLabel#label_title, QLabel#label_addTitle, QLabel#label_transactionsTitle, QLabel#label_historyTitle {\n"
"    font-size: 24pt;\n"
"    font-weight: bold;\n"
"    color: #ECEFF4;\n"
"}\n"
"\n"
"QTableWidget {\n"
"    background-color: #3B4252;\n"
"    border: 1px solid #4C566A;\n"
"    gridline-color: #4C566A;\n"
"    color: #D8DEE9;\n"
"    font-size: 10pt;\n"
"}\n"
"\n"
"QTableWidget::item {\n"
"    padding: 5px;\n"
"}\n"
"\n"
"QHeaderView::section {\n"
"    background-color: #434C5E;\n"
"    color: #ECEFF4;\n"
"    padding: 6px;\n"
"    border: none;\n"
"    font-weight: bold;\n"
"    font-size: 11pt;\n"
"}\n"
"\n"
"QTableWidget::item:selected {\n"
"    background-color: #88C0D0;\n"
"    color: #2E3440;\n"
"}\n"
"\n"
"QRadioButton {\n"
"    font-size: "
                        "11pt;\n"
"    spacing: 10px;\n"
"}\n"
"\n"
"QRadioButton::indicator {\n"
"    width: 15px;\n"
"    height: 15px;\n"
"}\n"
"\n"
"QRadioButton::indicator::unchecked {\n"
"    border: 1px solid #4C566A;\n"
"    background-color: #3B4252;\n"
"    border-radius: 7px;\n"
"}\n"
"\n"
"QRadioButton::indicator::checked {\n"
"    border: 1px solid #88C0D0;\n"
"    background-color: #88C0D0;\n"
"    border-radius: 7px;\n"
"}\n"
"\n"
"QStackedWidget {\n"
"    background-color: #2E3440;\n"
"}\n"
"\n"
"QMenuBar {\n"
"    background-color: #3B4252;\n"
"    color: #ECEFF4;\n"
"}\n"
"\n"
"QMenuBar::item:selected {\n"
"    background-color: #4C566A;\n"
"}\n"
"\n"
"QStatusBar {\n"
"    background-color: #3B4252;\n"
"    color: #ECEFF4;\n"
"}\n"
"\n"
"QSpinBox::up-button, QSpinBox::down-button {\n"
"    width: 20px;\n"
"    height: 20px;\n"
"}\n"
""));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        mainLayout = new QVBoxLayout(centralwidget);
        mainLayout->setSpacing(0);
        mainLayout->setObjectName("mainLayout");
        mainLayout->setContentsMargins(0, 0, 0, 0);
        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName("stackedWidget");
        pageMainMenu = new QWidget();
        pageMainMenu->setObjectName("pageMainMenu");
        verticalLayout_main = new QVBoxLayout(pageMainMenu);
        verticalLayout_main->setSpacing(15);
        verticalLayout_main->setObjectName("verticalLayout_main");
        verticalLayout_main->setContentsMargins(50, 30, 50, 30);
        spacerTop = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_main->addItem(spacerTop);

        label_title = new QLabel(pageMainMenu);
        label_title->setObjectName("label_title");
        label_title->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_main->addWidget(label_title);

        buttonsLayout = new QGridLayout();
        buttonsLayout->setSpacing(15);
        buttonsLayout->setObjectName("buttonsLayout");
        launchServerButton = new QPushButton(pageMainMenu);
        launchServerButton->setObjectName("launchServerButton");
        launchServerButton->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        buttonsLayout->addWidget(launchServerButton, 0, 0, 1, 1);

        stopServerButton = new QPushButton(pageMainMenu);
        stopServerButton->setObjectName("stopServerButton");
        stopServerButton->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        buttonsLayout->addWidget(stopServerButton, 0, 1, 1, 1);

        addTransactionButton = new QPushButton(pageMainMenu);
        addTransactionButton->setObjectName("addTransactionButton");
        addTransactionButton->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        buttonsLayout->addWidget(addTransactionButton, 1, 0, 1, 2);

        editTransactionButton = new QPushButton(pageMainMenu);
        editTransactionButton->setObjectName("editTransactionButton");
        editTransactionButton->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        buttonsLayout->addWidget(editTransactionButton, 2, 0, 1, 1);

        deleteTransactionButton = new QPushButton(pageMainMenu);
        deleteTransactionButton->setObjectName("deleteTransactionButton");
        deleteTransactionButton->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        buttonsLayout->addWidget(deleteTransactionButton, 2, 1, 1, 1);

        showAllButton = new QPushButton(pageMainMenu);
        showAllButton->setObjectName("showAllButton");
        showAllButton->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        buttonsLayout->addWidget(showAllButton, 3, 0, 1, 2);

        showHistoryButton = new QPushButton(pageMainMenu);
        showHistoryButton->setObjectName("showHistoryButton");
        showHistoryButton->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        buttonsLayout->addWidget(showHistoryButton, 4, 0, 1, 1);

        clearHistoryButton = new QPushButton(pageMainMenu);
        clearHistoryButton->setObjectName("clearHistoryButton");
        clearHistoryButton->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        buttonsLayout->addWidget(clearHistoryButton, 4, 1, 1, 1);

        exitButton = new QPushButton(pageMainMenu);
        exitButton->setObjectName("exitButton");
        exitButton->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        buttonsLayout->addWidget(exitButton, 5, 0, 1, 2);


        verticalLayout_main->addLayout(buttonsLayout);

        spacerBottom = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_main->addItem(spacerBottom);

        stackedWidget->addWidget(pageMainMenu);
        pageAddTransaction = new QWidget();
        pageAddTransaction->setObjectName("pageAddTransaction");
        verticalLayout = new QVBoxLayout(pageAddTransaction);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(100, 30, 100, 30);
        label_addTitle = new QLabel(pageAddTransaction);
        label_addTitle->setObjectName("label_addTitle");
        label_addTitle->setAlignment(Qt::AlignmentFlag::AlignCenter);
        label_addTitle->setMargin(10);

        verticalLayout->addWidget(label_addTitle);

        formLayout_add = new QFormLayout();
        formLayout_add->setObjectName("formLayout_add");
        formLayout_add->setLabelAlignment(Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignVCenter);
        formLayout_add->setFormAlignment(Qt::AlignmentFlag::AlignHCenter|Qt::AlignmentFlag::AlignTop);
        formLayout_add->setHorizontalSpacing(20);
        formLayout_add->setVerticalSpacing(15);
        label = new QLabel(pageAddTransaction);
        label->setObjectName("label");

        formLayout_add->setWidget(0, QFormLayout::ItemRole::LabelRole, label);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        radioButton_income = new QRadioButton(pageAddTransaction);
        radioButton_income->setObjectName("radioButton_income");

        horizontalLayout->addWidget(radioButton_income);

        radioButton_expense = new QRadioButton(pageAddTransaction);
        radioButton_expense->setObjectName("radioButton_expense");
        radioButton_expense->setChecked(true);

        horizontalLayout->addWidget(radioButton_expense);


        formLayout_add->setLayout(0, QFormLayout::ItemRole::FieldRole, horizontalLayout);

        label_2 = new QLabel(pageAddTransaction);
        label_2->setObjectName("label_2");

        formLayout_add->setWidget(1, QFormLayout::ItemRole::LabelRole, label_2);

        lineEdit_category = new QLineEdit(pageAddTransaction);
        lineEdit_category->setObjectName("lineEdit_category");

        formLayout_add->setWidget(1, QFormLayout::ItemRole::FieldRole, lineEdit_category);

        label_3 = new QLabel(pageAddTransaction);
        label_3->setObjectName("label_3");

        formLayout_add->setWidget(2, QFormLayout::ItemRole::LabelRole, label_3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        spinBox_day = new QSpinBox(pageAddTransaction);
        spinBox_day->setObjectName("spinBox_day");
        spinBox_day->setMinimum(1);
        spinBox_day->setMaximum(31);

        horizontalLayout_2->addWidget(spinBox_day);

        spinBox_month = new QSpinBox(pageAddTransaction);
        spinBox_month->setObjectName("spinBox_month");
        spinBox_month->setMinimum(1);
        spinBox_month->setMaximum(12);

        horizontalLayout_2->addWidget(spinBox_month);

        spinBox_year = new QSpinBox(pageAddTransaction);
        spinBox_year->setObjectName("spinBox_year");
        spinBox_year->setMinimum(2000);
        spinBox_year->setMaximum(2100);

        horizontalLayout_2->addWidget(spinBox_year);


        formLayout_add->setLayout(2, QFormLayout::ItemRole::FieldRole, horizontalLayout_2);

        label_4 = new QLabel(pageAddTransaction);
        label_4->setObjectName("label_4");

        formLayout_add->setWidget(3, QFormLayout::ItemRole::LabelRole, label_4);

        lineEdit_amount = new QLineEdit(pageAddTransaction);
        lineEdit_amount->setObjectName("lineEdit_amount");

        formLayout_add->setWidget(3, QFormLayout::ItemRole::FieldRole, lineEdit_amount);

        label_5 = new QLabel(pageAddTransaction);
        label_5->setObjectName("label_5");
        label_5->setAlignment(Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignTop);

        formLayout_add->setWidget(4, QFormLayout::ItemRole::LabelRole, label_5);

        textEdit_description = new QTextEdit(pageAddTransaction);
        textEdit_description->setObjectName("textEdit_description");

        formLayout_add->setWidget(4, QFormLayout::ItemRole::FieldRole, textEdit_description);


        verticalLayout->addLayout(formLayout_add);

        label_addStatusMessage = new QLabel(pageAddTransaction);
        label_addStatusMessage->setObjectName("label_addStatusMessage");
        label_addStatusMessage->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout->addWidget(label_addStatusMessage);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(15);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        pushButton_cancelAddTransaction = new QPushButton(pageAddTransaction);
        pushButton_cancelAddTransaction->setObjectName("pushButton_cancelAddTransaction");

        horizontalLayout_3->addWidget(pushButton_cancelAddTransaction);

        pushButton_saveTransaction = new QPushButton(pageAddTransaction);
        pushButton_saveTransaction->setObjectName("pushButton_saveTransaction");

        horizontalLayout_3->addWidget(pushButton_saveTransaction);


        verticalLayout->addLayout(horizontalLayout_3);

        stackedWidget->addWidget(pageAddTransaction);
        pageTransactionsView = new QWidget();
        pageTransactionsView->setObjectName("pageTransactionsView");
        verticalLayout_view = new QVBoxLayout(pageTransactionsView);
        verticalLayout_view->setObjectName("verticalLayout_view");
        verticalLayout_view->setContentsMargins(20, 20, 20, 20);
        label_transactionsTitle = new QLabel(pageTransactionsView);
        label_transactionsTitle->setObjectName("label_transactionsTitle");
        label_transactionsTitle->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_view->addWidget(label_transactionsTitle);

        tableWidget_transactions = new QTableWidget(pageTransactionsView);
        tableWidget_transactions->setObjectName("tableWidget_transactions");
        tableWidget_transactions->setAlternatingRowColors(true);
        tableWidget_transactions->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);
        tableWidget_transactions->verticalHeader()->setVisible(false);

        verticalLayout_view->addWidget(tableWidget_transactions);

        pushButton_backToMenu = new QPushButton(pageTransactionsView);
        pushButton_backToMenu->setObjectName("pushButton_backToMenu");

        verticalLayout_view->addWidget(pushButton_backToMenu);

        stackedWidget->addWidget(pageTransactionsView);
        pageHistory = new QWidget();
        pageHistory->setObjectName("pageHistory");
        verticalLayout_history = new QVBoxLayout(pageHistory);
        verticalLayout_history->setObjectName("verticalLayout_history");
        verticalLayout_history->setContentsMargins(20, 20, 20, 20);
        label_historyTitle = new QLabel(pageHistory);
        label_historyTitle->setObjectName("label_historyTitle");
        label_historyTitle->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_history->addWidget(label_historyTitle);

        tableWidget_history = new QTableWidget(pageHistory);
        tableWidget_history->setObjectName("tableWidget_history");
        tableWidget_history->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);
        tableWidget_history->verticalHeader()->setVisible(false);

        verticalLayout_history->addWidget(tableWidget_history);

        pushButton_backFromHistory = new QPushButton(pageHistory);
        pushButton_backFromHistory->setObjectName("pushButton_backFromHistory");

        verticalLayout_history->addWidget(pushButton_backFromHistory);

        stackedWidget->addWidget(pageHistory);

        mainLayout->addWidget(stackedWidget);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "\320\234\320\265\320\275\320\265\320\264\320\266\320\265\321\200 \320\273\320\270\321\207\320\275\321\213\321\205 \321\204\320\270\320\275\320\260\320\275\321\201\320\276\320\262", nullptr));
        label_title->setText(QCoreApplication::translate("MainWindow", "\320\223\320\273\320\260\320\262\320\275\320\276\320\265 \320\274\320\265\320\275\321\216", nullptr));
        launchServerButton->setText(QCoreApplication::translate("MainWindow", "\360\237\232\200 \320\227\320\260\320\277\321\203\321\201\321\202\320\270\321\202\321\214 \321\201\320\265\321\200\320\262\320\265\321\200", nullptr));
        stopServerButton->setText(QCoreApplication::translate("MainWindow", "\360\237\233\221 \320\236\321\201\321\202\320\260\320\275\320\276\320\262\320\270\321\202\321\214 \321\201\320\265\321\200\320\262\320\265\321\200", nullptr));
        addTransactionButton->setText(QCoreApplication::translate("MainWindow", "\342\236\225 \320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214 \321\202\321\200\320\260\320\275\320\267\320\260\320\272\321\206\320\270\321\216", nullptr));
        editTransactionButton->setText(QCoreApplication::translate("MainWindow", "\360\237\226\213\357\270\217 \320\240\320\265\320\264\320\260\320\272\321\202\320\270\321\200\320\276\320\262\320\260\321\202\321\214 \321\202\321\200\320\260\320\275\320\267\320\260\320\272\321\206\320\270\321\216", nullptr));
        deleteTransactionButton->setText(QCoreApplication::translate("MainWindow", "\360\237\227\221\357\270\217 \320\243\320\264\320\260\320\273\320\270\321\202\321\214 \321\202\321\200\320\260\320\275\320\267\320\260\320\272\321\206\320\270\321\216", nullptr));
        showAllButton->setText(QCoreApplication::translate("MainWindow", "\360\237\247\276 \320\237\320\276\320\272\320\260\320\267\320\260\321\202\321\214 \320\262\321\201\320\265 \321\202\321\200\320\260\320\275\320\267\320\260\320\272\321\206\320\270\320\270", nullptr));
        showHistoryButton->setText(QCoreApplication::translate("MainWindow", "\360\237\223\234 \320\230\321\201\321\202\320\276\321\200\320\270\321\217 \320\264\320\265\320\271\321\201\321\202\320\262\320\270\320\271", nullptr));
        clearHistoryButton->setText(QCoreApplication::translate("MainWindow", "\360\237\247\271 \320\236\321\207\320\270\321\201\321\202\320\270\321\202\321\214 \320\270\321\201\321\202\320\276\321\200\320\270\321\216", nullptr));
        exitButton->setText(QCoreApplication::translate("MainWindow", "\360\237\232\252 \320\222\321\213\320\271\321\202\320\270", nullptr));
        label_addTitle->setText(QCoreApplication::translate("MainWindow", "\320\235\320\276\320\262\320\260\321\217 \321\202\321\200\320\260\320\275\320\267\320\260\320\272\321\206\320\270\321\217", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\320\242\320\270\320\277:", nullptr));
        radioButton_income->setText(QCoreApplication::translate("MainWindow", "\320\224\320\276\321\205\320\276\320\264", nullptr));
        radioButton_expense->setText(QCoreApplication::translate("MainWindow", "\320\240\320\260\321\201\321\205\320\276\320\264", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "\320\232\320\260\321\202\320\265\320\263\320\276\321\200\320\270\321\217:", nullptr));
        lineEdit_category->setPlaceholderText(QCoreApplication::translate("MainWindow", "\320\235\320\260\320\277\321\200\320\270\320\274\320\265\321\200, \320\277\321\200\320\276\320\264\321\203\320\272\321\202\321\213", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "\320\224\320\260\321\202\320\260:", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "\320\241\321\203\320\274\320\274\320\260:", nullptr));
        lineEdit_amount->setPlaceholderText(QCoreApplication::translate("MainWindow", "0.00", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "\320\236\320\277\320\270\321\201\320\260\320\275\320\270\320\265:", nullptr));
        textEdit_description->setPlaceholderText(QCoreApplication::translate("MainWindow", "\320\235\320\260\320\277\321\200\320\270\320\274\320\265\321\200, \320\267\320\260\321\200\320\277\320\273\320\260\321\202\320\260 \320\267\320\260 \320\274\320\260\320\271", nullptr));
        label_addStatusMessage->setText(QString());
        pushButton_cancelAddTransaction->setText(QCoreApplication::translate("MainWindow", "\342\254\205\357\270\217 \320\235\320\260\320\267\320\260\320\264", nullptr));
        pushButton_saveTransaction->setText(QCoreApplication::translate("MainWindow", "\360\237\222\276 \320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214", nullptr));
        label_transactionsTitle->setText(QCoreApplication::translate("MainWindow", "\320\241\320\277\320\270\321\201\320\276\320\272 \321\202\321\200\320\260\320\275\320\267\320\260\320\272\321\206\320\270\320\271", nullptr));
        pushButton_backToMenu->setText(QCoreApplication::translate("MainWindow", "\342\254\205\357\270\217 \320\235\320\260\320\267\320\260\320\264 \320\262 \320\274\320\265\320\275\321\216", nullptr));
        label_historyTitle->setText(QCoreApplication::translate("MainWindow", "\320\230\321\201\321\202\320\276\321\200\320\270\321\217 \320\264\320\265\320\271\321\201\321\202\320\262\320\270\320\271", nullptr));
        pushButton_backFromHistory->setText(QCoreApplication::translate("MainWindow", "\342\254\205\357\270\217 \320\235\320\260\320\267\320\260\320\264 \320\262 \320\274\320\265\320\275\321\216", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
