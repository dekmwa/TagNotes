#ifndef NOTESWIDGET_H
#define NOTESWIDGET_H

#include <QWidget>
#include <QCalendarWidget>
#include <QHBoxLayout>
#include <QLabel>
#include "qflowlayout.h"
#include <QPushButton>
#include <QScrollArea>
#include <QVBoxLayout>
#include "selecttagswidget.h"


class NotesWidget : public QWidget
{
    Q_OBJECT

public:
    explicit NotesWidget(QWidget *parent = nullptr);

private:
    QCalendarWidget *calendar;

    QVBoxLayout *selectedTagsLay;
    QHBoxLayout *calendarAndSelectedTags;

    QLabel *selectedDay;
    QFlowLayout *selectedTags;
    QPushButton *saveDay;

    SelectTagsWidget *selectTagsWidget;

    QVBoxLayout *mainLay;
};

#endif // NOTESWIDGET_H
