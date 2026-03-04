#include "deletetagsorcategorieswidget.h"

DeleteTagsOrCategoriesWidget::DeleteTagsOrCategoriesWidget(QWidget *parent) : QWidget{parent},
    mainLay(new QVBoxLayout())
{
    setupNavigation();
    setupTagsAndCategories();

    mainLay->addLayout(navigation, 0);
    mainLay->addWidget(selectTagsWidget, 1);

    setLayout(mainLay);
}

void DeleteTagsOrCategoriesWidget::setupNavigation() {
    widgetTite = new QLabel();
    widgetTite->setText("Удаление Категорий и тегов");

    backToMenu = new QPushButton();
    backToMenu->setText("Меню");
    connect(backToMenu, &QPushButton::clicked, this, [this](){
        emit onBackToMenu();
    });

    navigation = new QHBoxLayout();
    navigation->addWidget(backToMenu, 0);
    navigation->addWidget(widgetTite, 1);
}

void DeleteTagsOrCategoriesWidget::setupTagsAndCategories() {
    selectTagsWidget = new SelectTagsWidget();

    // connect(selectTagsWidget, &SelectTagsWidget::onCategoryClicked, this)
}
