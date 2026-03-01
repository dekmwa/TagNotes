#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>


class Database
{
public:
    static Database& instance() {
        static Database instance;
        return instance;
    }

    Database(const Database&) = delete;
    Database& operator=(const Database&) = delete;
    Database(Database&&) = delete;
    Database& operator=(Database&&) = delete;

    bool connectDatabase();

private:
    Database() = default;
    ~Database() = default;

    bool initTables();

    QSqlDatabase m_dataBase;
};

#endif // DATABASE_H
