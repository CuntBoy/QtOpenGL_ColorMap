#ifndef WINDOWCENTERWIDGET_H
#define WINDOWCENTERWIDGET_H

#include <QOpenGLFunctions>
#include <QOpenGLWidget>

//opengl的绘制窗口

class WindowCenterWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    WindowCenterWidget(QWidget * parent = nullptr);
};

#endif // WINDOWCENTERWIDGET_H
