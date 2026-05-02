#ifndef NOTESWIDGET_H
#define NOTESWIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QScrollArea>
#include <QVBoxLayout>
#include "tagsbydatewidget.h"
#include "categoriesandtagswidget.h"
#include "customcalendar.h"
#include "database.h"


class NotesWidget : public QWidget
{
    Q_OBJECT

public:
    explicit NotesWidget(QWidget *parent = nullptr);

    void onBecomeActive();

private:
    Database &db;

    CustomCalendar *calendar;

    QVBoxLayout *selectedTagsLay;
    QHBoxLayout *calendarAndSelectedTags;

    QLabel *widgetTite;
    QPushButton *backToMenu;
    QHBoxLayout *navigation;

    QLabel *selectedDay;
    TagsByDateWidget *selectedTags;
    QPushButton *saveDay;

    QVBoxLayout *mainLay;

    void setupNavigation();

    CategoriesAndTagsWidget *categoriesAndTagsWidget;

signals:
    void onBackToMenu();

private slots:
    void onTagClicked(int tagId);
};

#endif // NOTESWIDGET_H
