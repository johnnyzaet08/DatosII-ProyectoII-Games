#include "imagegame.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ImageGame w;
    w.setWindowTitle("Image Game");
    w.resize(800, 600);
    w.show();
    return a.exec();
}
