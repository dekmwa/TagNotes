#ifndef MAINMENUWIDGET_H
#define MAINMENUWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>


class MainMenuWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MainMenuWidget(QWidget *parent = nullptr);

private:
    QLabel *widgetTitle;

    QVBoxLayout *mainLay;
    QHBoxLayout *navigateButtons;

    QPushButton *toDeleteWidget;
    QPushButton *toCreateNotes;
    QPushButton *toCharts;
    QPushButton *toDbSettings;

signals:
    void onShowNotesClicked();
    void onShowDeleteClicked();
    void onShowChartsClicked();
    void onShowDbSettingsClicked();
};

#endif // MAINMENUWIDGET_H
