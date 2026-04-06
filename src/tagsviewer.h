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
    explicit TagsViewer(QWidget *parent);

    void addTag(int tagId);
    void removeTag(int tagId);
    void clearAll();
    QVector<int> getTagIds();
    void unlockAddButton();
    void lockAddButton();
    void showAddTagButton();

private:
    Database& database;
    QFlowLayout *m_mainLay;
    QMap<int, QPushButton*> m_tags;

    QPushButton *plusButton;
    void setupAddTagButton();

signals:
    void tagClicked(int tagId);
    void addTagClicked();
    void tagRemoved(int tagId);
    void plusButtonClicked();
};

#endif // TAGSVIEWER_H
