#include <QWidget>
#include <colormap/colormap.h>
#include <colormap/colormapdata.h>

// 创建绘图的数据
std::shared_ptr<ColorMapData> data; // (new ColorMapData);
std::shared_ptr<ColorMap> widget;

std::shared_ptr<ColorMap> example_one()
//ColorMap* example_one()
{
    // 创建窗口对象
    //std::shared_ptr<ColorMap> widget(new ColorMap);
    widget.reset(new ColorMap);
    data.reset(new ColorMapData);

    // 将数据设置给OPenGL
    widget->colormap(data.get());

    return widget;
}
