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

}

void ColorMapWidget::initializeGL()
{
    makeCurrent();
    this->initializeOpenGLFunctions();
}

void ColorMapWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
}

void ColorMapWidget::paintGL()
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClearColor(0.0,1.0,0.0,1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}

void ColorMapWidget::colormapData(DrawData*  data_)
{
    colormap_data = data_;
}
