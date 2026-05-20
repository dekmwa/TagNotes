#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QWidget(parent),
    mLay(new QVBoxLayout(this)), stackedWidget(new QStackedWidget()),
    notesWidget(new NotesWidget(this)),
    mainMenuWidget(new MainMenuWidget(this)),
    deleteTagsOrCategoriesWidget(new EditTagsOrCategoriesWidget(this)),
    charts(new Charts(this)),
    databaseSettingsWidget(new DatabaseSettingsWidget()),
    customAppPanel(new CustomAppPanel()),
    m_database(Database::instance())
{
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);

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
        mainMenuWidget->onBecomeActive();
        stackedWidget->setCurrentIndex(1);
    });
    connect(deleteTagsOrCategoriesWidget, &EditTagsOrCategoriesWidget::onBackToMenu, this, [this](){
        mainMenuWidget->onBecomeActive();
        stackedWidget->setCurrentIndex(1);
    });
    connect(charts, &Charts::onBackToMenu, this, [this](){
        mainMenuWidget->onBecomeActive();
        stackedWidget->setCurrentIndex(1);
    });
    connect(databaseSettingsWidget, &DatabaseSettingsWidget::onBackToMenu, this, [this](){
        mainMenuWidget->onBecomeActive();
        stackedWidget->setCurrentIndex(1);
    });

    connect(customAppPanel, &CustomAppPanel::minimizeRequested, this, &MainWindow::showMinimized);
    connect(customAppPanel, &CustomAppPanel::closeRequested, this, &MainWindow::close);

    setupWindowSettings();

    mLay->addWidget(customAppPanel, 0);
    mLay->addWidget(stackedWidget, 1);
}

void MainWindow::setupWindowSettings() {
    resize(1000, 700);
    setMinimumWidth(500);
    setMinimumHeight(300);
    mLay->setContentsMargins(0, 0, 0, 0);
    mLay->setSpacing(0);
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if (customAppPanel->geometry().contains(event->pos())) {
        m_dragging = true;
        m_dragPosition = event->globalPos() - frameGeometry().topLeft();
        event->accept();
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if (m_dragging && (event->buttons() & Qt::LeftButton)) {
        move(event->globalPos() - m_dragPosition);
        event->accept();
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        m_dragging = false;
        event->accept();
    }
}

MainWindow::~MainWindow() {}
