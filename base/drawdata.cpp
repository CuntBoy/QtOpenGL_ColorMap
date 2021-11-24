#include "drawdata.h"
#include <QDebug>

DrawData::DrawData()
{
    // 初始化数组
    vertices_.clear();
    indices_.clear();
}

DrawData::~DrawData()
{
    vertices_.clear();
    indices_.clear();
}

void DrawData::resizeVerticesData(uint64_t dataSize)
{
    if(dataSize == 0)
    {
        vertices_.clear();
        return ;
    }
    vertices_.resize(dataSize);
}

double *DrawData::verticesData()
{
    return vertices_.data();
}

void DrawData::resizeIndicesData(uint64_t dataSize)
{
    if(dataSize == 0)
    {
        indices_.clear();
        return ;
    }
    indices_.resize(dataSize);
}

unsigned int *DrawData::indicesData()
{
    return indices_.data();
}

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

void DrawData::showData(const double *data, int len)
{
    for(auto i = 0;i < len;i++)
    {
        qDebug()<<data[i]<<endl;
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
