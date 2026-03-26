#include "categoriesviewer.h"

CategoriesViewer::CategoriesViewer(QWidget *parent) : QWidget{parent},
    database(Database::instance())
{
    setupCategoriesArea();
    updateCategories();
}

void CategoriesViewer::setupCategoriesArea() {
    m_lay = new QHBoxLayout();
    categoriesSrcAr = new QScrollArea();
    categoriesWidget = new QWidget();
    categoriesLayout = new QHBoxLayout();

    categoriesWidget->setLayout(categoriesLayout);
    categoriesSrcAr->setWidget(categoriesWidget);
    m_lay->addWidget(categoriesSrcAr);
    setLayout(m_lay);
}

void CategoriesViewer::updateCategories() {
    clearDisplayedCategories();

    QMap<int, QString> categories = database.getAllCategories();

    for (const auto& categoryId : categories.keys()) {
        QPushButton *categoryButton = new QPushButton(categories[categoryId], categoriesWidget);
        m_categories.insert(categoryId, categoryButton);
        connect(categoryButton, &QPushButton::clicked, this, [this, categoryId](){
            emit categoryClicked(categoryId);
        });

        categoriesLayout->addWidget(categoryButton);
    }
}

void CategoriesViewer::clearDisplayedCategories() {
    for (const auto& category : m_categories.values()) {
        categoriesLayout->removeWidget(category);
        delete category;
    }
    m_categories.clear();
}
