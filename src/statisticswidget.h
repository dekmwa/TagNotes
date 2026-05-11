#ifndef STATISTICSWIDGET_H
#define STATISTICSWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include "database.h"


class StatisticsWidget : public QWidget
{
    Q_OBJECT
public:
    explicit StatisticsWidget(QWidget *parent = nullptr);

    void updateStatistics();

private:
    Database& database;

    QVBoxLayout* mLay;

    QLabel* tagsAndCategoriesCount;
    QLabel* totalTagsUsed;
    QLabel* mostPopularTag;

    void unitUi();
    QString pluralForm(int number,
                        const QString &form1, const QString &form2,
                        const QString &form5);

signals:
};

#endif // STATISTICSWIDGET_H
