#include "src/mainwindow.h"
#include "src/database.h"
#include <QApplication>
#include <QSettings>
#include <QDirIterator>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFile colorTheme(":/themes/light.qss");
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
