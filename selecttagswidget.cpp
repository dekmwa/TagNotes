#include "selecttagswidget.h"

SelectTagsWidget::SelectTagsWidget(QWidget *parent) : QWidget{parent},
    categories(new QScrollArea(this)), categoriesWidget(new QWidget()), categoriesLayout(new QHBoxLayout()),
    categoriesAndTags(new QVBoxLayout()),
    tagsByCategory(new QFlowLayout()),
    database(Database::instance())
{
    database.connectDatabase();

    categories->setWidgetResizable(true);
    categories->setFixedHeight(60);

    categoriesWidget->setLayout(categoriesLayout);
    categories->setWidget(categoriesWidget);

    QPushButton *tag11 = new QPushButton("тег", this);
    QPushButton *tag21 = new QPushButton("rthreh", this);
    QPushButton *tag31 = new QPushButton("теhhhhhhhг", this);
    QPushButton *tag41 = new QPushButton("тhehег", this);
    QPushButton *tag51 = new QPushButton("тhrhrehег", this);

    categoriesLayout->addWidget(tag11);
    categoriesLayout->addWidget(tag21);
    categoriesLayout->addWidget(tag31);
    categoriesLayout->addWidget(tag41);
    categoriesLayout->addWidget(tag51);

    QPushButton *tag1 = new QPushButton("тег", this);
    QPushButton *tag2 = new QPushButton("rthreh", this);
    QPushButton *tag3 = new QPushButton("теhhhhhhhг", this);
    QPushButton *tag4 = new QPushButton("тhehег", this);
    QPushButton *tag5 = new QPushButton("тhrhrehег", this);

    tagsByCategory->addWidget(tag1);
    tagsByCategory->addWidget(tag2);
    tagsByCategory->addWidget(tag3);
    tagsByCategory->addWidget(tag4);
    tagsByCategory->addWidget(tag5);

    categoriesAndTags->addWidget(categories);
    categoriesAndTags->addLayout(tagsByCategory);

    setLayout(categoriesAndTags);
}
