#include "colormapwidget.h"

#include <math.h>
#include <iostream>
#include <QPainter>

ColorMapWidget::ColorMapWidget(QWidget *parent)
    : WindowCenterWidget(parent)
{
    initialize();
}

void ColorMapWidget::initialize()
{
    view_port_size = QSize(640,480);
    view_port_x = 0;
    view_port_y = 0;

#ifdef TEST_VIEWPORT
    test_image = QImage(":/pic/images/test_image.JPG"); // .scaled(QSize(640,480),Qt::KeepAspectRatio,Qt::SmoothTransformation);
#endif
}

void ColorMapWidget::initializeGL()
{
    makeCurrent();
    this->initializeOpenGLFunctions();
}

void ColorMapWidget::resizeGL(int w, int h)
{
    // 计算显示图形的区域
    view_port_size.setWidth(std::round(w / 3.0 * 2.0));  //向上取整
    view_port_size.setHeight(std::round(h / 3.0 * 2.0));

    view_port_x = std::round(w / 6.0);
    view_port_y = std::round(h / 6.0);

    //glViewport(0, 0, w, h);
    glViewport(view_port_x,view_port_y,view_port_size.width(),view_port_size.height());

#ifdef TEST_VIEWPORT
    // 此处会导致 失真
    test_image = test_image.scaled(QSize(w,h),Qt::KeepAspectRatioByExpanding,Qt::SmoothTransformation);
#endif

}

void ColorMapWidget::paintGL()
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClearColor(0.0,1.0,0.0,1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

#ifdef TEST_VIEWPORT
    QPainter painter(this);
    painter.begin(this);
    painter.drawImage(0,0,test_image);
    painter.end();
#endif

}