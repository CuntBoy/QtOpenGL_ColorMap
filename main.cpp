#include "base/mainwindow.h"
#include <QApplication>
#include <colormap/colormap.h>
#include <colormap/colormapdata.h>
#include "example/example_one.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    std::shared_ptr<ColorMap> widget(example_one().get());
    //std::shared_ptr<ColorMap> widget(example_one());
    widget->show();

    return a.exec();
    //widget->deleteLater();
}
