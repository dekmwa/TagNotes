#include "statisticswidget.h"

StatisticsWidget::StatisticsWidget(QWidget *parent) : QWidget{parent},
    database(Database::instance())
{
    setObjectName("StatisticsWidget");
    unitUi();
    updateStatistics();
}

void StatisticsWidget::unitUi() {
    mLay = new QVBoxLayout(this);
    QHBoxLayout* header = new QHBoxLayout();
    QHBoxLayout* statistics = new QHBoxLayout();

    // header->addStretch();
    // QLabel* title = new QLabel();
    // title->setText("Статистика");
    // header->addWidget(title);
    // header->addStretch();
    // mLay->addLayout(header);

    tagsAndCategoriesCount = new QLabel();
    totalTagsUsed = new QLabel();
    mostPopularTag = new QLabel();
    statistics->addStretch();
    statistics->addWidget(tagsAndCategoriesCount);
    statistics->addStretch();
    statistics->addWidget(totalTagsUsed);
    statistics->addStretch();
    statistics->addWidget(mostPopularTag);
    statistics->addStretch();
    mLay->addLayout(statistics);
}

QString StatisticsWidget::pluralForm(int number, const QString &form1, const QString &form2, const QString &form5) {
    // form1 – 1 тег, form2 – 2-4 тега, form5 – 5+ тегов
    int n = number % 100;
    if (n >= 11 && n <= 19)
        return form5;
    n = number % 10;
    if (n == 1)
        return form1;
    if (n >= 2 && n <= 4)
        return form2;
    return form5;
}

void StatisticsWidget::updateStatistics() {
    StatisticsDTO stats = database.getStatistics();

    tagsAndCategoriesCount->setText(
        QString("Всего создано\n%1 %2 и %3 %4")
            .arg(stats.totalTags)
            .arg(pluralForm(stats.totalTags, "тег", "тега", "тегов"))
            .arg(stats.totalCategories)
            .arg(pluralForm(stats.totalCategories, "категория", "категории", "категорий"))
        );

    totalTagsUsed->setText(
        QString("Всего отмечено\n%1 %2 в %3 %4")
            .arg(stats.totalTagsUsed)
            .arg(pluralForm(stats.totalTagsUsed, "тег", "тега", "тегов"))
            .arg(stats.totalDaysUsed)
            .arg(pluralForm(stats.totalDaysUsed, "день", "дня", "дней"))
        );

    mostPopularTag->setText(
        QString("Самый популярный тег\n%1 который отмечен %2 %3")
            .arg(stats.mostPopularTag.isEmpty() ? "-" : stats.mostPopularTag)
            .arg(stats.mostPopularTagCount)
            .arg(pluralForm(stats.mostPopularTagCount, "раз", "раза", "раз"))
        );
}
