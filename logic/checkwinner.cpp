#include <string>
#include "database.h"
#include "checkwinner.h"
#include <QString>
#include <iostream>
#include <QList>
#include <QWidget>
#include <QPushButton>

using namespace std;

Database* CheckWinner::innerDb;
QString CheckWinner::playerX;
QString CheckWinner::playerO;

CheckWinner::CheckWinner(Database* db, QString inputPlayerX, QString inputPlayerO) {
    CheckWinner::innerDb = db;
    CheckWinner::playerX = inputPlayerX;
    CheckWinner::playerO = inputPlayerO;
};

const int CheckWinner::winCombos[8][3] = {
    {1, 2, 3}, {4, 5, 6}, {7, 8, 9},
    {1, 4, 7}, {2, 5, 8}, {3, 6, 9},
    {1, 5, 9}, {3, 5, 7}
};

bool CheckWinner::winnerExists = false;

QString CheckWinner::checkForWin(QWidget *widget)
{
    QList<QPushButton*> btnObjects = getBtnObjects(widget);

    for (int i = 0; i < 8; i++)
    {
        int j = 0;
        QString btnName1 = "button" + QString::number(winCombos[i][j]);
        QString btnName2 = "button" + QString::number(winCombos[i][j+1]);
        QString btnName3 = "button" + QString::number(winCombos[i][j+2]);

        QPushButton* btn1 = getBtnByName(btnName1, btnObjects);
        QPushButton* btn2 = getBtnByName(btnName2, btnObjects);
        QPushButton* btn3 = getBtnByName(btnName3, btnObjects);

        if (btn1->text() == btn2->text() && btn2->text() == btn3->text() &&
        btn1->text() != "" && btn2->text() != "" && btn3->text() != "")
        {
            winnerExists = true;
            QString winner = btn1->text() == "x" ? playerX : playerO;
            CheckWinner::innerDb->updateData(winner);
            return winner;
        }
    }

    return "";
}

QString CheckWinner::checkForDraw(QWidget *widget){
    QList<QPushButton*> btnObjects = getBtnObjects(widget);
    bool gridIsFilled = btnsContainValue(btnObjects);

    if(gridIsFilled && !winnerExists){
        return "draw";
    }

    return "";
}

bool CheckWinner::btnsContainValue(QList<QPushButton*> buttons){
    for (QPushButton* button : buttons) {
        if (button->text().isEmpty()) {
            return false;
        }
    }
    return true;
}

QList<QPushButton*> CheckWinner::getBtnObjects(QWidget *widget) {
    QList<QPushButton*> buttons;
    if (!widget) return buttons;

    const auto children = widget->findChildren<QPushButton* >();
    for (QPushButton* button : children) {
        buttons.append(button);
    }

    return buttons;
}

QPushButton* CheckWinner::getBtnByName(QString btnName, QList<QPushButton*> btns){
    
    for(QPushButton* btn : btns)
    {
        if (btn->objectName() == btnName)
        {
            return btn;
        }
    }

    return NULL;
}

bool CheckWinner::getWinnerStatus(){
    return winnerExists;
}
