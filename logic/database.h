#ifndef DATABASE_H
#define DATABASE_H
#include <QString>
#include <QVector>
#include <QPair>

class Database
{
public:
    Database();
    void initializeDatabase();
    void createTable();
    void insertData(QString player);
    void updateData(QString player);
    bool playerFound(QString player);
    QVector<QPair<QString, int>> showStats();
};

#endif // DATABASE_H
