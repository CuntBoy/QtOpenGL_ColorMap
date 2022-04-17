#include <colormap/colormap.h>
#include <colormap/colormapwidget.h>


ColorMap::ColorMap(QWidget* parent_)
    : MainWindow(parent_)
    , m_colorMapData(nullptr)
    , m_colorScale(new CMColorScale)
{
    m_centerWindow = new ColorMapWidget(this);  // 创建绘图窗口
    m_centerWindow->setAutoFillBackground(true);
    this->setCentralWidget(m_centerWindow);

    // 设置最小的宽高
    m_centerWindow->setMinimumSize(640, 480);
    m_centerWindow->resize(640, 480);
}

ColorMap::~ColorMap()                    
{
    if (m_colorScale)
    {
        delete m_colorScale;
        m_colorScale = nullptr;
    }

}

// 绘图函数
void ColorMap::colorMap(const std::shared_ptr<ColorMapData>& data_) const
{
    // m_colorMapData = data_;
    const auto centerWidget = dynamic_cast<ColorMapWidget*>(m_centerWindow);
    centerWidget->colorMapData(data_);
}

