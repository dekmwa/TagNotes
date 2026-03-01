#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "noteswidget.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    NotesWidget *notesWidget;
};
#endif // MAINWINDOW_H
