#include <memory>
#include <QApplication>
#include <base/mainwindow.h>
#include "colormap/colormap.h"
#include "colormap/colormapdata.h"

using std::make_shared;
using std::make_unique;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    const auto widget = make_unique<ColorMap>();

    widget->setWindowTitle("Color Map Widget");
    widget->resize(1000,800);

    // create data to render widget
    const auto data = std::make_shared<ColorMapData>();

    //set render data to widget
    widget->colorMap(data);

    widget->show();
    
    return QApplication::exec();
}
