#ifndef CATEGORIESVIEWER_H
#define CATEGORIESVIEWER_H

#include <QWidget>
#include <QScrollArea>
#include <QHBoxLayout>
#include <QPushButton>
#include "database.h"


class CategoriesViewer : public QWidget
{
    Q_OBJECT

public:
    explicit CategoriesViewer(QWidget *parent = nullptr);
    void updateCategories();

private:
    Database& database;
    QHBoxLayout *m_lay;
    QScrollArea *categoriesSrcAr;
    QWidget *categoriesWidget;
    QHBoxLayout *categoriesLayout;
    QMap<int, QPushButton*> m_categories;
    int selectedCategory;

    void clearDisplayedCategories();
    void setupCategoriesArea();

signals:
    void categoryClicked(int categoryId);
};

#endif // CATEGORIESVIEWER_H
