#include <QWidget>
#include <colormap/colormap.h>
#include <colormap/colormapdata.h>

#if 0
// 创建绘图的数据
std::shared_ptr<ColorMapData> data;

// 绘图窗口
std::shared_ptr<ColorMap> widget;

std::shared_ptr<ColorMap> example_one()
{
    // 创建窗口对象
    widget.reset(new ColorMap);
    data.reset(new ColorMapData);

    // 将数据设置给OPenGL
    widget->colormap(data.get());

    return widget;
}
#endif
