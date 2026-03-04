#include "mainmenuwidget.h"

MainMenuWidget::MainMenuWidget(QWidget *parent) : QWidget{parent}, mainLay(new QVBoxLayout()),
    widgetTitle(new QLabel()),
    toDeleteWidget(new QPushButton()), toCreateNotes(new QPushButton()), toGraphics(new QPushButton()),
    navigateButtons(new QHBoxLayout())
{
    toDeleteWidget->setText("Удаление");
    toCreateNotes->setText("Заметки");
    toGraphics->setText("Графики");

    navigateButtons->addWidget(toDeleteWidget);
    navigateButtons->addWidget(toCreateNotes);
    navigateButtons->addWidget(toGraphics);

    mainLay->addWidget(widgetTitle);
    mainLay->addLayout(navigateButtons);

    connect(toCreateNotes, &QPushButton::clicked, this, [this](){
        emit onShowNotesClicked();
    });
    connect(toDeleteWidget, &QPushButton::clicked, this, [this](){
        emit onShowDeleteClicked();
    });

    setLayout(mainLay);
}
