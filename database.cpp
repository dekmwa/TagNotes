#include "database.h"


bool Database::connectDatabase() {
    if (m_dataBase.isOpen()) {
        return true;
    }

    m_dataBase = QSqlDatabase::addDatabase("QSQLITE");
    m_dataBase.setDatabaseName("TagNotes.db");

    if (!m_dataBase.open()) {
        qDebug() << "Ошибка подключения к базе данных: " << m_dataBase.lastError().text();
        return false;
    } else {
        qDebug() << "Подключение к базе данных установлено.";
        if (!initTables()) {
            return false;
        }
        return true;
    }
}

bool Database::initTables() {
    QSqlQuery query;
    bool success;

    success = query.exec("CREATE TABLE IF NOT EXISTS tag_categories ("
                "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                "title VARCHAR(50) NOT NULL"
                ")");
    if (!success) {
        qDebug() << "Ошибка создания таблицы tag_categories: " << query.lastError().text();
        return false;
    }

    success = query.exec("CREATE TABLE IF NOT EXISTS tags ("
                "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                "title VARCHAR(50) NOT NULL,"
                "category_id INTEGER NOT NULL,"
                "FOREIGN KEY (category_id) REFERENCES tag_categories (id) ON DELETE CASCADE"
                ")");
    if (!success) {
        qDebug() << "Ошибка создания таблицы tags: " << query.lastError().text();
        return false;
    }

    success = query.exec("CREATE TABLE IF NOT EXISTS tags_by_date ("
                "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                "date DATE NOT NULL,"
                "tag_id INTEGER NOT NULL,"
                "FOREIGN KEY (tag_id) REFERENCES tags (id) ON DELETE CASCADE"
                ")");
    if (!success) {
        qDebug() << "Ошибка создания таблицы tags_by_date: " << query.lastError().text();
        return false;
    }

    return true;
}
