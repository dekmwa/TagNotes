#ifndef CATEGORIESANDTAGSWIDGET_H
#define CATEGORIESANDTAGSWIDGET_H

enum class Mode {
    VIEW_ONLY,
    ADD_TAGS_AND_ADD_CATEGORIES
};

#include <QWidget>
#include <QVBoxLayout>
#include "tagsviewer.h"
#include "categoriesviewer.h"
#include "database.h"


class CategoriesAndTagsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CategoriesAndTagsWidget(QWidget *parent, Mode mode);
    void refresh();

private:
    Database& database;
    Mode currentMode;
    QVBoxLayout *mainLay;
    TagsViewer *tagsViewer;
    CategoriesViewer *categoriesViewer;
    int currentSelectedCategoryId;
    //QPushButton *addTagButton;

    void setupWidget();
    void updateTagsByCategoryId(int categoryId);
    void updateTagsByCurrentCategory();

signals:
    void onTagClicked(int tagId);
};

#endif // CATEGORIESANDTAGSWIDGET_H
