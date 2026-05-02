#ifndef TAGSBYDATEWIDGET2_H
#define TAGSBYDATEWIDGET2_H

#include <QWidget>
#include "tagsviewer.h"
#include <QHBoxLayout>


class TagsByDateWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TagsByDateWidget(QWidget *parent = nullptr);

    void updateTagsByDate(QDate date);
    void addTagToSelected(QMap<int, MarkValue> tagAndValue);
    void saveTags(QDate date);

private:
    QHBoxLayout *m_mainLay;
    TagsViewer *m_tagsViewer;
    QMap<int, MarkValue> m_tagsAndValues;
    void clearDisplayedTags();

    Database& m_database;

private slots:
    void onTagClicked(int tagId);

signals:
};

#endif // TAGSBYDATEWIDGET2_H
