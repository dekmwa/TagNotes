#ifndef SELECTTAGSWIDGET_H
#define SELECTTAGSWIDGET_H

#include <QWidget>
#include "qflowlayout.h"
#include <QScrollArea>
#include <QHBoxLayout>
#include <QPushButton>
#include <QVBoxLayout>
#include "database.h"


class SelectTagsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SelectTagsWidget(QWidget *parent = nullptr);

private:
    QFlowLayout *tagsByCategory;

    QScrollArea *categories;
    QWidget *categoriesWidget;
    QHBoxLayout *categoriesLayout;

    QVBoxLayout *categoriesAndTags;

    Database& database;

signals:
    void onTagClicked(int tagId);
};

#endif // SELECTTAGSWIDGET_H
