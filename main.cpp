#include "src/mainwindow.h"
#include "src/database.h"
#include <QApplication>
#include <QSettings>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QSettings config("config.ini", QSettings::IniFormat);
    QString databasePath = config.value("Database/path").toString();
    if (!Database::instance().connectDatabase(databasePath)) {
        qDebug() << "Не удалось подключиться к БД по пути из config.ini.";
    }

    MainWindow w;
    w.show();
    return a.exec();
}
