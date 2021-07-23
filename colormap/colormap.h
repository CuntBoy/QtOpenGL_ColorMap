#ifndef COLORMAP_H
#define COLORMAP_H

#include "mainwindow.h"

// 绘图窗口

class ColorMap final : public MainWindow
{
    Q_OBJECT
public:
    explicit ColorMap(QWidget * parent_ = nullptr);
    ~ColorMap() override;

signals:



};



#endif // COLORMAP_H
