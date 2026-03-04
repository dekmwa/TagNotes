#ifndef SELECTTAGSWIDGET_H
#define SELECTTAGSWIDGET_H

#include <QWidget>
#include "qflowlayout.h"
#include <QScrollArea>
#include <QHBoxLayout>
#include <QPushButton>
#include <QVBoxLayout>
#include "database.h"
#include <QInputDialog>
#include <QMessageBox>


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
    QHBoxLayout *categoriesAndAddButton;
    QPushButton *addCategory;

    QVector<QPushButton*> categoriesBtns;
    void clearDisplayedCategories();

    QVBoxLayout *categoriesAndTags;
    QPushButton *addTagButton;

    Database& database;

    QVector<QPushButton*> currentDisplayedTags;
    int currentSelectedCategoryId;

    void updateCategories();
    void updateTagsByCategoryId(int categoryId);
    void clearDisplayedTags();

    void addCategoryDialog();
    void addTagDialog();

signals:
    void onTagClicked(int tagId);
    void onCategoryClicked(int categoryId);
};

#endif // SELECTTAGSWIDGET_H
