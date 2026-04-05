#include "customcalendar.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>

CustomCalendar::CustomCalendar(QWidget *parent)
    : QWidget{parent}
    , m_mainLayout(new QVBoxLayout(this))
    , m_calendarGrid(new QGridLayout())
    , m_currentMonth(QDate::currentDate())
    , m_selectedDate(QDate::currentDate())
{
    setAttribute(Qt::WA_StyledBackground, true);
    setObjectName("CustomCalendar");

    setupUI();
    updateCalendar();
}

void CustomCalendar::setupUI() {
    QHBoxLayout* topPanel = new QHBoxLayout();

    QPushButton* prevBtn = new QPushButton("<");
    prevBtn->setProperty("type", "prevMonthButton");
    prevBtn->setMinimumSize(20, 20);

    QPushButton* nextBtn = new QPushButton(">");
    nextBtn->setProperty("type", "nextMonthButton");
    nextBtn->setMinimumSize(20, 20);

    QPushButton* todayBtn = new QPushButton("Сегодня");
    todayBtn->setProperty("type", "toToday");

    m_monthYearLabel = new QLabel();
    m_monthYearLabel->setProperty("type", "monthAndYear");
    m_monthYearLabel->setAlignment(Qt::AlignCenter);

    topPanel->addWidget(prevBtn);
    topPanel->addWidget(m_monthYearLabel, 1);
    topPanel->addWidget(nextBtn);
    topPanel->addWidget(todayBtn);

    connect(prevBtn, &QPushButton::clicked, this, &CustomCalendar::goToPreviousMonth);
    connect(nextBtn, &QPushButton::clicked, this, &CustomCalendar::goToNextMonth);
    connect(todayBtn, &QPushButton::clicked, this, &CustomCalendar::goToToday);

    for (int i = 0; i < 7; ++i) {
        m_calendarGrid->setColumnStretch(i, 1);
    }

    QStringList weekdays = {"Пн", "Вт", "Ср", "Чт", "Пт", "Сб", "Вс"};
    for (int col = 0; col < 7; ++col) {
        QLabel* dayLabel = new QLabel(weekdays[col]);
        dayLabel->setAlignment(Qt::AlignCenter);
        dayLabel->setObjectName("weekDayLabel");
        m_calendarGrid->addWidget(dayLabel, 0, col);
    }

    m_mainLayout->addLayout(topPanel);
    m_mainLayout->addLayout(m_calendarGrid);
}

void CustomCalendar::clearCalendar() {
    for (int row = 1; row <= 6; ++row) {
        for (int col = 0; col < 7; ++col) {
            QLayoutItem* item = m_calendarGrid->itemAtPosition(row, col);
            if (item && item->widget()) {
                delete item->widget();
            }
        }
    }
    m_dayButtons.clear();
}

void CustomCalendar::updateCalendar() {
    clearCalendar();

    m_monthYearLabel->setText(m_currentMonth.toString("MMMM yyyy"));

    QDate firstDayOfMonth(m_currentMonth.year(), m_currentMonth.month(), 1);
    int dayOfWeek = firstDayOfMonth.dayOfWeek();
    QDate startDate = firstDayOfMonth.addDays(1 - dayOfWeek);

    int dayNumber = 0;
    for (int row = 1; row <= 6; ++row) {
        for (int col = 0; col < 7; ++col) {
            QDate date = startDate.addDays(dayNumber++);
            QPushButton* btn = new QPushButton(QString::number(date.day()));

            btn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
            btn->setMinimumSize(30, 30);

            if (date.month() == m_currentMonth.month() && date.year() == m_currentMonth.year()) {
                btn->setProperty("type", "currentMonthDay");
            } else {
                btn->setProperty("type", "anotherMonthDay");
            }

            if (date == QDate::currentDate()) {
                btn->setProperty("type", "today");
            }

            if (date == m_selectedDate) {
                btn->setProperty("type", "selected");
            }

            btn->setProperty("dayButton", true);

            connect(btn, &QPushButton::clicked, this, [this, date]() {
                m_selectedDate = date;
                updateCalendar();
                emit onDayClicked(date);
            });

            m_calendarGrid->addWidget(btn, row, col);
            m_dayButtons.append(btn);
        }
    }

    for (int row = 1; row <= 6; ++row) {
        m_calendarGrid->setRowStretch(row, 1);
    }
}

QDate CustomCalendar::getSelectedDate() {
    return m_selectedDate;
}

void CustomCalendar::goToPreviousMonth() {
    m_currentMonth = m_currentMonth.addMonths(-1);
    updateCalendar();
}

void CustomCalendar::goToNextMonth() {
    m_currentMonth = m_currentMonth.addMonths(1);
    updateCalendar();
}

void CustomCalendar::goToToday() {
    m_currentMonth = QDate::currentDate();
    m_selectedDate = QDate::currentDate();
    updateCalendar();
}
