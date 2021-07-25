#include <QWidget>
#include <colormap/colormap.h>
#include <colormap/colormapdata.h>

//std::shared_ptr<ColorMap> example_one()
ColorMap* example_one()
{
    // 创建窗口对象
    //std::shared_ptr<ColorMap> widget(new ColorMap);
    auto widget = new ColorMap;

    // 创建绘图的数据
    std::shared_ptr<ColorMapData> data(new ColorMapData);

    // 将数据设置给OPenGL
    widget->colormap(data);

    return widget;
}
