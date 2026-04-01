#include "mainwindow.h"
#include "database.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    if (!Database::instance().connectDatabase()) {
        qDebug() << "Не удалось подключиться к БД.";
        return -1;
    }

    MainWindow w;
    w.show();
    return a.exec();
}
