#ifndef CUSTOMCALENDAR_H
#define CUSTOMCALENDAR_H

#include <QWidget>
#include <QDate>
#include <QVector>
#include <QPushButton>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QLabel;

class CustomCalendar : public QWidget
{
    Q_OBJECT
public:
    explicit CustomCalendar(QWidget *parent = nullptr);
    QDate getSelectedDate();

signals:
    void onDayClicked(const QDate &date);

private slots:
    void goToPreviousMonth();
    void goToNextMonth();
    void goToToday();

private:
    void setupUI();
    void updateCalendar();
    void clearCalendar();

    QVBoxLayout* m_mainLayout;
    QGridLayout* m_calendarGrid;

    QLabel* m_monthYearLabel;
    QVector<QPushButton*> m_dayButtons;

    QDate m_currentMonth;
    QDate m_selectedDate;
};

#endif
