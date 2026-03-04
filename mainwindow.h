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

    void showNotesWidget();

private:
    MainMenuWidget *mainMenuWidget;
    NotesWidget *notesWidget;
    DeleteTagsOrCategoriesWidget *deleteTagsOrCategoriesWidget;

    QStackedWidget *stackedWidget;
};
#endif // MAINWINDOW_H
