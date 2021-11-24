#include "colormap.h"
#include "colormapwidget.h"

#include <QLayout>


ColorMap::ColorMap(QWidget * parent_)
    : MainWindow(parent_),
    colormap_data_(nullptr),
    color_scale_(nullptr)
{
    center_window = new ColorMapWidget(this);  // 创建绘图窗口
    center_window->setAutoFillBackground(true);

    color_scale_ = new CMColorScale;

    auto hbox = new QHBoxLayout(this);
    hbox->addWidget(center_window);
    hbox->setSpacing(3);
    hbox->addWidget(color_scale_);
    hbox->setMargin(1);

    color_scale_->setFixedWidth(129);
    color_scale_->setVisible(false);

    const auto widget = new QWidget;
    widget->setLayout(hbox);
    setCentralWidget(widget);

    // 设置最小的宽高
    center_window->setMinimumSize(640,480);
    center_window->resize(640,480);
}

ColorMap::~ColorMap()
{
    if(color_scale_)
    {
        delete color_scale_;
        color_scale_ = nullptr;
    }
    if(colormap_data_)
    {
        delete colormap_data_;
        colormap_data_ = nullptr;
    }
}

// 绘图函数
void ColorMap::colormap(DrawData* data_)
{
    colormap_data_ = data_;
    auto centerWidget = static_cast<ColorMapWidget *>(center_window);
    centerWidget->colormapData(colormap_data_);
}

