#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QDate>
#include <QFile>
#include <QObject>

using namespace std;

enum MarkType {
    WITHOUT = 0,
    NUMBER = 1
};

struct MarkValue {
    int valueInt = 0;
    QString valueString;
    int valueTime = 0;
};


class Database : public QObject
{
    Q_OBJECT

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
    bool addTag(QString title, int categoryId, MarkType markType);
    bool updateAllTagsByDate(QDate date, const QMap<int, MarkValue>& tagsMarks);

    bool deleteEmptyCategory(int categoryId);
    bool deleteTag(int tagId);

    QMap<int, QString> getAllCategories();
    QMap<int, QString> getTagsByCategoryId(int categoryId);
    QMap<int, QString> getTagsDisplayTitleByDate(QDate date);
    QMap<int, MarkValue> getTagsWithMarkValue(QDate date);
    const QString getTagTitleById(int tagId);
    const int getTagMarkTypeById(int tagId);

    void updateCategoryTitle(int categoryId, QString newTitle);
    void updateTagTitle(int categoryId, QString newTitle);

private:
    Database() = default;
    ~Database() = default;

    bool initTables();

    QSqlDatabase m_dataBase;

signals:
    void onConnectDb();
};

#endif // DATABASE_H
