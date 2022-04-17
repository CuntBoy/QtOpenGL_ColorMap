#include <base/mainwindow.h>
#include <QApplication>
#include <colormap/colormap.h>
#include <colormap/colormapdata.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    ColorMap widget;

    // 创建新的线程构建数据
    // TODO
    // ColorMapData data;
    const std::shared_ptr<ColorMapData> data(new ColorMapData());

    widget.colorMap(data);

    widget.show();

    return QApplication::exec();
}
