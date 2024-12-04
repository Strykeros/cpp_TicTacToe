#include "tictactoe.h"
#include "ui_tictactoe.h"
#include <QGridLayout>
#include <QPushButton>
#include "./logic/playerturn.h"
#include "./logic/checkwinner.h"
#include "./layout/sidemenu.h"
#include <QString>
#include <memory>
#include <QMessageBox>
#include <QTimer>
#include <QDockWidget>
#include <QListWidget>
#include <QLabel>
#include <iostream>
#include <QDir>
#include <QInputDialog>
#include "./logic/database.h"

using namespace std;

// sets grid button's text on click
void TicTacToe::updateButtonText(QPushButton* btn, PlayerTurn* turn, CheckWinner *winner)
{
    bool winnerExists = winner->getWinnerStatus();
    if(btn->text() == "" && !winnerExists)
    {
        QString currentTurn = turn->getCurrentTurn();
        QString nxtTurn = turn->checkTurn(currentTurn);
        btn->setText(nxtTurn);
    }
}

// creates 9 buttons for grid
void TicTacToe::initGrid(QGridLayout *layout, QWidget *widget, SideMenu* menu, CheckWinner *winner)
{
    PlayerTurn *turn = new PlayerTurn();
    int btnNumber = 1;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            QPushButton *button = new QPushButton("", widget);
            QFont font = button->font();
            font.setPointSize(16);
            button->setFont(font);
            button->setObjectName("button" + QString::number(btnNumber));
            button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
            QObject::connect(button, &QPushButton::clicked, [this, button, turn, winner, widget, menu]() {
                 updateButtonText(button, turn, winner);

            });
            layout->addWidget(button, i, j);
            btnNumber++;
        }
        
    }   
}

TicTacToe::TicTacToe(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::TicTacToe)
{
    ui->setupUi(this);

    QString playerX, playerO;
    bool ok;

    // asks player X for username
    while (true) {
        playerX = QInputDialog::getText(this, tr("Enter Nickname"),
                                        tr("Player X, enter your nickname (atleast 4 chars long):"), QLineEdit::Normal,
                                        QDir::home().dirName(), &ok);
        if (ok && !playerX.isEmpty() && playerX.length() == 4) break;
        QMessageBox::warning(this, tr("Nickname Required"), tr("You must enter a nickname to continue."));
    }

    // asks player O for username
    while (true) {
        playerO = QInputDialog::getText(this, tr("Enter Nickname"),
                                        tr("Player O, enter your nickname (atleast 4 chars long):"), QLineEdit::Normal,
                                        QDir::home().dirName(), &ok);
        if (ok && !playerO.isEmpty() && playerX.length() == 4) break;
        QMessageBox::warning(this, tr("Nickname Required"), tr("You must enter a nickname to continue."));
    }

    Database *db = new Database();
    SideMenu *menu = new SideMenu(db);
    QWidget *centralWidget = new QWidget(this);

    db->initializeDatabase();

    bool playerXExists = db->playerFound(playerX);
    bool playerOExists = db->playerFound(playerO);

    // if player X name does not exist, insert it in DB
    if(!playerXExists){
        db->insertData(playerX);
    }

    // if player O name does not exist, insert it in DB
    if(!playerOExists){
        db->insertData(playerO);
    }

    CheckWinner *winner = new CheckWinner(db, playerX, playerO);

    // create grid layout
    this->setCentralWidget(centralWidget);
    QGridLayout *layout = new QGridLayout(centralWidget);
    initGrid(layout, centralWidget, menu, winner);
    centralWidget->setLayout(layout);

    // create side menu
    QDockWidget *sideMenuDock = menu->initSideMenu(centralWidget);
    this->addDockWidget(Qt::LeftDockWidgetArea, sideMenuDock);

    // create and start main timer
    QTimer *mainTimer = new QTimer(this);
    mainTimer->setInterval(100);
    connect(mainTimer, &QTimer::timeout, this, [this, winner, centralWidget, menu, mainTimer, playerX, playerO] {
        checkForTurns(winner, centralWidget, menu, mainTimer, playerX, playerO);
    });
    mainTimer->start();
}

// checks for game end
void TicTacToe::checkForTurns(CheckWinner *winner, QWidget *widget, SideMenu *menu, QTimer *mainTimer, QString playerX, QString playerO){
    QString win = winner->checkForWin(widget);
    QString draw = winner->checkForDraw(widget);
    menu->updateTurnLbl(playerX, playerO);

    if(!win.isEmpty()){
        menu->setEndGameTxtLbl("The winner is " + win);
        mainTimer->stop();
    }

    if(!draw.isEmpty()){
        menu->setEndGameTxtLbl("Its a draw!");
        mainTimer->stop();
    }
}

TicTacToe::~TicTacToe()
{
    delete ui;
}




