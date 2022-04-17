#ifndef COLOR_MAP_DATA_H
#define COLOR_MAP_DATA_H

#include <base/drawdata.h>

// 绘制 color map 的数据

class ColorMapData : public DrawData
{

public:
    ColorMapData();

    ColorMapData(const int length_x, const int length_y, const double* data_);
    ColorMapData(const std::vector<float>& x, const std::vector<float>& y, const std::vector<float>& z);

    ColorMapData(const ColorMapData&) = delete;
    ColorMapData(const ColorMapData&&) = delete;
    ColorMapData& operator=(const ColorMapData&) = delete;
    ColorMapData& operator=(const ColorMapData&&) = delete;

    ~ColorMapData();

protected:
    void initialize();
    void generateBoundaryData();
    void saveDrawData(const std::vector<float>& x, const std::vector<float>& y, const std::vector<float>& z);

    // 生成绘制的数据 
    void generateDrawData();

private:
    // 使用STL      -- 三个方向上的数据
    // m_zdata.size() = m_xdata.size() * m_ydata.size()
    std::vector<float> m_inputXData;
    std::vector<float> m_inputYData;
    std::vector<float> m_inputZData;

    // 通过计算生成一组新的X的data Y的data,Z依旧是曲原先的值 
    // new x data & y data(最终使用此部分的数据生成绘图的数据)
    std::vector<float> m_xData;
    std::vector<float> m_yData;

};

#endif // COLORMAPDATA_H
