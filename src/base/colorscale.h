#ifndef COLORSCALE_H
#define COLORSCALE_H

#include <QWidget>

// color scale -- 颜色窗口 -- 用于绘制显示的Color Bar

class ColorScale: public QWidget
{
    // Q_OBJECT
public:
    explicit ColorScale(QWidget *parent = nullptr);
    ~ColorScale() override;

signals:

};

#endif // COLORSCALE_H
