#include "noteswidget.h"

NotesWidget::NotesWidget(QWidget *parent) : QWidget{parent}, calendar(new QCalendarWidget()),
    calendarAndSelectedTags(new QHBoxLayout()), selectedTagsLay(new QVBoxLayout()),
    selectedDay(new QLabel(this)), selectedTags(new QFlowLayout()), saveDay(new QPushButton("Сохранить", this)),
    mainLay(new QVBoxLayout()),
    selectTagsWidget(new SelectTagsWidget())
{
    selectedTagsLay->addWidget(selectedDay, 0);
    selectedTagsLay->addLayout(selectedTags, 1);
    selectedTagsLay->addWidget(saveDay, 0);

    QPushButton *tag1 = new QPushButton("тег", this);
    QPushButton *tag2 = new QPushButton("rthreh", this);
    QPushButton *tag3 = new QPushButton("теhhhhhhhг", this);
    QPushButton *tag4 = new QPushButton("тhehег", this);
    QPushButton *tag5 = new QPushButton("тhrhrehег", this);

    selectedTags->addWidget(tag1);
    selectedTags->addWidget(tag2);
    selectedTags->addWidget(tag3);
    selectedTags->addWidget(tag4);
    selectedTags->addWidget(tag5);

    calendarAndSelectedTags->addWidget(calendar, 4);
    calendarAndSelectedTags->addLayout(selectedTagsLay, 6);

    mainLay->addLayout(calendarAndSelectedTags);
    mainLay->addWidget(selectTagsWidget);

    connect(calendar, &QCalendarWidget::clicked, this, [this](QDate date){
        selectedDay->setText(date.toString());
    });

    setLayout(mainLay);
}
