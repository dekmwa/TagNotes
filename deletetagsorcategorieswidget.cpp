#include "deletetagsorcategorieswidget.h"

DeleteTagsOrCategoriesWidget::DeleteTagsOrCategoriesWidget(QWidget *parent) : QWidget{parent},
    mainLay(new QVBoxLayout()),
    database(Database::instance())
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

    connect(selectTagsWidget, &SelectTagsWidget::onCategoryClicked, this, [this](int categoryId){
        deleteCategoryDialog(categoryId);
    });
    connect(selectTagsWidget, &SelectTagsWidget::onTagClicked, this, [this](int tagId){
        deleteTagDialog(tagId);
    });
}

void DeleteTagsOrCategoriesWidget::deleteCategoryDialog(int categoryId) {
    QMessageBox msgBox(QMessageBox::Question,
                       "Удаление категории",
                       "Вы хотите удалить эту категорию?",
                       QMessageBox::NoButton,
                       this);

    QPushButton *deleteButton = msgBox.addButton("Да", QMessageBox::YesRole);
    QPushButton *cancelButton = msgBox.addButton("Нет", QMessageBox::RejectRole);

    msgBox.exec();

    if (msgBox.clickedButton() == deleteButton) {
        database.deleteEmptyCategory(categoryId);
        selectTagsWidget->updateCategories();
        qDebug() << "oid DeleteTagsOrCategoriesWidget::deleteCategoryDialog " << categoryId;
    } else if (msgBox.clickedButton() == cancelButton) {
    }
}

void DeleteTagsOrCategoriesWidget::deleteTagDialog(int tagId) {
    QMessageBox msgBox(QMessageBox::Question,
                       "Удаление тега",
                       "Вы хотите удалить этот тег?",
                       QMessageBox::NoButton,
                       this);

    QPushButton *deleteButton = msgBox.addButton("Да", QMessageBox::YesRole);
    QPushButton *cancelButton = msgBox.addButton("Нет", QMessageBox::RejectRole);

    msgBox.exec();

    if (msgBox.clickedButton() == deleteButton) {
        database.deleteTag(tagId);
        selectTagsWidget->updateTagsByCurrentCategory();
    } else if (msgBox.clickedButton() == cancelButton) {
    }
}

void DeleteTagsOrCategoriesWidget::onBecomeActive() {
    selectTagsWidget->updateCategories();
}
