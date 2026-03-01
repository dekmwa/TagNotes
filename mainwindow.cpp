#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), notesWidget(new NotesWidget(this))
{
    setCentralWidget(notesWidget);
}

MainWindow::~MainWindow() {}
