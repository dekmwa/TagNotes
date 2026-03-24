#include "noteswidget.h"


NotesWidget::NotesWidget(QWidget *parent) : QWidget{parent}, calendar(new QCalendarWidget()),
    calendarAndSelectedTags(new QHBoxLayout()), selectedTagsLay(new QVBoxLayout()),
    selectedDay(new QLabel(this)), selectedTags(new TagsByDateWidget2()), saveDay(new QPushButton("Сохранить", this)),
    mainLay(new QVBoxLayout()),
    selectTagsWidget(new SelectTagsWidget())
{
    selectedTagsLay->addWidget(selectedDay, 0);
    selectedTagsLay->addWidget(selectedTags, 1);
    selectedTagsLay->addWidget(saveDay, 0);

    calendarAndSelectedTags->addWidget(calendar, 4);
    calendarAndSelectedTags->addLayout(selectedTagsLay, 6);

    setupNavigation();

    mainLay->addLayout(navigation, 0);
    mainLay->addLayout(calendarAndSelectedTags, 0);
    mainLay->addWidget(selectTagsWidget, 1);

    connect(calendar, &QCalendarWidget::clicked, this, [this](QDate date){
        selectedDay->setText("Теги по дате: " + date.toString());
        selectedTags->updateTagsByDate(date);
    });

    connect(selectTagsWidget, &SelectTagsWidget::onTagClicked, this, [this](int tagId){
        selectedTags->addTagToSelected(tagId);
    });

    connect(saveDay, &QPushButton::clicked, [this](){
        selectedTags->saveTags(calendar->selectedDate());
    });

    selectedTags->updateTagsByDate(QDate::currentDate());

    setLayout(mainLay);
}

void NotesWidget::setupNavigation() {
    widgetTite = new QLabel();
    widgetTite->setText("Создание заметок");

    backToMenu = new QPushButton();
    backToMenu->setText("Меню");
    connect(backToMenu, &QPushButton::clicked, this, [this](){
        emit onBackToMenu();
    });

    navigation = new QHBoxLayout();
    navigation->addWidget(backToMenu, 0);
    navigation->addWidget(widgetTite, 1);
}

void NotesWidget::onBecomeActive() {
    selectTagsWidget->updateCategories();
}
