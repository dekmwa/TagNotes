#include "customcalendar.h"

CustomCalendar::CustomCalendar(QWidget *parent)
    : QWidget{parent},
    m_lay(new QVBoxLayout(this)),
    m_daysLay(new QGridLayout()),
    m_currentMonth(QDate::currentDate())
{
    setupTopPanel();
    setupWeekdayPanel();
    updateDaysByCurrentMonth();
}

void CustomCalendar::setupTopPanel() {
    QHBoxLayout *lay = new QHBoxLayout();

    QPushButton *goPrevMonth = new QPushButton();
    goPrevMonth->setText("<-");

    monthAndYear = new QLabel();

    QPushButton *goNextMonth = new QPushButton();
    goNextMonth->setText("->");

    QPushButton *goToday = new QPushButton();
    goToday->setText("сегодня");

    lay->addWidget(goPrevMonth);
    lay->addWidget(monthAndYear);
    lay->addWidget(goNextMonth);
    lay->addWidget(goToday);

    connect(goPrevMonth, &QPushButton::clicked, this, &CustomCalendar::goToPreviousMonth);
    connect(goNextMonth, &QPushButton::clicked, this, &CustomCalendar::goToNextMonth);
    connect(goToday, &QPushButton::clicked, this, &CustomCalendar::goToToday);

    m_lay->addLayout(lay);
}

void CustomCalendar::setupWeekdayPanel() {
    QVector<QString> weekdays = {"Пн", "Вт", "Ср", "Чт", "Пт", "Сб", "Вс"};
    for (int i = 0; i < 7; ++i) {
        QLabel *day = new QLabel(weekdays[i], this);
        day->setAlignment(Qt::AlignCenter);
        m_daysLay->addWidget(day, 0, i);
    }

    m_lay->addLayout(m_daysLay);
}

void CustomCalendar::clearDays() {
    for (auto btn : m_daysButtons) {
        m_daysLay->removeWidget(btn);
        delete btn;
    }
    m_daysButtons.clear();
}

void CustomCalendar::updateDaysByCurrentMonth() {
    clearDays();
    monthAndYear->clear();
    monthAndYear->setText(m_currentMonth.toString("MMMM yyyy"));

    QDate firstDayOfMonth(m_currentMonth.year(), m_currentMonth.month(), 1);
    int dayOfWeek = firstDayOfMonth.dayOfWeek();
    QDate startDate = firstDayOfMonth.addDays(1 - dayOfWeek);

    int dayNumber = 0;
    for (int i = 1; i <= 6; ++i) {
        for (int j = 0; j <= 6; ++j) {
            QDate date = startDate.addDays(dayNumber++);
            QPushButton *day = new QPushButton(QString::number(date.day()), this);
            connect(day, &QPushButton::clicked, this, [this, date](){
                m_selectedDate = date;
                emit onDayClicked(date);
            });
            m_daysLay->addWidget(day, i, j);
            m_daysButtons.push_back(day);
        }
    }
}

QDate CustomCalendar::getSelectedDate() {
    return m_selectedDate;
}

void CustomCalendar::goToPreviousMonth() {
    m_currentMonth = m_currentMonth.addMonths(-1);
    updateDaysByCurrentMonth();
}

void CustomCalendar::goToNextMonth() {
    m_currentMonth = m_currentMonth.addMonths(1);
    updateDaysByCurrentMonth();
}

void CustomCalendar::goToToday() {
    m_currentMonth = QDate::currentDate();
    updateDaysByCurrentMonth();
}
