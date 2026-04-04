#ifndef DATABASESETTINGSWIDGET_H
#define DATABASESETTINGSWIDGET_H

#include <QWidget>
#include <QSettings>
#include <QFileDialog>
#include "database.h"


namespace Ui {
class DatabaseSettingsWidget;
}

class DatabaseSettingsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DatabaseSettingsWidget(QWidget *parent = nullptr);
    ~DatabaseSettingsWidget();

    void onBecomeActive();
    void setupSetDbMode();
    void connectDbByNewPath(QString& path);

private:
    Ui::DatabaseSettingsWidget *ui;
    Database& m_database;

private slots:
    void on_toMenuButton_clicked();
    void on_selectFileButton_clicked();

signals:
    void onBackToMenu();
};

#endif // DATABASESETTINGSWIDGET_H
