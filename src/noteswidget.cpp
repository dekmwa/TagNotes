#include "noteswidget.h"


NotesWidget::NotesWidget(QWidget *parent) : QWidget{parent},
    db(Database::instance()),
    calendar(new CustomCalendar()),
    calendarAndSelectedTags(new QHBoxLayout()), selectedTagsLay(new QVBoxLayout()),
    selectedDay(new QLabel(this)), selectedTags(new TagsByDateWidget()), saveDay(new QPushButton("Сохранить", this)),
    mainLay(new QVBoxLayout()),
    categoriesAndTagsWidget(new CategoriesAndTagsWidget(this, Mode::ADD_TAGS_AND_ADD_CATEGORIES))
{
    setAttribute(Qt::WA_StyledBackground, true);
    setObjectName("NotesWidget");

    selectedDay->setAlignment(Qt::AlignCenter);
    selectedDay->setProperty("type", "text");
    selectedTagsLay->addWidget(selectedDay, 0);

    selectedTagsLay->addWidget(selectedTags, 1);

    QHBoxLayout *saveBntLay = new QHBoxLayout();
    saveBntLay->addStretch();
    saveBntLay->addWidget(saveDay);
    saveBntLay->addStretch();
    selectedTagsLay->addLayout(saveBntLay, 0);
    selectedTagsLay->setContentsMargins(20, 0, 10, 0);

    saveDay->setProperty("type", "saveDayButton");

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

    connect(categoriesAndTagsWidget, &CategoriesAndTagsWidget::onTagClicked, this, &NotesWidget::onTagClicked);

    connect(saveDay, &QPushButton::clicked, [this](){
        selectedTags->saveTags(calendar->getSelectedDate());
    });

    selectedTags->updateTagsByDate(QDate::currentDate());

    mainLay->setContentsMargins(20, 20, 20, 20);
    setLayout(mainLay);
}

void NotesWidget::onTagClicked(int tagId) {
    int markType = db.getTagMarkTypeById(tagId);
    MarkValue markValue;
    bool ok;
    QMap<int, MarkValue> tagAndValue;
    QString tagTitle = db.getTagTitleById(tagId);

    switch (markType) {
    case MarkType::WITHOUT:
        ok = true;
        break;
    case MarkType::NUMBER:
        int value = QInputDialog::getInt(
            this,
            "Значение метки",
            tagTitle,
            0, -999999, 999999, 1, &ok
            );
        if (ok) {
            markValue.valueInt = value;
        }
        break;
    }

    if (ok) {
        tagAndValue.insert(tagId, markValue);
        selectedTags->addTagToSelected(tagAndValue);
    }
}

void NotesWidget::setupNavigation() {
    widgetTitle = new QLabel();
    widgetTitle->setText("Создание заметок");
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
}

void NotesWidget::onBecomeActive() {
    categoriesAndTagsWidget->refresh();
    selectedTags->updateTagsByDate(QDate::currentDate());
}
