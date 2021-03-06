#ifndef WINDOWCENTERWIDGET_H
#define WINDOWCENTERWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions_4_5_Core>

//OpenGL render widget
class WindowCenterWidget : public QOpenGLWidget, protected QOpenGLFunctions_4_5_Core
{
    // Q_OBJECT
public:
    explicit WindowCenterWidget(QWidget* parent = nullptr);

    WindowCenterWidget(const WindowCenterWidget&) = delete;
    WindowCenterWidget(const WindowCenterWidget&&) = delete;
    WindowCenterWidget& operator=(const WindowCenterWidget&) = delete;
    WindowCenterWidget& operator=(const WindowCenterWidget&&) = delete;

    ~WindowCenterWidget() override = default;
};

#endif // WINDOWCENTERWIDGET_H
