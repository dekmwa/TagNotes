#include "src/mainwindow.h"
#include "src/database.h"
#include <QApplication>
#include <QSettings>
#include <QDirIterator>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // === ДИАГНОСТИКА РЕСУРСОВ ===
    qDebug() << "=== Проверка ресурсов ===";

    // Список всех ресурсов
    QDirIterator it(":", QDirIterator::Subdirectories);
    bool found = false;
    while (it.hasNext()) {
        QString res = it.next();
        qDebug() << "Ресурс:" << res;
        if (res == ":/themes/dark.qss") {
            found = true;
            qDebug() << ">>> НАШЁЛ! <<<";
        }
    }

    if (!found) {
        qDebug() << "Файл :/themes/dark.qss НЕ НАЙДЕН в ресурсах!";
        qDebug() << "Проверьте:";
        qDebug() << "1. Файл themes/dark.qss существует";
        qDebug() << "2. В resources.qrc правильный путь";
        qDebug() << "3. Вы пересобрали проект (Run CMake -> Rebuild)";
    }

    // Попытка открыть
    QFile theme(":/themes/dark.qss");
    if (theme.open(QFile::ReadOnly)) {
        QString styleSheet = QTextStream(&theme).readAll();
        a.setStyleSheet(styleSheet);
        qDebug() << "Тема успешно загружена! Размер:" << styleSheet.size();
        theme.close();
    } else {
        qDebug() << "Ошибка открытия:" << theme.errorString();
    }

    QFile colorTheme(":/themes/dark.qss");
    if (colorTheme.open(QFile::ReadOnly)) {
        QString styleSheet = QTextStream(&colorTheme).readAll();
        a.setStyleSheet(styleSheet);
        colorTheme.close();
    } else {
        qDebug() << "main: Не удалось загрузить цветовую тему из ресурсов.";
    }

    QSettings config("config.ini", QSettings::IniFormat);
    QString databasePath = config.value("Database/path").toString();
    if (!Database::instance().connectDatabase(databasePath)) {
        qDebug() << "Не удалось подключиться к БД по пути из config.ini.";
    }

    MainWindow w;
    w.show();
    return a.exec();
}
