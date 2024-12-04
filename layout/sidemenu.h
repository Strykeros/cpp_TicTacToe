#ifndef SIDEMENU_H
#define SIDEMENU_H
#include <QLabel>
#include <QWidget>
#include "./logic/database.h"
#include <QDockWidget>

class SideMenu
{
private:
    QWidget* parentWidget;
    QLabel *playerTurnLabel;
    static Database* innerDb;
public:
    explicit SideMenu(Database* db);
    void showLeaderboard();
    QDockWidget* initSideMenu(QWidget* parent);
    void updateTurnLbl(QString playerX, QString playerO);
    void setEndGameTxtLbl(QString text);
};

#endif // SIDEMENU_H
