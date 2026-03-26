#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "noteswidget.h"
#include "deletetagsorcategorieswidget.h"
#include "mainmenuwidget.h"
#include <QStackedWidget>


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

    QStackedWidget *stackedWidget;

    void setupWindowSettings();
};
#endif // MAINWINDOW_H
