#include "noteswidget.h"


NotesWidget::NotesWidget(QWidget *parent) : QWidget{parent}, calendar(new CustomCalendar()),
    calendarAndSelectedTags(new QHBoxLayout()), selectedTagsLay(new QVBoxLayout()),
    selectedDay(new QLabel(this)), selectedTags(new TagsByDateWidget2()), saveDay(new QPushButton("Сохранить", this)),
    mainLay(new QVBoxLayout()),
    categoriesAndTagsWidget(new CategoriesAndTagsWidget(this, Mode::ADD_TAGS_AND_ADD_CATEGORIES))
{
    setAttribute(Qt::WA_StyledBackground, true);
    setObjectName("NotesWidget");

    selectedDay->setAlignment(Qt::AlignCenter);
    selectedDay->setProperty("type", "text");
    selectedTagsLay->addWidget(selectedDay, 0);

    selectedTagsLay->addWidget(selectedTags, 1);

    selectedTagsLay->addWidget(saveDay, 0);
    selectedTagsLay->setContentsMargins(20, 0, 10, 0);

    saveDay->setObjectName("saveDayButton");

    calendarAndSelectedTags->addWidget(calendar, 4);

    calendarAndSelectedTags->addLayout(selectedTagsLay, 6);

    setupNavigation();

    mainLay->addLayout(navigation, 0);
    mainLay->addLayout(calendarAndSelectedTags, 1);
    mainLay->addWidget(categoriesAndTagsWidget, 1);

    connect(calendar, &CustomCalendar::onDayClicked, this, [this](QDate date){
        selectedDay->setText("Теги по дате: " + date.toString());
        selectedTags->updateTagsByDate(date);
    });

    connect(categoriesAndTagsWidget, &CategoriesAndTagsWidget::onTagClicked, this, [this](int tagId){
        selectedTags->addTagToSelected(tagId);
    });

    connect(saveDay, &QPushButton::clicked, [this](){
        selectedTags->saveTags(calendar->getSelectedDate());
    });

    selectedTags->updateTagsByDate(QDate::currentDate());

    mainLay->setContentsMargins(20, 20, 20, 20);
    setLayout(mainLay);
}

void NotesWidget::setupNavigation() {
    widgetTite = new QLabel();
    widgetTite->setText("Создание заметок");
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
}

void NotesWidget::onBecomeActive() {
    categoriesAndTagsWidget->refresh();
    selectedTags->updateTagsByDate(QDate::currentDate());
}
