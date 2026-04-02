#ifndef DELETETAGSORCATEGORIESWIDGET_H
#define DELETETAGSORCATEGORIESWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QMessageBox>
#include "database.h"
#include "categoriesviewer.h"
#include "categoriesandtagswidget.h"


class DeleteTagsOrCategoriesWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DeleteTagsOrCategoriesWidget(QWidget *parent = nullptr);

    void onBecomeActive();

private:
    Database& database;

    QVBoxLayout *mainLay;

    QLabel *widgetTite;
    QPushButton *backToMenu;
    QHBoxLayout *navigation;
    CategoriesViewer *categoriesViewer;
    CategoriesAndTagsWidget *categoriesAndTagsWidget;

    void categoryActionDialog(int categoryId);
    void tagActionDialog(int tagId);
    void deleteCategoryDialog(int categoryId);
    void deleteTagDialog(int tagId);

    void setupNavigation();
    void setupChangeCategories();
    void setupChangeTags();

signals:
    void onBackToMenu();
};

#endif // DELETETAGSORCATEGORIESWIDGET_H
