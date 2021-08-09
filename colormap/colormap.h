#ifndef COLORMAP_H
#define COLORMAP_H

#include "mainwindow.h"
#include "drawdata.h"
#include <iostream>

// 绘图窗口

class ColorMap final : public MainWindow
{
    Q_OBJECT
public:
    explicit ColorMap(QWidget * parent_ = nullptr);
    ~ColorMap() override;

    // 绘制图形的函数-- 会将构建好的数据 设置给 center widget(QOpenglWidget 进行初始化)
    void colormap(const std::shared_ptr<DrawData> data_);

private:
    std::shared_ptr<DrawData> colormap_data_;

signals:



};



#endif // COLORMAP_H
