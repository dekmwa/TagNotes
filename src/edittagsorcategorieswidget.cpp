#include "edittagsorcategorieswidget.h"

EditTagsOrCategoriesWidget::EditTagsOrCategoriesWidget(QWidget *parent) : QWidget{parent},
    mainLay(new QVBoxLayout()),
    database(Database::instance())//,
    //categoriesViewer(new CategoriesViewer(this))
{
    setAttribute(Qt::WA_StyledBackground, true);
    setObjectName("DeleteTagsOrCategoriesWidget");

    setupNavigation();
    mainLay->addStretch();
    setupChangeCategories();
    mainLay->addStretch();
    setupChangeTags();
    mainLay->addStretch();

    mainLay->setContentsMargins(20, 20, 20, 20);
    setLayout(mainLay);
}

void EditTagsOrCategoriesWidget::setupNavigation() {
    widgetTitle = new QLabel();
    widgetTitle->setText("Редактирование Категорий и Тегов");
    widgetTitle->setAlignment(Qt::AlignCenter);
    widgetTitle->setProperty("type", "widgetTitle");

    backToMenu = new QPushButton();
    backToMenu->setText("Меню");
    backToMenu->setObjectName("backToMenuButton");
    connect(backToMenu, &QPushButton::clicked, this, [this](){
        emit onBackToMenu();
    });

    navigation = new QHBoxLayout();
    navigation->addWidget(backToMenu, 0);
    navigation->addWidget(widgetTitle, 1);

    mainLay->addLayout(navigation);
}

void EditTagsOrCategoriesWidget::setupChangeCategories() {
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

    mainLay->addLayout(lay);
}

void EditTagsOrCategoriesWidget::setupChangeTags() {
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

    mainLay->addLayout(lay);
}

void EditTagsOrCategoriesWidget::categoryActionDialog(int categoryId) {
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

void EditTagsOrCategoriesWidget::tagActionDialog(int tagId) {
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

void EditTagsOrCategoriesWidget::deleteCategoryDialog(int categoryId) {
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

void EditTagsOrCategoriesWidget::deleteTagDialog(int tagId) {
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

void EditTagsOrCategoriesWidget::updateCategoryDialog(int categoryId) {
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

void EditTagsOrCategoriesWidget::updateTagDialog(int categoryId) {
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

void EditTagsOrCategoriesWidget::onBecomeActive() {
    categoriesViewer->updateCategories();
    categoriesAndTagsWidget->refresh();
}
