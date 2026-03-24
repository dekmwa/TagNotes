#ifndef TAGSVIEWER_H
#define TAGSVIEWER_H

#include <QWidget>
#include "qflowlayout.h"
#include <QPushButton>
#include <QMap>
#include "database.h"


class TagsViewer : public QWidget
{
    Q_OBJECT

public:
    explicit TagsViewer(QWidget *parent = nullptr);

    void addTag(int tagId);
    void removeTag(int tagId);
    void clearAll();
    QVector<int> getTagIds();

private:
    Database& database;
    QFlowLayout *m_mainLay;
    QMap<int, QPushButton*> m_tags;

signals:
    void tagClicked(int tagId);
    void tagRemoved(int tagId);
};

#endif // TAGSVIEWER_H
