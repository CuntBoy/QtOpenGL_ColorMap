#ifndef COLOR_MAP_H
#define COLOR_MAP_H

#include <base/drawdata.h>
#include <base/mainwindow.h>
#include <colormap/colormapcolorscale.h>

#include "colormapdata.h"

// 绘图窗口 -- main Window
// 创建对应的菜单一起其他的东西 

class ColorMap final : public MainWindow
{
    Q_OBJECT
public:
    explicit ColorMap(QWidget * parent_ = nullptr);
    ~ColorMap() override;

    ColorMap(const ColorMap&) = delete;
    ColorMap(const ColorMap&&) = delete;

    ColorMap& operator=(const ColorMap&) = delete;
    ColorMap& operator=(const ColorMap&&) = delete;

    // 绘制图形的函数-- 会将构建好的数据 设置给 center widget(QOpenGLWidget 进行初始化)
    void colorMap(const std::shared_ptr<ColorMapData>& data_) const;  // 外部绘图的接口  -- 在show之前调用

private:
    std::shared_ptr<ColorMapData> m_colorMapData;      // 绘图的数据
    CMColorScale * m_colorScale;   // ColorScale

signals:


};



#endif // COLORMAP_H
