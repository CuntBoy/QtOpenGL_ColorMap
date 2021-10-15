#include "colormap.h"
#include "colormapwidget.h"

#include <QLayout>


ColorMap::ColorMap(QWidget * parent_)
    : MainWindow(parent_)
{
    center_window = new ColorMapWidget(this);
    center_window->setAutoFillBackground(true);
    this->setCentralWidget(center_window);
    auto layout = this->layout();
    layout->setMargin(0);

    // 设置最小的宽高
    center_window->setMinimumSize(640,480);
    center_window->resize(640,480);
}

ColorMap::~ColorMap()
{

}

void ColorMap::colormap(DrawData* data_)
{
    colormap_data_ = data_;
    auto centerWidget = static_cast<ColorMapWidget *>(this->centralWidget());
    centerWidget->colormapData(colormap_data_);
}

