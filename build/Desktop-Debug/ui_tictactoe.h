/********************************************************************************
** Form generated from reading UI file 'tictactoe.ui'
**
** Created by: Qt User Interface Compiler version 5.15.15
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TICTACTOE_H
#define UI_TICTACTOE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TicTacToe
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *TicTacToe)
    {
        if (TicTacToe->objectName().isEmpty())
            TicTacToe->setObjectName(QString::fromUtf8("TicTacToe"));
        TicTacToe->resize(800, 600);
        centralwidget = new QWidget(TicTacToe);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        TicTacToe->setCentralWidget(centralwidget);
        menubar = new QMenuBar(TicTacToe);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 27));
        TicTacToe->setMenuBar(menubar);
        statusbar = new QStatusBar(TicTacToe);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        TicTacToe->setStatusBar(statusbar);

        retranslateUi(TicTacToe);

        QMetaObject::connectSlotsByName(TicTacToe);
    } // setupUi

    void retranslateUi(QMainWindow *TicTacToe)
    {
        TicTacToe->setWindowTitle(QCoreApplication::translate("TicTacToe", "TicTacToe", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TicTacToe: public Ui_TicTacToe {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TICTACTOE_H
