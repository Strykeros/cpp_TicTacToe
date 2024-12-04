#ifndef PLAYERTURN_H
#define PLAYERTURN_H

#include <string>
#include <QString>

using namespace std;

class PlayerTurn
{
private:
    static QString player;
public:
    QString checkTurn(QString previousTurn);
    QString getCurrentTurn();
    QString getCurrentTurnTxt(QString playerX, QString playerO);
};

#endif PLAYERTURN_H
