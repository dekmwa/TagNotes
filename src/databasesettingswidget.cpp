#include "databasesettingswidget.h"
#include "ui_databasesettingswidget.h"

DatabaseSettingsWidget::DatabaseSettingsWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::DatabaseSettingsWidget),
    m_database(Database::instance())
{
    ui->setupUi(this);

    setAttribute(Qt::WA_StyledBackground, true);
    setObjectName("DatabaseSettingsWidget");

    ui->toMenuButton->setObjectName("backToMenuButton");
    ui->headerText->setObjectName("widgetTitle");
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
        ui->infoText->setText("Успешное подключение! Этот файл будет использоваться по умолчанию.");
    } else {
        ui->infoText->setText("Не удалось использовать этот файл заметок. Укажите другой файл или создайте новый.");
        ui->toMenuButton->setEnabled(false);
    }
}

void DatabaseSettingsWidget::createNewDbAndConnect(QString& path) {
    if (m_database.createAndConnect(path)) {
        QSettings config("config.ini", QSettings::IniFormat);
        config.setValue("Database/path", path);
        ui->toMenuButton->setEnabled(true);
        ui->infoText->setText("Успешное подключение! Новый файл будет использоваться по умолчанию.");
    } else {
        ui->infoText->setText("Не удалось подключиться к новому файлу заметок.");
        ui->toMenuButton->setEnabled(false);
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

void DatabaseSettingsWidget::on_selectPathButton_clicked() {
    QString folderPath = QFileDialog::getExistingDirectory(
        nullptr,
        "Выберите папку для базы данных",
        QDir::homePath(),
        QFileDialog::ShowDirsOnly
        );

    if (folderPath.isEmpty()) {
        return;
    }

    bool ok;
    QString dbName = QInputDialog::getText(
        nullptr,
        "Имя базы данных",
        "Введите имя файла базы данных:",
        QLineEdit::Normal,
        "TagNotes.db",
        &ok
        );

    if (!ok || dbName.isEmpty()) {
        return;
    }

    if (!dbName.endsWith(".db", Qt::CaseInsensitive)) {
        dbName += ".db";
    }

    QString path = folderPath + "/" + dbName;
    createNewDbAndConnect(path);
}

void DatabaseSettingsWidget::onBecomeActive() {
    ui->infoText->setText("Вы можете выбрать другой файл с заметками");
}

DatabaseSettingsWidget::~DatabaseSettingsWidget()
{
    delete ui;
}
