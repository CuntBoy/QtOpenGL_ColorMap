#include "colormapwidget.h"

ColorMapWidget::ColorMapWidget(QWidget *parent)
    : WindowCenterWidget(parent)
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
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}
