#ifndef CUSTOMCALENDAR_H
#define CUSTOMCALENDAR_H

#include <QWidget>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>
#include <QDate>


class CustomCalendar : public QWidget
{
    Q_OBJECT
public:
    explicit CustomCalendar(QWidget *parent = nullptr);

    QDate getSelectedDate();
    //void setSelectedDate(QDate& date);
    void updateDaysByCurrentMonth();

signals:
    void onDayClicked(QDate date);

private:
    QVBoxLayout *m_lay;
    QGridLayout *m_daysLay;
    QVector<QPushButton*> m_daysButtons;
    QDate m_selectedDate;
    QDate m_currentMonth;
    QLabel *monthAndYear;

    void setupTopPanel();
    void setupWeekdayPanel();

    void extracted();
    void clearDays();

private slots:
    void goToPreviousMonth();
    void goToNextMonth();
    void goToToday();
};

#endif // CUSTOMCALENDAR_H
