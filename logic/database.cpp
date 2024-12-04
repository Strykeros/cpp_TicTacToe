#include "database.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDir>
#include <QVector>
#include <QPair>
#include <QDebug>
#include <iostream>

using namespace std;

Database::Database() {

}

// connect to database
void Database::initializeDatabase() {
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    QString path = "../../databases/game_data.db";

    db.setDatabaseName(path);

    if (!db.open()) {
        cout << "Error: connection with database failed: "
                  << db.lastError().text().toStdString();
    } else {
        cout << "Database: connection ok" << "\n";
    }

    createTable();
}

// create necessary tables
void Database::createTable() {
    QSqlQuery query;
    query.exec(
        "CREATE TABLE IF NOT EXISTS leaderboard ("
        "id INTEGER UNIQUE, "
        "player TEXT NOT NULL, "
        "score INTEGER NOT NULL, "
        "PRIMARY KEY(id AUTOINCREMENT))"
        );
}

// insert player name and initial score
void Database::insertData(QString player) {
    QSqlQuery insertQuery;
    insertQuery.prepare("INSERT INTO leaderboard (player, score) VALUES (:player, :score)");
    insertQuery.bindValue(":player", player);
    insertQuery.bindValue(":score", 0);
    insertQuery.exec();
}

// update score for player who won the game
void Database::updateData(QString player) {
    QSqlQuery query;
    query.prepare("SELECT score FROM leaderboard WHERE player = :player");
    query.bindValue(":player", player);
    query.exec();

    if (query.next()) {
        int currentScore = query.value(0).toInt();
        QSqlQuery updateQuery;
        updateQuery.prepare("UPDATE leaderboard SET score = :score WHERE player = :player");
        updateQuery.bindValue(":score", currentScore + 1);
        updateQuery.bindValue(":player", player);
        updateQuery.exec();
    }
}

// returns whether there is a player or not
bool Database::playerFound(QString player) {
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM leaderboard WHERE player = :player");
    query.bindValue(":player", player);
    query.exec();

    if (query.next()) {
        int count = query.value(0).toInt();
        return count > 0;
    }

    return false;
}

// gets all players that have a score of atleast "1"
QVector<QPair<QString, int>> Database::showStats() {
    QVector<QPair<QString, int>> stats;
    QSqlQuery query;
    query.prepare("SELECT player, score FROM leaderboard ORDER BY score DESC");

    if (query.exec()) {
        while (query.next()) {
            QString player = query.value(0).toString();
            int score = query.value(1).toInt();
            stats.append(qMakePair(player, score));
        }
    }

    return stats;
}
