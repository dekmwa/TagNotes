#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), stackedWidget(new QStackedWidget()),
    notesWidget(new NotesWidget(this)), mainMenuWidget(new MainMenuWidget),
    deleteTagsOrCategoriesWidget(new DeleteTagsOrCategoriesWidget)

{
    stackedWidget->addWidget(notesWidget);
    stackedWidget->addWidget(mainMenuWidget);
    stackedWidget->addWidget(deleteTagsOrCategoriesWidget);

    stackedWidget->setCurrentIndex(1);

    connect(mainMenuWidget, &MainMenuWidget::onShowNotesClicked, this, &MainWindow::showNotesWidget);
    connect(mainMenuWidget, &MainMenuWidget::onShowDeleteClicked, this, [this](){
        stackedWidget->setCurrentIndex(2);
    });

    connect(notesWidget, &NotesWidget::onBackToMenu, this, [this](){
        stackedWidget->setCurrentIndex(1);
    });
    connect(deleteTagsOrCategoriesWidget, &DeleteTagsOrCategoriesWidget::onBackToMenu, this, [this](){
        stackedWidget->setCurrentIndex(1);
    });

    setCentralWidget(stackedWidget);
}

MainWindow::~MainWindow() {}

void MainWindow::showNotesWidget() {
    stackedWidget->setCurrentIndex(0);
}
