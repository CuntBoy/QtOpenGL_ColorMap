#ifndef COLORMAPWIDGET_H
#define COLORMAPWIDGET_H

#include "windowcenterwidget.h"
#include <QWidget>

// color map center widget

class ColorMapWidget final: public WindowCenterWidget
{
    Q_OBJECT
public:
    explicit ColorMapWidget(QWidget *parent = nullptr);

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

signals:

};

#endif // COLORMAPWIDGET_H
