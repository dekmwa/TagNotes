#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
    stackedWidget(new QStackedWidget()),
    notesWidget(new NotesWidget(this)),
    mainMenuWidget(new MainMenuWidget(this)),
    deleteTagsOrCategoriesWidget(new DeleteTagsOrCategoriesWidget(this)),
    charts(new Charts(this)),
    databaseSettingsWidget(new DatabaseSettingsWidget()),
    m_database(Database::instance())
{
    stackedWidget->addWidget(notesWidget);
    stackedWidget->addWidget(mainMenuWidget);
    stackedWidget->addWidget(deleteTagsOrCategoriesWidget);
    stackedWidget->addWidget(charts);
    stackedWidget->addWidget(databaseSettingsWidget);

    stackedWidget->setCurrentIndex(1);
    if (!m_database.isOpen()) {
        databaseSettingsWidget->setupSetDbMode();
        stackedWidget->setCurrentIndex(4);
    }

    connect(mainMenuWidget, &MainMenuWidget::onShowNotesClicked, this, [this](){
        notesWidget->onBecomeActive();
        stackedWidget->setCurrentIndex(0);
    });
    connect(mainMenuWidget, &MainMenuWidget::onShowDeleteClicked, this, [this](){
        deleteTagsOrCategoriesWidget->onBecomeActive();
        stackedWidget->setCurrentIndex(2);
    });
    connect(mainMenuWidget, &MainMenuWidget::onShowChartsClicked, this, [this](){
        charts->onBecomeActive();
        stackedWidget->setCurrentIndex(3);
    });
    connect(mainMenuWidget, &MainMenuWidget::onShowDbSettingsClicked, this, [this](){
        databaseSettingsWidget->onBecomeActive();
        stackedWidget->setCurrentIndex(4);
    });

    connect(notesWidget, &NotesWidget::onBackToMenu, this, [this](){
        stackedWidget->setCurrentIndex(1);
    });
    connect(deleteTagsOrCategoriesWidget, &DeleteTagsOrCategoriesWidget::onBackToMenu, this, [this](){
        stackedWidget->setCurrentIndex(1);
    });
    connect(charts, &Charts::onBackToMenu, this, [this](){
        stackedWidget->setCurrentIndex(1);
    });
    connect(databaseSettingsWidget, &DatabaseSettingsWidget::onBackToMenu, this, [this](){
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
