#include "categoriesandtagswidget.h"

CategoriesAndTagsWidget::CategoriesAndTagsWidget(QWidget *parent, Mode mode) : QWidget{parent},
    database(Database::instance()),
    currentMode(mode),
    mainLay(new QVBoxLayout(this)),
    tagsViewer(new TagsViewer(this)),
    categoriesViewer(new CategoriesViewer(this))
{
    setAttribute(Qt::WA_StyledBackground, true);
    setObjectName("CategoriesAndTagsWidget");

    connect(categoriesViewer, &CategoriesViewer::categoryClicked, [this](int categoryId){
        currentSelectedCategoryId = categoryId;
        updateTagsByCategoryId(categoryId);
        tagsViewer->unlockAddButton();
    });
    connect(tagsViewer, &TagsViewer::tagClicked, this, [this](int tagId){
        emit onTagClicked(tagId);
    });
    connect(tagsViewer, &TagsViewer::addTagClicked, this, &CategoriesAndTagsWidget::addTagDialog);

    setupWidget();
    refresh();
}

void CategoriesAndTagsWidget::setupWidget() {
    QHBoxLayout *categoriesAndPlus = new QHBoxLayout();

    QPushButton *addCategory = new QPushButton(this);
    connect(addCategory, &QPushButton::clicked, this, &CategoriesAndTagsWidget::addCategoryDialog);
    addCategory->setText("+");
    addCategory->setFixedWidth(25);
    addCategory->setProperty("type", "addCategory");

    if (currentMode == Mode::VIEW_ONLY) {
        addCategory->hide();
    } else if (currentMode == Mode::ADD_TAGS_AND_ADD_CATEGORIES) {
        addCategory->show();
        tagsViewer->showAddTagButton();
    }

    categoriesAndPlus->addWidget(categoriesViewer);
    categoriesAndPlus->addWidget(addCategory);

    mainLay->addLayout(categoriesAndPlus, 0);
    mainLay->addWidget(tagsViewer, 1);

    setLayout(mainLay);
}

void CategoriesAndTagsWidget::refresh() {
    categoriesViewer->updateCategories();
    updateTagsByCategoryId(currentSelectedCategoryId);
}

void CategoriesAndTagsWidget::updateTagsByCategoryId(int categoryId) {
    tagsViewer->clearAll();
    currentSelectedCategoryId = categoryId;

    QMap<int, QString> tags = database.getTagsByCategoryId(categoryId);

    for (const auto& tagId : tags.keys()) {
        tagsViewer->addTag(tagId);
    }
}

void CategoriesAndTagsWidget::updateTagsByCurrentCategory() {
    updateTagsByCategoryId(currentSelectedCategoryId);
}

void CategoriesAndTagsWidget::addCategoryDialog() {
    bool ok;
    QString title = QInputDialog::getText(
        this,
        "Добавление категории",
        "Название категории",
        QLineEdit::Normal,
        "",
        &ok
        );

    if (ok && !title.isEmpty()) {
        if (database.addCategory(title)) {
            categoriesViewer->updateCategories();
            QMessageBox success;
            success.setText("Категория добавлена");
            success.exec();
        } else {
            QMessageBox error;
            error.setText("Ошибка добавления категории");
            error.setIcon(QMessageBox::Warning);
            error.exec();
        }
    }
}

void CategoriesAndTagsWidget::addTagDialog() {
    bool ok;
    QString title = QInputDialog::getText(
        this,
        "Добавление тега",
        "Что хотите отмечать?",
        QLineEdit::Normal,
        "",
        &ok
        );

    if (ok && !title.isEmpty()) {
        if (database.addTag(title, currentSelectedCategoryId)) {
            updateTagsByCategoryId(currentSelectedCategoryId);
            QMessageBox success;
            success.setText("Тег добавлен");
            success.exec();
        } else {
            QMessageBox error;
            error.setText("Ошибка добавления тега");
            error.setIcon(QMessageBox::Warning);
            error.exec();
        }
    }
}
