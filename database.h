#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QDate>
#include <QFile>

using namespace std;


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

    bool connectDatabase(QString& path);
    bool createAndConnect(QString& path);
    bool isOpen();

    bool addCategory(QString title);
    bool addTag(QString title, int categoryId);
    bool updateAllTagsByDate(QDate date, const QVector<int>& tagsId);

    bool deleteEmptyCategory(int categoryId);
    bool deleteTag(int tagId);

    QMap<int, QString> getAllCategories();
    QMap<int, QString> getTagsByCategoryId(int categoryId);
    QMap<int, QString> getTagsByDate(QDate date);
    const QString getTagTitleById(int tagId);

    void updateCategoryTitle(int categoryId, QString newTitle);
    void updateTagTitle(int categoryId, QString newTitle);

private:
    Database() = default;
    ~Database() = default;

    bool initTables();

    QSqlDatabase m_dataBase;
};

#endif // DATABASE_H
