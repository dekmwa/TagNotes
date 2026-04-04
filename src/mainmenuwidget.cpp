#include "mainmenuwidget.h"

MainMenuWidget::MainMenuWidget(QWidget *parent) : QWidget{parent}, mainLay(new QVBoxLayout()),
    widgetTitle(new QLabel()),
    toDeleteWidget(new QPushButton()), toCreateNotes(new QPushButton()), toCharts(new QPushButton()), toDbSettings(new QPushButton()),
    navigateButtons(new QHBoxLayout())
{
    toDeleteWidget->setText("Удаление");
    toCreateNotes->setText("Заметки");
    toCharts->setText("Графики");
    toDbSettings->setText("Настройка Бд");

    navigateButtons->addWidget(toDeleteWidget);
    navigateButtons->addWidget(toCreateNotes);
    navigateButtons->addWidget(toCharts);
    navigateButtons->addWidget(toDbSettings);

    mainLay->addWidget(widgetTitle);
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

    setLayout(mainLay);
}
