#include "selecttagswidget.h"

SelectTagsWidget::SelectTagsWidget(QWidget *parent) : QWidget{parent},
    categories(new QScrollArea(this)), categoriesWidget(new QWidget()), categoriesLayout(new QHBoxLayout()),
    categoriesAndAddButton(new QHBoxLayout()), addCategory(new QPushButton("+")),
    categoriesAndTags(new QVBoxLayout()), addTagButton(new QPushButton("+")),
    tagsByCategory(new QFlowLayout()),
    database(Database::instance())
{
    //database.connectDatabase();

    categories->setWidgetResizable(true);
    categories->setFixedHeight(60);

    addTagButton->setFixedWidth(25);
    addTagButton->setDisabled(true);
    currentDisplayedTags.append(addTagButton);
    tagsByCategory->addWidget(addTagButton);
    connect(addTagButton, &QPushButton::clicked, this, [this](){
        addTagDialog();
    });

    addCategory->setFixedWidth(25);
    connect(addCategory, &QPushButton::clicked, this, [this](){
        addCategoryDialog();
    });

    categoriesWidget->setLayout(categoriesLayout);
    categories->setWidget(categoriesWidget);

    categoriesAndAddButton->addWidget(categories, 1);
    categoriesAndAddButton->addWidget(addCategory, 0);

    categoriesAndTags->addLayout(categoriesAndAddButton, 0);
    categoriesAndTags->addLayout(tagsByCategory, 1);

    updateCategories();

    connect(this, &SelectTagsWidget::onCategoryClicked, this, [this](int categoryId){
        updateTagsByCategoryId(categoryId);
    });

    setLayout(categoriesAndTags);
}

void SelectTagsWidget::updateCategories() {
    clearDisplayedCategories();

    QMap<int, QString> categories = database.getAllCategories();

    for (const auto& categoryId : categories.keys()) {
        QPushButton *categoryButton = new QPushButton(categories[categoryId], categoriesWidget);
        categoriesBtns.append(categoryButton);
        connect(categoryButton, &QPushButton::clicked, this, [this, categoryId](){
            emit onCategoryClicked(categoryId);
        });

        categoriesLayout->addWidget(categoryButton);
    }
}

void SelectTagsWidget::updateTagsByCategoryId(int categoryId) {
    clearDisplayedTags();
    currentSelectedCategoryId = categoryId;
    addTagButton->setDisabled(false);

    QMap<int, QString> tags = database.getTagsByCategoryId(categoryId);

    for (const auto& tagId : tags.keys()) {
        QPushButton *tag = new QPushButton(tags[tagId]);
        connect(tag, &QPushButton::clicked, this, [this, tagId](){
            emit onTagClicked(tagId);
        });
        currentDisplayedTags.append(tag);
        tagsByCategory->addWidget(tag);
    }
}

void SelectTagsWidget::updateTagsByCurrentCategory() {
    updateTagsByCategoryId(currentSelectedCategoryId);
}

void SelectTagsWidget::clearDisplayedTags() {
    for (QPushButton* tag : currentDisplayedTags) {
        if (tag == addTagButton) {
            continue;
        }
        tagsByCategory->removeWidget(tag);
        delete tag;
    }
    currentDisplayedTags.erase(currentDisplayedTags.begin() + 1, currentDisplayedTags.end());
}

void SelectTagsWidget::clearDisplayedCategories() {
    for (const auto& category : categoriesBtns) {
        categoriesLayout->removeWidget(category);
        delete category;
    }
    categoriesBtns.clear();
}

void SelectTagsWidget::addCategoryDialog() {
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
            updateCategories();
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

void SelectTagsWidget::addTagDialog() {
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
