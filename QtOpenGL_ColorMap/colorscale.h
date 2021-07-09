#ifndef COLORSCALE_H
#define COLORSCALE_H

#include <QWidget>

class ColorScale final: public QWidget
{
    Q_OBJECT
public:
    explicit ColorScale(QWidget *parent = nullptr);
    ~ColorScale() override;

signals:

};

#endif // COLORSCALE_H
