#include "mainwindow.h"
#include <QApplication>
#include <colormap/colormap.h>
#define COLORMAP_TEST

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    ColorMap colormap_widget;

#ifdef COLORMAP_TEST
    // 创建绘图的数据
    colormap_widget.colormap();
#endif
    colormap_widget.show();

    return a.exec();
}
