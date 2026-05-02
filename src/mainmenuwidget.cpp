#include "mainmenuwidget.h"

MainMenuWidget::MainMenuWidget(QWidget *parent) : QWidget{parent}, mainLay(new QVBoxLayout(this)),
    widgetTitle(new QLabel("Главное меню")),
    toDeleteWidget(new QPushButton()), toCreateNotes(new QPushButton()), toCharts(new QPushButton()), toDbSettings(new QPushButton()),
    navigateButtons(new QHBoxLayout())
{
    setAttribute(Qt::WA_StyledBackground, true);
    setObjectName("MainMenuWidget");

    widgetTitle->setAlignment(Qt::AlignCenter);
    widgetTitle->setProperty("type", "text");

    toDeleteWidget->setText("Удаление");
    toCreateNotes->setText("Заметки");
    toCharts->setText("Графики");
    toDbSettings->setText("Настройка Бд");

    navigateButtons->addWidget(toDeleteWidget);
    navigateButtons->addWidget(toCreateNotes);
    navigateButtons->addWidget(toCharts);
    navigateButtons->addWidget(toDbSettings);

    mainLay->addWidget(widgetTitle);
    mainLay->addStretch();
    setupCalendarAndTagsView();
    mainLay->addStretch();
    mainLay->addLayout(navigateButtons);

    connect(toCreateNotes, &QPushButton::clicked, this, [this](){
        emit onShowNotesClicked();
    });
    connect(toDeleteWidget, &QPushButton::clicked, this, [this](){
        emit onShowDeleteClicked();
    });
    connect(toCharts, &QPushButton::clicked, this, [this](){
        emit onShowChartsClicked();
    });
    connect(toDbSettings, &QPushButton::clicked, this, [this](){
        emit onShowDbSettingsClicked();
    });

    tagsByDate->updateTagsByDate(QDate::currentDate());

    setLayout(mainLay);
}

void MainMenuWidget::setupCalendarAndTagsView() {
    calendarAndTagsView = new QHBoxLayout();

    calendar = new CustomCalendar();
    calendar->setMaximumWidth(400);
    calendar->setMaximumHeight(350);

    tagsByDate = new TagsByDateWidget();

    connect(calendar, &CustomCalendar::onDayClicked, tagsByDate, &TagsByDateWidget::updateTagsByDate);

    calendarAndTagsView->addWidget(calendar, 4);
    calendarAndTagsView->addWidget(tagsByDate, 6);

    mainLay->addLayout(calendarAndTagsView);
}

void MainMenuWidget::onBecomeActive() {
    tagsByDate->updateTagsByDate(QDate::currentDate());
}
