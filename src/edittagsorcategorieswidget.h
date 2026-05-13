#ifndef EDITTAGSORCATEGORIESWIDGET_H
#define EDITTAGSORCATEGORIESWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QMessageBox>
#include "database.h"
#include "categoriesviewer.h"
#include "categoriesandtagswidget.h"


class EditTagsOrCategoriesWidget : public QWidget
{
    Q_OBJECT
public:
    explicit EditTagsOrCategoriesWidget(QWidget *parent = nullptr);

    void onBecomeActive();

private:
    Database& database;

    QVBoxLayout *mainLay;

    QLabel *widgetTitle;
    QPushButton *backToMenu;
    QHBoxLayout *navigation;
    CategoriesViewer *categoriesViewer;
    CategoriesAndTagsWidget *categoriesAndTagsWidget;

    void categoryActionDialog(int categoryId);
    void tagActionDialog(int tagId);
    void deleteCategoryDialog(int categoryId);
    void deleteTagDialog(int tagId);

    void updateCategoryDialog(int categoryId);
    void updateTagDialog(int categoryId);

    void setupNavigation();
    void setupChangeCategories();
    void setupChangeTags();

signals:
    void onBackToMenu();
};

#endif // EDITTAGSORCATEGORIESWIDGET_H
