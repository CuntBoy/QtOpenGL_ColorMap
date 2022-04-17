#ifndef WINDOWCENTERWIDGET_H
#define WINDOWCENTERWIDGET_H

#include <QOpenGLFunctions>
#include <QOpenGLWidget>

//OpenGL的绘制窗口

class WindowCenterWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    explicit  WindowCenterWidget(QWidget * parent = nullptr);
    WindowCenterWidget(const WindowCenterWidget&) = delete;
    WindowCenterWidget(const WindowCenterWidget&&) = delete;
    WindowCenterWidget& operator=(const WindowCenterWidget&) = delete;
    WindowCenterWidget& operator=(const WindowCenterWidget&&) = delete;

    ~WindowCenterWidget() override = default;
};

#endif // WINDOWCENTERWIDGET_H
