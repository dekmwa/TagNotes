#include "categoriesandtagswidget.h"

CategoriesAndTagsWidget::CategoriesAndTagsWidget(QWidget *parent, Mode mode) : QWidget{parent},
    database(Database::instance()),
    currentMode(mode),
    mainLay(new QVBoxLayout(this)),
    tagsViewer(new TagsViewer(this, WidgetMode::WITH_PLUS_BUTTON)),
    categoriesViewer(new CategoriesViewer(this))//,
    //addTagButton(new QPushButton(this))
{
    connect(categoriesViewer, &CategoriesViewer::categoryClicked, [this](int categoryId){
        updateTagsByCategoryId(categoryId);
    });
    connect(tagsViewer, &TagsViewer::tagClicked, this, [this](int tagId){
        emit onTagClicked(tagId);
    });

    setupWidget();
    refresh();
}

void CategoriesAndTagsWidget::setupWidget() {
    QHBoxLayout *categoriesAndPlus = new QHBoxLayout();
    QPushButton *addCategory = new QPushButton(this);
    addCategory->setText("+");
    addCategory->setFixedWidth(20);
    if (currentMode == Mode::VIEW_ONLY) addCategory->hide();

    categoriesAndPlus->addWidget(categoriesViewer);
    categoriesAndPlus->addWidget(addCategory);

    mainLay->addLayout(categoriesAndPlus);

    QHBoxLayout *tagsAndPlus = new QHBoxLayout();
    //if (currentMode == Mode::VIEW_ONLY) addTagButton->hide();

    tagsAndPlus->addWidget(tagsViewer);
    //tagsAndPlus->addWidget(addTagButton);

    mainLay->addLayout(tagsAndPlus);
    setLayout(mainLay);
}

void CategoriesAndTagsWidget::refresh() {
    categoriesViewer->updateCategories();
}

void CategoriesAndTagsWidget::updateTagsByCategoryId(int categoryId) {
    tagsViewer->clearAll();
    currentSelectedCategoryId = categoryId;
    //addTagButton->setDisabled(false);

    QMap<int, QString> tags = database.getTagsByCategoryId(categoryId);

    for (const auto& tagId : tags.keys()) {
        tagsViewer->addTag(tagId);
    }

    tagsViewer->unlockAddButton();
}

void CategoriesAndTagsWidget::updateTagsByCurrentCategory() {
    updateTagsByCategoryId(currentSelectedCategoryId);
}
