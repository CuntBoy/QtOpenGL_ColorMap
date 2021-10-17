#ifndef COLORMAPWIDGET_H
#define COLORMAPWIDGET_H

// #define TEST_VIEWPORT
#include "base/windowcenterwidget.h"
#include <QWidget>
#include <QSize>
#include <base/drawdata.h>

// color map center widget

class ColorMapWidget final: public WindowCenterWidget
{
    Q_OBJECT
public:
    explicit ColorMapWidget(QWidget *parent = nullptr);
    void colormapData(DrawData*data_);

protected:
    void initialize();   // 初始化
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

private:
    QSize view_port_size;
    int view_port_x;
    int view_port_y;

    DrawData* colormap_data;

signals:

};



#endif // COLORMAPWIDGET_H
