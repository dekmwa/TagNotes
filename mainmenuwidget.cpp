#include "mainmenuwidget.h"

MainMenuWidget::MainMenuWidget(QWidget *parent) : QWidget{parent}, mainLay(new QVBoxLayout()),
    widgetTitle(new QLabel()),
    toDeleteWidget(new QPushButton()), toCreateNotes(new QPushButton()), toCharts(new QPushButton()),
    navigateButtons(new QHBoxLayout())
{
    toDeleteWidget->setText("Удаление");
    toCreateNotes->setText("Заметки");
    toCharts->setText("Графики");

    navigateButtons->addWidget(toDeleteWidget);
    navigateButtons->addWidget(toCreateNotes);
    navigateButtons->addWidget(toCharts);

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

    setLayout(mainLay);
}
