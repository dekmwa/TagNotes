#include "categoriesviewer.h"

CategoriesViewer::CategoriesViewer(QWidget *parent) : QWidget{parent},
    database(Database::instance()),
    m_lay(new QHBoxLayout(this))
{
    setAttribute(Qt::WA_StyledBackground, true);
    setObjectName("CategoriesViewer");

    setupCategoriesArea();
    updateCategories();
}

void CategoriesViewer::setupCategoriesArea() {
    categoriesSrcAr = new QScrollArea();
    categoriesWidget = new QWidget();
    categoriesLayout = new QHBoxLayout();

    categoriesSrcAr->setWidgetResizable(true);
    categoriesSrcAr->setFixedHeight(80);
    categoriesSrcAr->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    categoriesSrcAr->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

    categoriesWidget->setLayout(categoriesLayout);
    categoriesSrcAr->setWidget(categoriesWidget);
    m_lay->addWidget(categoriesSrcAr);
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
