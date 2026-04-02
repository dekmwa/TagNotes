#ifndef CHARTS_H
#define CHARTS_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QDateEdit>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QChart>
#include <QDateTimeAxis >
#include <QValueAxis>
#include "tagsviewer.h"
#include "categoriesandtagswidget.h"


class Charts : public QWidget
{
    Q_OBJECT

public:
    explicit Charts(QWidget *parent = nullptr);
    void onBecomeActive();

private:
    Database& m_database;
    QVBoxLayout *m_lay;

    QLineSeries *m_series;
    QChart *m_chart;
    QChartView *m_chartView;

    QDateEdit *m_startDate;
    QDateEdit *m_endDate;
    QDateTimeAxis *m_axisX;
    QValueAxis *m_axisY;

    TagsViewer *tagsViewer;
    CategoriesAndTagsWidget *categoriesAndTagsWidget;

    void setupNavigation();
    void setupDatesChoice();
    void setupTagsSelect();
    void setupChart();

    void updateChart();

signals:
    void onBackToMenu();
};

#endif // CHARTS_H
