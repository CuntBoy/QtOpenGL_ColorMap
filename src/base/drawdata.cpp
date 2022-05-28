#include "drawdata.h"
#include <QDebug>

DrawData::DrawData()
{
    // 初始化数组
    m_vertices.clear();
    m_indices.clear();
}

DrawData::~DrawData()
{
    m_vertices.clear();
    m_indices.clear();
}

void DrawData::resizeVerticesData(const uint64_t data_size)
{
    if(data_size == 0)
    {
        m_vertices.clear();
        return ;
    }
    m_vertices.resize(data_size);
}

std::vector<float>& DrawData::verticesData()
{
    return m_vertices;
}

#if 0
float *DrawData::verticesData()
{
    return m_vertices.data();
}
#endif 

void DrawData::resizeIndicesData(const uint64_t data_size)
{
    if(data_size == 0)
    {
        m_indices.clear();
        return ;
    }
    m_indices.resize(data_size);
}

std::vector<unsigned>& DrawData::indicesData()
{
    return m_indices;
}

#if 0
unsigned int *DrawData::indicesData()
{
    return m_indices.data();
}
#endif 

void DrawData::calculateBoundary(const double *dst_, double *target_, const int len)
{
    // 使用传如的数据生成一组新的数据

    if(len == 1)  //只有一个数
    {
        return ;
    }

    target_[0] = dst_[0] - (dst_[1] - dst_[0]) / 2.0;

    for(auto i = 1;i < len;i++)
    {
        target_[i] = dst_[i -1] + (dst_[i] -dst_[i-1]) / 2.0;
    }

    target_[len] = dst_[len - 1] + (dst_[len -1] - dst_[len - 2])/2.0;

}

void DrawData::calculateBoundary(const std::vector<float>& input, std::vector<float>& out)
{
    if (input.size() <= 1)
        return;
    out.clear();

    // 创建数据
    out.reserve(input.size() + 1);

    out.push_back(input.at(0) - (input.at(1) - input.at(0)) /2.0f);

    for(auto it = input.cbegin() + 1;it != input.cend();++it)
    {
        const auto preItem = *--it;
        out.push_back(preItem + (*it - preItem) / 2.0f);
    }

    // 最后一个元素 
    const auto last = input.back();
    const auto lastSecond = input.at(input.size() - 1);
    out.push_back(last + (last - lastSecond) / 2.0f);
}

void DrawData::showData(const double *data, const int len)
{
    for(auto i = 0;i < len;i++)
    {
        qDebug()<<data[i]<< Qt::endl;
    }
}


#if 0
template<typename T1, typename T2>
static void DrawData::calculateBoundary(const T1 *dst_, T1 *target_, const T2 len)
{
    // 使用传如的数据生成一组新的数据

    if(len == 1)  //只有一个数
    {
        return ;
    }

    target_[0] = dst_[0] - (dst_[1] - dst_[0]) / 2.0;

    for(auto i = 1;i < len - 1;i++)
    {
        target_[i] = dst_[i -1] + (dst_[i] -dst_[i-1]) / 2.0;
    }

    target_[len] = dst_[len - 1] + (dst_[len -1] - dst_[len - 2])/2.0;
}
#endif
