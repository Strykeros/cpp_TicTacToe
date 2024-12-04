#ifndef CHECKWINNER_H
#define CHECKWINNER_H
#include <string>
#include "checkwinner.h"
#include "database.h"
#include <QString>
#include <QList>
#include <QWidget>
#include <QPushButton>


using namespace std;

class CheckWinner
{
private:
    static const int winCombos[8][3];
    static bool winnerExists;
    static Database* innerDb;
    static QString playerX;
    static QString playerO;
public:
    explicit CheckWinner(Database* db, QString inputPlayerX, QString inputPlayerO);
    ~CheckWinner();
    QString checkForWin(QWidget *widget);
    QString checkForDraw(QWidget *widget);
    QList<QPushButton*> getBtnObjects(QWidget *widget);
    QPushButton* getBtnByName(QString btnName, QList<QPushButton*> btns);
    bool btnsContainValue(QList<QPushButton *> buttons);
    bool getWinnerStatus();
};

#endif CHECKWINNER_H
