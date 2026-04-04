#include "database.h"


bool Database::connectDatabase(QString& path) {
    QFile dbFile(path);
    if (!dbFile.exists()) {
        qDebug() << "Database::connectDatabase: файла "
                 << path << " не существует.";
        return false;
    }

    if (dbFile.open(QIODevice::ReadOnly)) {
        QByteArray header = dbFile.read(16);
        dbFile.close();

        if (!header.startsWith("SQLite format 3")) {
            qDebug() << "Database::connectDatabase: Содержимое файла имеет не sqlite3 формат.";
            return false;
        }
    } else {
        return false;
    }

    if (m_dataBase.isOpen()) {
        qDebug() << "Database::connectDatabase: подключение было активно, попытка подключения к другому файлу.";
        m_dataBase.close();
        m_dataBase = QSqlDatabase();
    }

    if (QSqlDatabase::contains("notesDb")) QSqlDatabase::removeDatabase("notesDb");

    m_dataBase = QSqlDatabase::addDatabase("QSQLITE", "notesDb");
    m_dataBase.setDatabaseName(path);

    if (!m_dataBase.open()) {
        qDebug() << "Database::connectDatabase: Ошибка подключения к базе данных: " << m_dataBase.lastError().text();
        return false;
    } else {
        qDebug() << "Database::connectDatabase: Подключение к базе данных установлено. " << path;
        if (!initTables()) {
            return false;
        }
        return true;
    }
}

bool Database::createAndConnect(QString& path) {
    if (m_dataBase.isOpen()) {
        m_dataBase.close();
        m_dataBase = QSqlDatabase();
    }

    if (QSqlDatabase::contains("notesDb")) QSqlDatabase::removeDatabase("notesDb");

    m_dataBase = QSqlDatabase::addDatabase("QSQLITE", "notesDb");
    m_dataBase.setDatabaseName(path);

    if (!m_dataBase.open()) {
        qDebug() << "Database::createAndConnect: Ошибка подключения к базе данных: " << m_dataBase.lastError().text();
        return false;
    } else {
        qDebug() << "Database::createAndConnect: Подключение к базе данных установлено. " << path;
        if (!initTables()) {
            return false;
        }
        return true;
    }
}

bool Database::isOpen() {
    return m_dataBase.isOpen();
}

bool Database::initTables() {
    QSqlQuery query(m_dataBase);
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
    QSqlQuery query(m_dataBase);
    query.prepare("INSERT INTO tag_categories (title) VALUES (:title)");
    query.bindValue(":title", title);

    if (!query.exec()) {
        qDebug() << "Ошибка добавления категории: " << query.lastError().text();
        return false;
    }
    return true;
}

bool Database::addTag(QString title, int categoryId) {
    QSqlQuery query(m_dataBase);
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

    QSqlQuery deleteQuery(m_dataBase);
    deleteQuery.prepare("DELETE FROM tags_by_date WHERE date = :date");
    deleteQuery.bindValue(":date", date);

    if (!deleteQuery.exec()) {
        qDebug() << "Ошибка при удалении старых тегов: " << deleteQuery.lastError().text();
        m_dataBase.rollback();
        return false;
    }

    QSqlQuery insertQuery(m_dataBase);
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
    QSqlQuery query(m_dataBase);

    if (!query.exec("SELECT id, title FROM tag_categories")) {
        qDebug() << "Ошибка получения категорий: " << query.lastError().text();
        return categories;
    }

    while (query.next()) {
        int id = query.value(0).toInt();
        QString title = query.value(1).toString();
        categories.insert(id, title);
    }

    return categories;
}

QMap<int, QString> Database::getTagsByCategoryId(int categoryId) {
    QMap<int, QString> tags;
    QSqlQuery query(m_dataBase);
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

    QSqlQuery query(m_dataBase);
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
    QSqlQuery query(m_dataBase);
    query.prepare("SELECT title FROM tags WHERE id = :tagId");
    query.bindValue(":tagId", tagId);

    if (!query.exec()) {
        qDebug() <<  "Database::getTagTitleById: " << query.lastError().text();
        return "";
    }

    if (query.next()) {
        return query.value(0).toString();
    }
    return "";
}

bool Database::deleteEmptyCategory(int categoryId) {
    QSqlQuery tagsByCategory(m_dataBase);
    tagsByCategory.prepare("SELECT COUNT(*) FROM tags WHERE category_id = :categoryId");
    tagsByCategory.bindValue(":categoryId", categoryId);

    if (!tagsByCategory.exec()) {
        qDebug() << "Database::deleteEmptyCategory: " << tagsByCategory.lastError().text();
        return false;
    }

    if (tagsByCategory.next()) {
        int tagsCount = tagsByCategory.value(0).toInt();
        if (tagsCount > 0) {
            qDebug() << "Database::deleteEmptyCategory: в категории есть теги";
            return false;
        }
    }

    QSqlQuery deleteCategory(m_dataBase);
    deleteCategory.prepare("DELETE FROM tag_categories WHERE id = :categoryId");
    deleteCategory.bindValue(":categoryId", categoryId);
    if (!deleteCategory.exec()) {
        qDebug() << "Database::deleteEmptyCategory: " << deleteCategory.lastError().text();
        return false;
    }

    qDebug() << "Database::deleteEmptyCategory " << categoryId;
    return true;
}

bool Database::deleteTag(int tagId) {
    if (!m_dataBase.transaction()) {
        qDebug() << "Database::deleteTag - Не удалось начать транзакцию: " << m_dataBase.lastError().text();
        return false;
    }

    QSqlQuery deleteFromTagsByDate(m_dataBase);
    deleteFromTagsByDate.prepare("DELETE FROM tags_by_date WHERE tag_id = :tagId");
    deleteFromTagsByDate.bindValue(":tagId", tagId);

    if (!deleteFromTagsByDate.exec()) {
        qDebug() << "Database::deleteTag - ошибка во время удаления из таблицы tags_by_date: " << deleteFromTagsByDate.lastError().text();
        m_dataBase.rollback();
        return false;
    }

    QSqlQuery deleteFromTags(m_dataBase);
    deleteFromTags.prepare("DELETE FROM tags WHERE id = :tagId");
    deleteFromTags.bindValue(":tagId", tagId);

    if (!deleteFromTags.exec()) {
        qDebug() << "Database::deleteTag - ошибка во время удаления из таблицы tags: " << deleteFromTags.lastError().text();
        m_dataBase.rollback();
        return false;
    }

    if (!m_dataBase.commit()) {
        qDebug() << "Database::deleteTag - Не удалось сделать commit изменений: " << m_dataBase.lastError().text();
        return false;
    }

    return true;
}

void Database::updateCategoryTitle(int categoryId, QString newTitle) {
    QSqlQuery query(m_dataBase);
    query.prepare("UPDATE tag_categories SET title = :newTitle WHERE id = :id");
    query.bindValue(":newTitle", newTitle);
    query.bindValue(":id", categoryId);

    if (!query.exec()) {
        qDebug() << "Database::updateCategoryTitle: " << query.lastError().text();
    }
}

void Database::updateTagTitle(int tagId, QString newTitle) {
    QSqlQuery query(m_dataBase);
    query.prepare("UPDATE tags SET title = :newTitle WHERE id = :id");
    query.bindValue(":newTitle", newTitle);
    query.bindValue(":id", tagId);

    if (!query.exec()) {
        qDebug() << "Database::updateTagTitle: " << query.lastError().text();
    }
}
