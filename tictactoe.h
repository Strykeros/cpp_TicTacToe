#ifndef TICTACTOE_H
#define TICTACTOE_H

#include <QMainWindow>
#include <logic/checkwinner.h>
#include <logic/playerturn.h>
#include <layout/sidemenu.h>
#include <QGridLayout>

QT_BEGIN_NAMESPACE
namespace Ui {
class TicTacToe;
}
QT_END_NAMESPACE

class TicTacToe : public QMainWindow
{
    Q_OBJECT

public:
    TicTacToe(QWidget *parent = nullptr);
    ~TicTacToe();

private:
    Ui::TicTacToe *ui;
    void initGrid(QGridLayout *layout, QWidget *widget, SideMenu* menu, CheckWinner *winner);
    void updateButtonText(QPushButton* btn, PlayerTurn* turn, CheckWinner *winner);
    void checkForTurns(CheckWinner *winner, QWidget *widget, SideMenu *menu, QTimer *mainTimer, QString playerX, QString playerO);
    void showLeaderboard();
};
#endif
