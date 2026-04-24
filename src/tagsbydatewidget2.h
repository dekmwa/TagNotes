#ifndef TAGSBYDATEWIDGET2_H
#define TAGSBYDATEWIDGET2_H

#include <QWidget>
#include "tagsviewer.h"
#include <QHBoxLayout>


class TagsByDateWidget2 : public QWidget
{
    Q_OBJECT

public:
    explicit TagsByDateWidget2(QWidget *parent = nullptr);

    void updateTagsByDate(QDate date);
    void addTagToSelected(QMap<int, MarkValue> tagAndValue);
    void saveTags(QDate date);

private:
    QHBoxLayout *m_mainLay;
    TagsViewer *m_tagsViewer;
    void clearDisplayedTags();

    Database& database;

private slots:
    void onTagClicked(int tagId);

signals:
};

#endif // TAGSBYDATEWIDGET2_H
