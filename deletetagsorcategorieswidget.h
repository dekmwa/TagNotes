#ifndef DELETETAGSORCATEGORIESWIDGET_H
#define DELETETAGSORCATEGORIESWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include "selecttagswidget.h"
#include "database.h"


class DeleteTagsOrCategoriesWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DeleteTagsOrCategoriesWidget(QWidget *parent = nullptr);

private:
    Database& database;

    QVBoxLayout *mainLay;

    QLabel *widgetTite;
    QPushButton *backToMenu;
    QHBoxLayout *navigation;

    SelectTagsWidget *selectTagsWidget;

    void deleteCategoryDialog(int categoryId);
    // void deleteTagDialog();

    void setupNavigation();
    void setupTagsAndCategories();

signals:
    void onBackToMenu();
};

#endif // DELETETAGSORCATEGORIESWIDGET_H
