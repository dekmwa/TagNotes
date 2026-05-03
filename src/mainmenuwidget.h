#ifndef MAINMENUWIDGET_H
#define MAINMENUWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "customcalendar.h"
#include "tagsbydatewidget.h"


class MainMenuWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MainMenuWidget(QWidget *parent = nullptr);
    void onBecomeActive();

private:
    QLabel *widgetTitle;

    QVBoxLayout *mainLay;

    QHBoxLayout *buttonsLay;
    QPushButton *toDeleteWidget;
    QPushButton *toCreateNotes;
    QPushButton *toCharts;
    QPushButton *toDbSettings;
    void setupNavigationButtons();

    QHBoxLayout *calendarAndTagsView;
    CustomCalendar *calendar;
    TagsByDateWidget *tagsByDate;
    void setupCalendarAndTagsView();

signals:
    void onShowNotesClicked();
    void onShowDeleteClicked();
    void onShowChartsClicked();
    void onShowDbSettingsClicked();
};

#endif // MAINMENUWIDGET_H
