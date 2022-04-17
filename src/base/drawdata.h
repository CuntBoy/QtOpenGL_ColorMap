#ifndef DRAW_DATA_H
#define DRAW_DATA_H

// 数据类 -- 存储并组织了所有的数据
// 绘图的时候只需要将此数据类的指针 共享给显示图像的窗口

#include <iostream>
#include <vector>

class DrawData
{
public:
    DrawData();
    ~DrawData();
    DrawData(const DrawData&) = delete;
    DrawData(const DrawData&&) = delete;
    DrawData& operator=(const DrawData&) = delete;
    DrawData& operator=(const DrawData&&) = delete;

    // 重新设置顶点数据-vector的大小 -- 默认置空
    void resizeVerticesData(uint64_t data_size = 0);
    // 获取顶点数据的指针
    // float * verticesData();
    std::vector<float>& verticesData();

    // 重新设置缩影数据-vector的大小
    void resizeIndicesData(uint64_t data_size = 0);
    // 获取索引数据的指针
    // unsigned int * indicesData();
    std::vector<unsigned int>& indicesData();

    // 计算绘制的数据 
    static void calculateBoundary(const double* dst_, double* target_, const int len);

    //计算新的边界数据 
    static void calculateBoundary(const std::vector<float>& input, std::vector<float>& out);

    static void showData(const double* data, int len);

protected:
    //绘制的数据和索引
    std::vector<float> m_vertices;        // 顶点数据
    std::vector<unsigned int> m_indices;   // 顶点的索引数据
};

#endif // DRAWDATA_H
