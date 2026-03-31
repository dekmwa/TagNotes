#ifndef TAGSVIEWER_H
#define TAGSVIEWER_H

enum class WidgetMode {
    WITH_PLUS_BUTTON,
    CLEAR
};

#include <QWidget>
#include "qflowlayout.h"
#include <QPushButton>
#include <QMap>
#include "database.h"


class TagsViewer : public QWidget
{
    Q_OBJECT

public:
    explicit TagsViewer(QWidget *parent, WidgetMode mode);

    void addTag(int tagId);
    void removeTag(int tagId);
    void clearAll();
    QVector<int> getTagIds();
    void unlockAddButton();

private:
    Database& database;
    WidgetMode currentMode;
    QFlowLayout *m_mainLay;
    QMap<int, QPushButton*> m_tags;

    QPushButton *plusButton;
    void addPlusButton();

signals:
    void tagClicked(int tagId);
    void addTagClicked();
    void tagRemoved(int tagId);
    void plusButtonClicked();
};

#endif // TAGSVIEWER_H
