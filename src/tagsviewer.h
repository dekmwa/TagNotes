#ifndef TAGSVIEWER_H
#define TAGSVIEWER_H


#include <QWidget>
#include "qflowlayout.h"
#include <QPushButton>
#include <QMap>
#include <QScrollArea>
#include "database.h"


class TagsViewer : public QWidget
{
    Q_OBJECT

public:
    explicit TagsViewer(QWidget *parent);

    void addTag(QMap<int, QString> tagIdAndTitle);
    void removeTag(int tagId);
    void clearAll();
    void unlockAddButton();
    void lockAddButton();
    void showAddTagButton();

private:
    Database& database;
    QScrollArea *scrollArea;
    QVBoxLayout *m_mainLay;
    QFlowLayout *flowLay;
    QWidget *contentWidget;
    QMap<int, QPushButton*> m_tagsButtons;

    QPushButton *plusButton;
    void setupAddTagButton();

signals:
    void onTagClicked(int tagId);
    void addTagClicked();
    void tagRemoved(int tagId);
    void plusButtonClicked();
};

#endif // TAGSVIEWER_H
