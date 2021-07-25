#ifndef COLORMAPDATA_H
#define COLORMAPDATA_H

#include <drawdata.h>

class ColorMapData : public DrawData
{
public:

    ColorMapData();
    ColorMapData(const double * xdata,const double * ydata,int xlen,int ylen,const double * zdata);
    ColorMapData(const int xsize,const int ysize,const double * data_);

    void saveDrawData(const double * xdata,const double * ydata,const double * zdata,int xlen,int ylen);

protected:
    void initialize();

private:
    // 存储绘制的是数据  -- 只在此存一份
    double * x_data_;    // X轴上的数据
    double * y_data_;    // Y轴上的数据
    double * z_data_;    // 绘图时候使用的数据
    int x_len_;           // X轴上数据的个数
    int y_len_;          // Y轴上数据的个数

};

#endif // COLORMAPDATA_H
