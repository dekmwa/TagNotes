#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), stackedWidget(new QStackedWidget()),
    notesWidget(new NotesWidget(this)), mainMenuWidget(new MainMenuWidget),
    deleteTagsOrCategoriesWidget(new DeleteTagsOrCategoriesWidget)
{
    stackedWidget->addWidget(notesWidget);
    stackedWidget->addWidget(mainMenuWidget);
    stackedWidget->addWidget(deleteTagsOrCategoriesWidget);

    stackedWidget->setCurrentIndex(1);

    connect(mainMenuWidget, &MainMenuWidget::onShowNotesClicked, this, [this](){
        notesWidget->onBecomeActive();
        stackedWidget->setCurrentIndex(0);
    });
    connect(mainMenuWidget, &MainMenuWidget::onShowDeleteClicked, this, [this](){
        deleteTagsOrCategoriesWidget->onBecomeActive();
        stackedWidget->setCurrentIndex(2);
    });

    connect(notesWidget, &NotesWidget::onBackToMenu, this, [this](){
        stackedWidget->setCurrentIndex(1);
    });
    connect(deleteTagsOrCategoriesWidget, &DeleteTagsOrCategoriesWidget::onBackToMenu, this, [this](){
        stackedWidget->setCurrentIndex(1);
    });

    setupWindowSettings();

    setCentralWidget(stackedWidget);
}

void MainWindow::setupWindowSettings() {
    resize(800, 500);
    setMinimumWidth(500);
    setMinimumHeight(300);
}

MainWindow::~MainWindow() {}
