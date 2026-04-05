#ifndef NOTESWIDGET_H
#define NOTESWIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QScrollArea>
#include <QVBoxLayout>
#include "tagsbydatewidget2.h"
#include "categoriesandtagswidget.h"
#include "customcalendar.h"


class NotesWidget : public QWidget
{
    Q_OBJECT

public:
    explicit NotesWidget(QWidget *parent = nullptr);

    void onBecomeActive();

private:
    CustomCalendar *calendar;

    QVBoxLayout *selectedTagsLay;
    QHBoxLayout *calendarAndSelectedTags;

    QLabel *widgetTite;
    QPushButton *backToMenu;
    QHBoxLayout *navigation;

    QLabel *selectedDay;
    TagsByDateWidget2 *selectedTags;
    QPushButton *saveDay;

    QVBoxLayout *mainLay;

    void setupNavigation();

    CategoriesAndTagsWidget *categoriesAndTagsWidget;

signals:
    void onBackToMenu();
};

#endif // NOTESWIDGET_H
