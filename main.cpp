#include "base/mainwindow.h"
#include <QApplication>
#include <colormap/colormap.h>
#include <colormap/colormapdata.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    ColorMap widget;
    ColorMapData data;
    widget.colormap(&data);
    widget.show();

    return a.exec();
}
