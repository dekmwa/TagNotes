#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QStackedWidget>
#include <QVBoxLayout>
#include <QMouseEvent>
#include "noteswidget.h"
#include "edittagsorcategorieswidget.h"
#include "mainmenuwidget.h"
#include "charts.h"
#include "databasesettingswidget.h"
#include "database.h"
#include "customapppanel.h"


class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    MainMenuWidget *mainMenuWidget;
    NotesWidget *notesWidget;
    EditTagsOrCategoriesWidget *deleteTagsOrCategoriesWidget;
    Charts *charts;
    DatabaseSettingsWidget *databaseSettingsWidget;
    CustomAppPanel *customAppPanel;

    QVBoxLayout *mLay;
    QStackedWidget *stackedWidget;

    Database& m_database;

    void setupWindowSettings();

    bool m_dragging = false;
    QPoint m_dragPosition;
};
#endif // MAINWINDOW_H
