#include "databasesettingswidget.h"
#include "ui_databasesettingswidget.h"

DatabaseSettingsWidget::DatabaseSettingsWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::DatabaseSettingsWidget),
    m_database(Database::instance())
{
    ui->setupUi(this);
}

void DatabaseSettingsWidget::setupSetDbMode() {
    ui->infoText->setText("Файл с заметками не найден, укажите новый путь.");
    ui->toMenuButton->setEnabled(false);
}

void DatabaseSettingsWidget::connectDbByNewPath(QString& path) {
    if (m_database.connectDatabase(path)) {
        QSettings config("config.ini", QSettings::IniFormat);
        config.setValue("Database/path", path);
        ui->toMenuButton->setEnabled(true);
        ui->infoText->setText("Успешное подключение! Новый файл будет использоваться по умолчанию.");
    }
}

void DatabaseSettingsWidget::on_toMenuButton_clicked() {
    emit onBackToMenu();
}

void DatabaseSettingsWidget::on_selectFileButton_clicked() {
    QString filePath = QFileDialog::getOpenFileName(
        this,
        "Укажите файл с заметками",
        "",
        "Все файлы (*.db)"
    );

    if (!filePath.isEmpty()) {
        connectDbByNewPath(filePath);
    }
}

void DatabaseSettingsWidget::onBecomeActive() {
    ui->infoText->setText("Вы можете выбрать другой файл с заметками");
}

DatabaseSettingsWidget::~DatabaseSettingsWidget()
{
    delete ui;
}
