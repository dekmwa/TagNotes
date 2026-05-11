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
    connect(tagsViewer, &TagsViewer::onTagClicked, this, [this](int tagId){
        emit onTagClicked(tagId);
    });
    connect(tagsViewer, &TagsViewer::addTagClicked, this, &CategoriesAndTagsWidget::addTagDialog);

    setupWidget();
    refresh();
}

void CategoriesAndTagsWidget::setupWidget() {
    QHBoxLayout *categoriesAndPlus = new QHBoxLayout();

    searchBtn = new QPushButton();
    searchBtn->setIcon(QIcon(":/icons/search.svg"));
    searchBtn->setFixedSize(42, 42);
    searchBtn->setIconSize(QSize(32, 32));
    searchBtn->setProperty("type", "filter");
    connect(searchBtn, &QPushButton::clicked, this, &CategoriesAndTagsWidget::setFilterDialog);

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
    categoriesAndPlus->addWidget(searchBtn);
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
        if (!currentFilter.trimmed().isEmpty() &&
            !tags[tagId].toLower().contains(currentFilter.trimmed().toLower())) {
            continue;
        }

        QMap<int, QString> tagAndTitle;
        QString markTypeForTitle = "";

        switch (database.getTagMarkTypeById(tagId)) {
        case MarkType::WITHOUT:
            markTypeForTitle = "";
            break;
        case MarkType::NUMBER:
            markTypeForTitle = " <число>";
            break;
        }

        tagAndTitle.insert(tagId, tags[tagId] + markTypeForTitle);
        tagsViewer->addTag(tagAndTitle);
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
    QDialog dialog(this);
    dialog.setWindowTitle("Создание тега");
    dialog.setModal(true);

    QFormLayout *form = new QFormLayout(&dialog);

    QLineEdit *nameEdit = new QLineEdit();
    nameEdit->setPlaceholderText("Отжимания");
    form->addRow("Название:", nameEdit);

    QComboBox *typeCombo = new QComboBox();
    typeCombo->addItems({"Без значения", "Число"});
    form->addRow("Тип:", typeCombo);

    QDialogButtonBox *buttons = new QDialogButtonBox(
        QDialogButtonBox::Ok | QDialogButtonBox::Cancel
        );
    form->addRow(buttons);

    connect(buttons, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
    connect(buttons, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);

    if (dialog.exec() == QDialog::Accepted && !nameEdit->text().isEmpty()) {
        MarkType markType = static_cast<MarkType>(typeCombo->currentIndex());

        if (database.addTag(nameEdit->text(), currentSelectedCategoryId, markType)) {
            updateTagsByCategoryId(currentSelectedCategoryId);
        }
    }
}

void CategoriesAndTagsWidget::setFilterDialog() {
    if (!currentFilter.isEmpty()) {
        currentFilter = "";
        searchBtn->setIcon(QIcon(":/icons/search.svg"));
        updateTagsByCategoryId(currentSelectedCategoryId);
        return;
    }

    bool ok;
    QString filter = QInputDialog::getText(
        this,
        "Фильтр по названию",
        "Введите название/часть названия тега",
        QLineEdit::Normal,
        "",
        &ok
        );

    if (ok && !filter.isEmpty()) {
        currentFilter = filter;
        searchBtn->setIcon(QIcon(":/icons/search_off.svg"));
        updateTagsByCategoryId(currentSelectedCategoryId);
    }
}
