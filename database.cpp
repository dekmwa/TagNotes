#include "database.h"

// using namespace std;


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
                "title VARCHAR(50) NOT NULL UNIQUE"
                ")");
    if (!success) {
        qDebug() << "Ошибка создания таблицы tag_categories: " << query.lastError().text();
        return false;
    }

    success = query.exec("CREATE TABLE IF NOT EXISTS tags ("
                "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                "title VARCHAR(50) NOT NULL UNIQUE,"
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

bool Database::addCategory(QString title) {
    QSqlQuery query;
    query.prepare("INSERT INTO tag_categories (title) VALUES (:title)");
    query.bindValue(":title", title);

    if (!query.exec()) {
        qDebug() << "Ошибка добавления категории: " << query.lastError().text();
        return false;
    }
    return true;
}

bool Database::addTag(QString title, int categoryId) {
    QSqlQuery query;
    query.prepare("INSERT INTO tags (title, category_id) VALUES (:title, :category_id)");
    query.bindValue(":title", title);
    query.bindValue(":category_id", categoryId);

    if (!query.exec()) {
        qDebug() << "Ошибка добавления тега: " << query.lastError().text();
        return false;
    }
    return true;
}

bool Database::updateAllTagsByDate(QDate date, const QVector<int>& tagsId) {
    if (!m_dataBase.transaction()) {
        qDebug() << "Не удалось начать транзакцию: " << m_dataBase.lastError().text();
        return false;
    }

    QSqlQuery deleteQuery;
    deleteQuery.prepare("DELETE FROM tags_by_date WHERE date = :date");
    deleteQuery.bindValue(":date", date);

    if (!deleteQuery.exec()) {
        qDebug() << "Ошибка при удалении старых тегов: " << deleteQuery.lastError().text();
        m_dataBase.rollback();
        return false;
    }

    QSqlQuery insertQuery;
    insertQuery.prepare("INSERT INTO tags_by_date (date, tag_id) VALUES (:date, :tag_id)");
    for (int tagId : tagsId) {
        insertQuery.bindValue(":date", date);
        insertQuery.bindValue(":tag_id", tagId);

        if (!insertQuery.exec()) {
            qDebug() << "Ошибка при добавлении тега с id: " << tagId << " " << insertQuery.lastError().text();
            m_dataBase.rollback();
            return false;
        }
    }

    if (!m_dataBase.commit()) {
        qDebug() << "Не удалось сделать commit изменений: " << m_dataBase.lastError().text();
        return false;
    }

    qDebug() << "";
    qDebug() << "БД: сохраненные теги";
    for (int id : tagsId) {
        qDebug() << id;
    }
    return true;
}

QMap<int, QString> Database::getAllCategories() {
    QMap<int, QString> categories;
    QSqlQuery query;
    query.exec("SELECT id, title FROM tag_categories");

    while (query.next()) {
        int id = query.value(0).toInt();
        QString title = query.value(1).toString();
        categories.insert(id, title);
    }

    return categories;
}

QMap<int, QString> Database::getTagsByCategoryId(int categoryId) {
    QMap<int, QString> tags;
    QSqlQuery query;
    query.prepare("SELECT id, title FROM tags WHERE category_id = :category_id");
    query.bindValue(":category_id", categoryId);

    if (!query.exec()) {
        qDebug() << "Ошибка при получении тегов по категории с id: " << categoryId << " " << query.lastError().text();
        return tags;
    }

    while (query.next()) {
        int id = query.value(0).toInt();
        QString title = query.value(1).toString();
        tags.insert(id, title);
    }

    return tags;
}

QMap<int, QString> Database::getTagsByDate(QDate date) {
    QMap<int, QString> tags;

    QSqlQuery query;
    query.prepare("SELECT tags.id, tags.title FROM tags_by_date "
                  "JOIN tags ON tags.id = tags_by_date.tag_id "
                  "WHERE tags_by_date.date = :date");
    query.bindValue(":date", date.toString(Qt::ISODate));

    if (!query.exec()) {
        qDebug() << "Database::getTagsByDate " << query.lastError().text();
        return tags;
    }

    while(query.next()) {
        int id = query.value(0).toInt();
        QString title = query.value(1).toString();
        tags.insert(id, title);
    }

    return tags;
}

const QString Database::getTagTitleById(int tagId) {
    QSqlQuery query;
    query.prepare("SELECT title FROM tags WHERE id = :tagId");
    query.bindValue(":tagId", tagId);

    if (!query.exec()) {
        qDebug() <<  "Database::getTagTitleById";
        return "";
    }

    query.next();
    return query.value(0).toString();
}
