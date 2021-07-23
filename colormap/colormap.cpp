#include "colormap.h"
#include "colormapwidget.h"


ColorMap::ColorMap(QWidget * parent_)
    : MainWindow(parent_)
{
    center_window = new ColorMapWidget(this);
    center_window->setAutoFillBackground(true);
    this->setCentralWidget(center_window);
}

ColorMap::~ColorMap()
{

}
