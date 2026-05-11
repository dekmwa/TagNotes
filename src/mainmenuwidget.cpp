#include "mainmenuwidget.h"

MainMenuWidget::MainMenuWidget(QWidget *parent) : QWidget{parent}, mainLay(new QVBoxLayout(this)),
    widgetTitle(new QLabel("Главное меню")),
    statisticsWidget(new StatisticsWidget())
{
    setAttribute(Qt::WA_StyledBackground, true);
    setObjectName("MainMenuWidget");

    widgetTitle->setAlignment(Qt::AlignCenter);
    widgetTitle->setProperty("type", "widgetTitle");

    mainLay->addWidget(widgetTitle);
    mainLay->addStretch();
    mainLay->addWidget(statisticsWidget);
    mainLay->addStretch();
    setupCalendarAndTagsView();
    mainLay->addStretch();
    setupNavigationButtons();

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
    statisticsWidget->updateStatistics();

    setLayout(mainLay);
}

void MainMenuWidget::setupNavigationButtons() {
    QWidget *buttonsContainer = new QWidget();
    buttonsLay = new QHBoxLayout();
    QHBoxLayout *centeredLay = new QHBoxLayout();

    toDeleteWidget = new QPushButton();
    toCreateNotes = new QPushButton();
    toCharts = new QPushButton();
    toDbSettings = new QPushButton();

    toDeleteWidget->setText("Удаление");
    toDeleteWidget->setProperty("type", "navigationButton");
    toDeleteWidget->setProperty("name", "toDeleteWidget");
    toDeleteWidget->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    toCreateNotes->setText("Заметки");
    toCreateNotes->setProperty("type", "navigationButton");
    toCreateNotes->setProperty("name", "toCreateNotes");
    toCreateNotes->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    toCharts->setText("Графики");
    toCharts->setProperty("type", "navigationButton");
    toCharts->setProperty("name", "toCharts");
    toCharts->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    toDbSettings->setText("Настройка Бд");
    toDbSettings->setProperty("type", "navigationButton");
    toDbSettings->setProperty("name", "toDbSettings");
    toDbSettings->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    buttonsLay->addWidget(toDeleteWidget);
    buttonsLay->addWidget(toCreateNotes);
    buttonsLay->addWidget(toCharts);
    buttonsLay->addWidget(toDbSettings);

    buttonsContainer->setLayout(buttonsLay);

    centeredLay->addStretch();
    centeredLay->addWidget(buttonsContainer);
    centeredLay->addStretch();

    buttonsContainer->setProperty("type", "buttonsContainer");

    mainLay->addLayout(centeredLay);
}

void MainMenuWidget::setupCalendarAndTagsView() {
    calendarAndTagsView = new QHBoxLayout();

    calendar = new CustomCalendar();
    calendar->setMaximumWidth(400);
    calendar->setMaximumHeight(500);

    tagsByDate = new TagsByDateWidget();

    connect(calendar, &CustomCalendar::onDayClicked, tagsByDate, &TagsByDateWidget::updateTagsByDate);

    calendarAndTagsView->addWidget(calendar, 4);
    calendarAndTagsView->addWidget(tagsByDate, 6);

    mainLay->addLayout(calendarAndTagsView);
}

void MainMenuWidget::onBecomeActive() {
    tagsByDate->updateTagsByDate(QDate::currentDate());
    statisticsWidget->updateStatistics();
}
