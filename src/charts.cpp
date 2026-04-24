#include "charts.h"

Charts::Charts(QWidget *parent) : QWidget{parent},
    m_database(Database::instance()),
    m_lay(new QVBoxLayout(this)),
    m_series(new QLineSeries()), m_chart(new QChart())
{
    setupNavigation();
    setupDatesChoice();
    setupTagsSelect();
    setupChart();
}

void Charts::setupNavigation() {
    QLabel *widgetTite = new QLabel();
    widgetTite->setText("Создание графиков");

    QPushButton *backToMenu = new QPushButton();
    backToMenu->setText("Меню");
    connect(backToMenu, &QPushButton::clicked, this, [this](){
        emit onBackToMenu();
    });

    QHBoxLayout *navigation = new QHBoxLayout();

    navigation->addWidget(backToMenu, 0);
    navigation->addWidget(widgetTite, 1);

    m_lay->addLayout(navigation, 0);
}

void Charts::setupDatesChoice() {
    QHBoxLayout *lay = new QHBoxLayout();

    QLabel *text1 = new QLabel();
    text1->setText("с");
    QLabel *text2 = new QLabel();
    text2->setText("по");
    m_startDate = new QDateEdit();
    m_startDate->setDate(QDate::currentDate().addDays(-10));
    m_startDate->setCalendarPopup(true);
    m_startDate->setDisplayFormat("dd.MM.yyyy");
    m_endDate = new QDateEdit();
    m_endDate->setDate(QDate::currentDate().addDays(10));
    m_endDate->setCalendarPopup(true);
    m_endDate->setDisplayFormat("dd.MM.yyyy");

    lay->addWidget(text1);
    lay->addWidget(m_startDate);
    lay->addWidget(text2);
    lay->addWidget(m_endDate);

    m_lay->addLayout(lay, 0);
}

void Charts::setupTagsSelect() {
    // QHBoxLayout *lay = new QHBoxLayout();

    // QVBoxLayout *layV = new QVBoxLayout();
    // tagsViewer = new TagsViewer(this);
    // QPushButton *button = new QPushButton();
    // button->setText("Создать график");
    // connect(button, &QPushButton::clicked, this, [this](){
    //     updateChart();
    // });

    // categoriesAndTagsWidget = new CategoriesAndTagsWidget(this, Mode::VIEW_ONLY);
    // connect(categoriesAndTagsWidget, &CategoriesAndTagsWidget::onTagClicked, this, [this](int tagId){
    //     tagsViewer->addTag(tagId);
    // });
    // connect(tagsViewer, &TagsViewer::onTagClicked, this, [this](int tagId){
    //     tagsViewer->removeTag(tagId);
    // });

    // layV->addWidget(tagsViewer);
    // layV->addWidget(button);

    // lay->addLayout(layV, 3);
    // lay->addWidget(categoriesAndTagsWidget, 7);

    // m_lay->addLayout(lay, 0);
}

void Charts::setupChart() {
    m_series->setName("m_series");

    m_axisX = new QDateTimeAxis();
    m_axisX->setTitleText("Дата");
    m_axisX->setFormat("d MMM");

    m_axisY = new QValueAxis();
    m_axisY->setTitleText("Количество выбранных тегов");
    m_axisY->setRange(0, 7);
    m_axisY->setLabelFormat("%.0f");
    m_axisY->setTickCount(8);

    m_chart->addSeries(m_series);
    m_chart->setTitle("График тегов");

    m_chart->addAxis(m_axisX, Qt::AlignBottom);
    m_chart->addAxis(m_axisY, Qt::AlignLeft);

    m_series->attachAxis(m_axisX);
    m_series->attachAxis(m_axisY);

    m_chartView = new QChartView(m_chart);
    m_chartView->setRenderHint(QPainter::Antialiasing);

    m_lay->addWidget(m_chartView, 1);
}

void Charts::updateChart() {
    // QDate startDate = m_startDate->date();
    // QDate endDate = m_endDate->date();

    // if (endDate <= startDate) {
    //     qDebug() << "Charts::updateChart: endDate <= startDate";
    //     return;
    // }

    // QVector<int> tagIds = tagsViewer->getTagIds();
    // if (tagIds.isEmpty()) {
    //     qDebug() << "Charts::updateChart: нет выбранных тегов";
    //     m_series->clear();
    //     return;
    // }

    // m_series->clear();

    // int maxTagsOfDay = 0;

    // for (QDate date = startDate; date <= endDate; date = date.addDays(1)) {
    //     int tagsOfDay = 0;
    //     QMap<int, QString> tagsByDate = m_database.getTagsByDate(date);

    //     for (int id : tagsByDate.keys()) {
    //         if (tagIds.contains(id)) {
    //             tagsOfDay++;
    //         }
    //     }

    //     if (tagsOfDay > maxTagsOfDay) {
    //         maxTagsOfDay = tagsOfDay;
    //     }

    //     QDateTime dateTime(date, QTime(0, 0, 0));
    //     m_series->append(dateTime.toMSecsSinceEpoch(), tagsOfDay);
    // }

    // QDateTime startDateTime(startDate, QTime(0, 0, 0));
    // QDateTime endDateTime(endDate, QTime(0, 0, 0));
    // m_axisX->setRange(startDateTime, endDateTime);
    // m_axisX->setTickCount(startDateTime.daysTo(endDateTime) + 1);

    // m_axisY->setRange(0, maxTagsOfDay + 1);
    // m_axisY->setTickCount(maxTagsOfDay + 2);
}

void Charts::onBecomeActive() {
    categoriesAndTagsWidget->refresh();
}
