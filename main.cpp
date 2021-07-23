#include "mainwindow.h"

#include <QApplication>

#include <colormap/colormap.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    ColorMap colormap_widget;
    colormap_widget.show();

    return a.exec();
}
