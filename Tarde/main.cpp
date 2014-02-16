#include <QApplication>
#include "MainWindow.h"

int main(int argc, char *argv[])
{
    QApplication application(argc, argv);
    MainWindow window;

    QPalette* palette = new QPalette();
    QLinearGradient linearGradient(0, 0, 0, window.height());
    linearGradient.setColorAt(0, "#242424");
    linearGradient.setColorAt(1, "#090808");
    palette->setBrush(QPalette::Window, *(new QBrush(linearGradient)));

    window.setPalette(*palette);
    window.show();
    return application.exec();
}
