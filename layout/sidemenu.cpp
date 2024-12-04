#include "sidemenu.h"
#include "./logic/playerturn.h"
#include <QDockWidget>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include <QMessageBox>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QDialog>

Database* SideMenu::innerDb;
SideMenu::SideMenu(Database* db){
    SideMenu::innerDb = db;
}


QDockWidget* SideMenu::initSideMenu(QWidget* parent) {
    QDockWidget *sideMenuDock = new QDockWidget("Game Info", parent);
    sideMenuDock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    sideMenuDock->setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetFloatable);

    QWidget *gameInfoWidget = new QWidget;
    QVBoxLayout *gameInfoLayout = new QVBoxLayout(gameInfoWidget);

    SideMenu::playerTurnLabel = new QLabel("Turn: Player X");
    gameInfoLayout->addWidget(playerTurnLabel);

    QLabel *winnerLabel = new QLabel("Winner: None");
    winnerLabel->hide();
    gameInfoLayout->addWidget(winnerLabel);

    QPushButton *leaderboardButton = new QPushButton("Leaderboard");
    gameInfoLayout->addWidget(leaderboardButton);

    QObject::connect(leaderboardButton, &QPushButton::clicked, [this]() {
        showLeaderboard();
    });

    sideMenuDock->setWidget(gameInfoWidget);
    return sideMenuDock;
}

void SideMenu::updateTurnLbl(QString playerX, QString playerO) {
    PlayerTurn *turn = new PlayerTurn();
    QString currentTurnTxt = turn->getCurrentTurnTxt(playerX, playerO);
    playerTurnLabel->setText(currentTurnTxt + "'s turn");
}

void SideMenu::setEndGameTxtLbl(QString text){
    playerTurnLabel->setText(text);
}

void SideMenu::showLeaderboard() {
    QVector<QPair<QString, int>> stats = SideMenu::innerDb->showStats();
    QDialog *dialog = new QDialog();
    QTableWidget *table = new QTableWidget(stats.size(), 2, dialog);
    QVBoxLayout *layout = new QVBoxLayout();

    dialog->setWindowTitle("Leaderboard");
    table->setHorizontalHeaderLabels({"Player", "Score"});

    for (int i = 0; i < stats.size(); i++) {
        QTableWidgetItem *playerItem = new QTableWidgetItem(stats[i].first);
        QTableWidgetItem *scoreItem = new QTableWidgetItem(QString::number(stats[i].second));
        table->setItem(i, 0, playerItem);
        table->setItem(i, 1, scoreItem);
    }

    table->resizeColumnsToContents();
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->setSelectionMode(QAbstractItemView::NoSelection);
    table->setFocusPolicy(Qt::NoFocus);

    layout->addWidget(table);
    dialog->setLayout(layout);

    dialog->exec();
}
