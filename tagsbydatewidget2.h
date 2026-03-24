#ifndef TAGSBYDATEWIDGET2_H
#define TAGSBYDATEWIDGET2_H

#include <QWidget>
#include "tagsviewer.h"


class TagsByDateWidget2 : public QWidget
{
    Q_OBJECT

public:
    explicit TagsByDateWidget2(QWidget *parent = nullptr);

    void updateTagsByDate(QDate date);
    void addTagToSelected(int tagId);
    void saveTags(QDate date);

private:
    TagsViewer *m_taskViewer;
    void clearDisplayedTags();

    Database& database;

signals:
};

#endif // TAGSBYDATEWIDGET2_H
