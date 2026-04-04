#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include "noteswidget.h"
#include "deletetagsorcategorieswidget.h"
#include "mainmenuwidget.h"
#include "charts.h"
#include "databasesettingswidget.h"
#include "database.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    MainMenuWidget *mainMenuWidget;
    NotesWidget *notesWidget;
    DeleteTagsOrCategoriesWidget *deleteTagsOrCategoriesWidget;
    Charts *charts;
    DatabaseSettingsWidget *databaseSettingsWidget;

    QStackedWidget *stackedWidget;

    Database& m_database;

    void setupWindowSettings();
};
#endif // MAINWINDOW_H
