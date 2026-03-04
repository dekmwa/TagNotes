#ifndef TAGSBYDATEWIDGET_H
#define TAGSBYDATEWIDGET_H

#include <QWidget>
#include "qflowlayout.h"
#include <QDate>
#include "database.h"
#include <QPushButton>


class TagsByDateWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TagsByDateWidget(QWidget *parent = nullptr);

    void updateTagsByDate(QDate date);
    void addTagToSelected(int tagId);
    void saveTags(QDate date);

private:
    QFlowLayout *tagsByDate;
    QVector<QPushButton*> displayedTagsBtns;
    QVector<int> displayedTagsIds;

    void clearDisplayedTags();

    Database& database;
};

#endif // TAGSBYDATEWIDGET_H
