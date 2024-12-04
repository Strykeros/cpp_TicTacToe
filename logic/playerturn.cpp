#include <string>
#include "playerturn.h"
#include <QString>

using namespace std;

QString PlayerTurn::player = "o";

// sets the next turn
QString PlayerTurn::checkTurn(QString previousTurn)
{
    QString nextTurn;
    if (previousTurn == "")
    {
        return "x";
    }

    if (previousTurn == "x")
        nextTurn = "o";
    else
        nextTurn = "x";

    player = nextTurn;
    return nextTurn;
}

// returns the current turn
QString PlayerTurn::getCurrentTurn()
{
    return player;
}

// returns player text for side menu label
QString PlayerTurn::getCurrentTurnTxt(QString playerX, QString playerO)
{
    if(player == "" || player == "x")
        return playerO;
    else
        return playerX;
}
