#include "deletetagsorcategorieswidget.h"

DeleteTagsOrCategoriesWidget::DeleteTagsOrCategoriesWidget(QWidget *parent) : QWidget{parent},
    mainLay(new QVBoxLayout()),
    database(Database::instance())//,
    //categoriesViewer(new CategoriesViewer(this))
{
    setAttribute(Qt::WA_StyledBackground, true);
    setObjectName("DeleteTagsOrCategoriesWidget");

    setupNavigation();
    setupChangeCategories();
    setupChangeTags();

    mainLay->setContentsMargins(20, 20, 20, 20);
    setLayout(mainLay);
}

void DeleteTagsOrCategoriesWidget::setupNavigation() {
    widgetTite = new QLabel();
    widgetTite->setText("Редактирование Категорий и Тегов");
    widgetTite->setAlignment(Qt::AlignCenter);
    widgetTite->setProperty("type", "text");

    backToMenu = new QPushButton();
    backToMenu->setText("Меню");
    backToMenu->setObjectName("backToMenuButton");
    connect(backToMenu, &QPushButton::clicked, this, [this](){
        emit onBackToMenu();
    });

    navigation = new QHBoxLayout();
    navigation->addWidget(backToMenu, 0);
    navigation->addWidget(widgetTite, 1);

    mainLay->addLayout(navigation, 0);
}

void DeleteTagsOrCategoriesWidget::setupChangeCategories() {
    QVBoxLayout *lay = new QVBoxLayout();

    QLabel *text = new QLabel();
    text->setText("Удалить или редактировать категорию");
    text->setAlignment(Qt::AlignCenter);
    text->setProperty("type", "text");

    categoriesViewer = new CategoriesViewer();

    lay->addWidget(text, 1);
    lay->addWidget(categoriesViewer, 1);

    connect(categoriesViewer, &CategoriesViewer::categoryClicked, this, [this](int categoryId){
        categoryActionDialog(categoryId);
    });

    mainLay->addLayout(lay, 1);
}

void DeleteTagsOrCategoriesWidget::setupChangeTags() {
    QVBoxLayout *lay = new QVBoxLayout();

    QLabel *text = new QLabel();
    text->setText("Удалить или редактировать тег");
    text->setAlignment(Qt::AlignCenter);
    text->setProperty("type", "text");

    categoriesAndTagsWidget = new CategoriesAndTagsWidget(this, Mode::VIEW_ONLY);

    lay->addWidget(text, 1);
    lay->addWidget(categoriesAndTagsWidget, 1);

    connect(categoriesAndTagsWidget, &CategoriesAndTagsWidget::onTagClicked, this, [this](int tagId){
        tagActionDialog(tagId);
    });

    mainLay->addLayout(lay, 1);
}

void DeleteTagsOrCategoriesWidget::categoryActionDialog(int categoryId) {
    QMessageBox msgBox(QMessageBox::Question,
                       "Редактирование категорий",
                       "Что вы хотите сделать с этой категорией?",
                       QMessageBox::NoButton,
                       this);

    QPushButton *deleteButton = msgBox.addButton("Удалить", QMessageBox::YesRole);
    QPushButton *changeButton = msgBox.addButton("Редактировать", QMessageBox::YesRole);
    QPushButton *cancelButton = msgBox.addButton("Отмена", QMessageBox::RejectRole);

    msgBox.exec();

    if (msgBox.clickedButton() == deleteButton) {
        deleteCategoryDialog(categoryId);
    } else if (msgBox.clickedButton() == changeButton) {
        updateCategoryDialog(categoryId);
    }
}

void DeleteTagsOrCategoriesWidget::tagActionDialog(int tagId) {
    QMessageBox msgBox(QMessageBox::Question,
                       "Редактирование тегов",
                       "Что вы хотите сделать с этим тегом?",
                       QMessageBox::NoButton,
                       this);

    QPushButton *deleteButton = msgBox.addButton("Удалить", QMessageBox::YesRole);
    QPushButton *changeButton = msgBox.addButton("Редактировать", QMessageBox::YesRole);
    QPushButton *cancelButton = msgBox.addButton("Отмена", QMessageBox::RejectRole);

    msgBox.exec();

    if (msgBox.clickedButton() == deleteButton) {
        deleteTagDialog(tagId);
    } else if (msgBox.clickedButton() == changeButton) {
        updateTagDialog(tagId);
    }
}

void DeleteTagsOrCategoriesWidget::deleteCategoryDialog(int categoryId) {
    QMessageBox msgBox(QMessageBox::Question,
                       "Удаление категории",
                       "Вы действительно хотите удалить эту категорию?",
                       QMessageBox::NoButton,
                       this);

    QPushButton *deleteButton = msgBox.addButton("Да", QMessageBox::YesRole);
    QPushButton *cancelButton = msgBox.addButton("Нет", QMessageBox::RejectRole);

    msgBox.exec();

    if (msgBox.clickedButton() == deleteButton) {
        database.deleteEmptyCategory(categoryId);
        categoriesViewer->updateCategories();
        categoriesAndTagsWidget->refresh();
        qDebug() << "oid DeleteTagsOrCategoriesWidget::deleteCategoryDialog " << categoryId;
    } else if (msgBox.clickedButton() == cancelButton) {
    }
}

void DeleteTagsOrCategoriesWidget::deleteTagDialog(int tagId) {
    QMessageBox msgBox(QMessageBox::Question,
                       "Удаление тега",
                       "Вы действительно хотите удалить этот тег?",
                       QMessageBox::NoButton,
                       this);

    QPushButton *deleteButton = msgBox.addButton("Да", QMessageBox::YesRole);
    QPushButton *cancelButton = msgBox.addButton("Нет", QMessageBox::RejectRole);

    msgBox.exec();

    if (msgBox.clickedButton() == deleteButton) {
        database.deleteTag(tagId);
        categoriesAndTagsWidget->refresh();
    } else if (msgBox.clickedButton() == cancelButton) {
    }
}

void DeleteTagsOrCategoriesWidget::updateCategoryDialog(int categoryId) {
    bool ok;
    QString title = QInputDialog::getText(
        this,
        "Обновление категории",
        "Введите новое название категории:",
        QLineEdit::Normal,
        "",
        &ok
        );

    if (ok && !title.isEmpty()) {
        database.updateCategoryTitle(categoryId, title);
        categoriesViewer->updateCategories();
        categoriesAndTagsWidget->refresh();
    }
}

void DeleteTagsOrCategoriesWidget::updateTagDialog(int categoryId) {
    bool ok;
    QString title = QInputDialog::getText(
        this,
        "Обновление тега",
        "Введите новое название тега:",
        QLineEdit::Normal,
        "",
        &ok
        );

    if (ok && !title.isEmpty()) {
        database.updateTagTitle(categoryId, title);
        categoriesViewer->updateCategories();
        categoriesAndTagsWidget->refresh();
    }
}

void DeleteTagsOrCategoriesWidget::onBecomeActive() {
    categoriesViewer->updateCategories();
    categoriesAndTagsWidget->refresh();
}
