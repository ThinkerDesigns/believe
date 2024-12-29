#include <QApplication>
#include "weatherwidget.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    WeatherWidget w;
    w.show();

    return a.exec();
}
