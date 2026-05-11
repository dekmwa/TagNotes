#ifndef DATABASESETTINGSWIDGET_H
#define DATABASESETTINGSWIDGET_H

#include <QWidget>
#include <QSettings>
#include <QFileDialog>
#include <QInputDialog>
#include <QLineEdit>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QMessageBox>
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
    void createNewDbAndConnect(QString& path);

private:
    Ui::DatabaseSettingsWidget *ui;
    Database& m_database;

    bool exportStatisticsAndTags(const QString& filePath);

private slots:
    void on_toMenuButton_clicked();
    void on_selectFileButton_clicked();
    void on_selectPathButton_clicked();
    void on_exportButton_clicked();

signals:
    void onBackToMenu();
};

#endif // DATABASESETTINGSWIDGET_H
