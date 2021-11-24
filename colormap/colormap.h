#ifndef COLORMAP_H
#define COLORMAP_H

#include "colormapcolorscale.h"
#include <base/mainwindow.h>
#include <base/drawdata.h>

// 绘图窗口 -- main Window

class ColorMap final : public MainWindow
{
    Q_OBJECT
public:
    explicit ColorMap(QWidget * parent_ = nullptr);
    ~ColorMap() override;

    // 绘制图形的函数-- 会将构建好的数据 设置给 center widget(QOpenglWidget 进行初始化)
    void colormap(DrawData* data_);  // 外部绘图的接口  -- 在show之前调用

private:

    DrawData* colormap_data_;      // 绘图的数据
    CMColorScale * color_scale_;   // ColorScale

signals:



};



#endif // COLORMAP_H
