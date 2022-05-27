#include <base/mainwindow.h>
#include <QApplication>
#include "colormap/colormap.h"
#include "colormap/colormapdata.h"
#include <memory>

using std::make_shared;
using std::unique_ptr;
using std::shared_ptr;
using std::make_unique;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    unique_ptr<ColorMap> widget = make_unique<ColorMap>();

    widget->setWindowTitle("Color Map Widget");
    widget->resize(1000,800);

    // create data to render widget
    const std::shared_ptr<ColorMapData> data = std::make_shared<ColorMapData>();

    //set render data to widget
    widget->colorMap(data);

    widget->show();
    
    return QApplication::exec();
}
