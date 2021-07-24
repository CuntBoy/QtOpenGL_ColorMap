#ifndef DRAWDATA_H
#define DRAWDATA_H

// 数据类 -- 存储并组织了所有的数据
// 绘图的时候只需要将此数据类的指针 共享给显示图像的窗口

#include <iostream>
#include <algorithm>
#include <vector>

class DrawData
{
public:
    DrawData();
    ~DrawData();

    // 重新设置顶点数据-vector的大小
    void resizeVerticesData(uint64_t dataSize);
    // 获取顶点数据的指针
    double * verticesData();

    // 重新设置缩影数据-vector的大小
    void resizeIndicesData(uint64_t dataSize);
    // 获取索引数据的指针
    unsigned int * indicesData();

protected:
    std::vector<double> vertices_;        // 顶点数据
    std::vector<unsigned int> indices_;   // 顶点的索引数据
};

#endif // DRAWDATA_H
