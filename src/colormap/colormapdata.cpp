#include "colormapdata.h"
#include <QDebug>

ColorMapData::ColorMapData()
    :DrawData()
{
    initialize();
    resizeVerticesData(0);
    resizeIndicesData(0);

}

ColorMapData::ColorMapData(const int length_x, const int length_y, const double* data_)
    :DrawData()
{
    initialize();
    Q_UNUSED(length_x)
    Q_UNUSED(length_y)
    Q_UNUSED(data_)
}

ColorMapData::ColorMapData(const std::vector<float>& x, const std::vector<float>& y, const std::vector<float>& z)
    : DrawData()
    , m_inputXData(0)
    , m_inputYData(0)
    , m_inputZData(0)
    , m_xData(0)
    , m_yData(0)
{
    // 初始化数组的大小
    resizeVerticesData();
    resizeIndicesData();

    // 记录传入的数据 
    saveDrawData(x, y, z);

    // 生成绘制的边界数据
    generateBoundaryData();

    // 生成绘制数据  - 输出数据和索引 
    generateDrawData();
    generateIndexData();

}

ColorMapData::~ColorMapData()
{
    m_inputXData.clear();
    m_inputYData.clear();
    m_inputZData.clear();
    m_xData.clear();
    m_yData.clear();

}


void ColorMapData::saveDrawData(const std::vector<float>& x, const std::vector<float>& y, const std::vector<float>& z)
{
    m_inputXData.clear();
    m_inputYData.clear();
    m_inputZData.clear();

    m_inputXData.reserve(x.size());
    m_inputYData.reserve(y.size());
    m_inputZData.reserve(z.size());

    m_inputXData.insert(m_inputXData.end(), x.begin(), x.end());
    m_inputYData.insert(m_inputYData.end(), y.begin(), y.end());
    m_inputZData.insert(m_inputZData.end(), z.begin(), z.end());
}

void ColorMapData::generateDrawData()
{
    // 生成顶点数据 - XYZ RGBA 每一个顶点有七个属性
    // Z中的值 按列存储
    // 按列存取
    // 数据的第一列

    if(m_xData.size() < 2 || m_yData.size() < 2)
    {
        // 生成其他类型的数据 
        // TODO
        return;
    }

    m_vertices.reserve(m_xData.size() * m_yData.size() * 7);
    for(int column = 0;column < m_xData.size();column ++)  // NOLINT(clang-diagnostic-sign-compare)
    {
        for(int row = 0;row < m_yData.size();row++)  // NOLINT(clang-diagnostic-sign-compare)
        {
            std::vector<float> pos; pos.reserve(7);
            pos.push_back(m_xData.at(column));
            pos.push_back(m_yData.at(row));
            int yPos = (row - 1);
            yPos = yPos == -1 ? 0 : yPos;
            int xPos = column - 1;
            xPos = xPos == -1 ? 0 : xPos;
            pos.push_back(m_inputZData.at(yPos * xPos + yPos));
            // 插入颜色数据
            pos.insert(pos.end(), {1.0,1.0,1.0,1.0});
            std::copy(pos.cbegin(), pos.cend(), m_vertices.end());
        }
    }
}

void ColorMapData::generateIndexData()
{
    //生成索引数据
    const int column = static_cast<int>(m_xData.size());
    const int row = static_cast<int>(m_yData.size());

    for (int i = 0; column - 1 > i; i++)
    {
        for (int j = 0; row - 1 > j; j++)
        {
            m_indices.push_back(i*j + j);
            m_indices.push_back((i+1)*j + j);
            m_indices.push_back((i+1)*(j+1) + j);

            m_indices.push_back(i * j + j);
            m_indices.push_back((i+1) * (j+1) + j);
            m_indices.push_back(i * j + j);
        }
    }


}

void ColorMapData::initialize()
{
    m_inputXData.clear();
    m_inputYData.clear();
    m_inputZData.clear();

    m_xData.clear();
    m_yData.clear();
}

void ColorMapData::generateBoundaryData()
{
    calculateBoundary(m_inputXData, m_xData);
    calculateBoundary(m_inputYData, m_yData);

}

