#include "colormapdata.h"
#include <QDebug>

ColorMapData::ColorMapData()
{
    resizeVerticesData(0);
    resizeIndicesData(0);

}

ColorMapData::ColorMapData(const double *xdata, const double *ydata, int xlen, int ylen, const double *zdata)
{
    // 初始化数组的大小
    resizeVerticesData();
    resizeIndicesData();

    // 拷贝一份数据
    saveDrawData(xdata,ydata,zdata,xlen,ylen);
    // 计算新的X&Y的数据
    // 设置边界数据数组的大小
    resizeBoundaryDataSize();  //大小是前面一步保存的数据的大小
    // 生成边界数据
    generateBoundaryData();
    // 计算绘制的数据 -- 使用上一步的数据生成新的数据

}

ColorMapData::ColorMapData(const int xsize, const int ysize, const double * data_)
{
    Q_UNUSED(xsize)
    Q_UNUSED(ysize)
    Q_UNUSED(data_)
}

ColorMapData::~ColorMapData()
{
    if(x_data_)
    {
        delete [] x_data_;
        x_data_ = nullptr;
    }
    if(y_data_)
    {
        delete [] y_data_;
        y_data_ = nullptr;
    }
    if(z_data_)
    {
        delete [] z_data_;
        z_data_ = nullptr;
    }

    if(x_boundary_)
    {
        delete [] x_boundary_;
        x_boundary_ = nullptr;
    }

    if(y_boundary_)
    {
        delete [] y_boundary_;
        y_boundary_ = nullptr;
    }


}

void ColorMapData::saveDrawData(const double *xdata, const double *ydata, const double *zdata, int xlen, int ylen)
{
    x_len_ = xlen;
    y_len_ = ylen;

    {
        if(x_data_)
        {
            delete [] x_data_;
            x_data_ = nullptr;
        }
        x_data_ = new double[xlen];
        if(!x_data_)
        {
            return ;
        }
        memcpy(x_data_,xdata,sizeof(double)*xlen);
    }

    {
        if(y_data_)
        {
            delete[] y_data_;
            y_data_ = nullptr;
        }
        y_data_ = new double[ylen];
        if(!y_data_)
        {
            delete [] x_data_;
            x_data_ = nullptr;
            return ;
        }
        memcpy(y_data_,ydata,sizeof(double)*ylen);
    }

    {
        if(z_data_)
        {
            delete[] z_data_;
            z_data_ = nullptr;
        }
        z_data_ = new double[ylen*xlen];
        if(!z_data_)
        {
            delete [] x_data_;
            x_data_ = nullptr;

            delete[] y_data_;
            y_data_ = nullptr;

            return ;
        }
        memcpy(z_data_,zdata,sizeof(double)*ylen*xlen);
    }

}

void ColorMapData::initialize()
{
    x_data_ = nullptr;
    y_data_ = nullptr;
    z_data_ = nullptr;
    x_len_ = 0;
    y_len_ = 0;

    x_boundary_ = nullptr;
    y_boundary_ = nullptr;

}

void ColorMapData::resizeBoundaryDataSize()
{
    // X Boundary Data
    {
        if(x_boundary_)
        {
            delete [] x_boundary_;
            x_boundary_ = nullptr;
        }

        x_boundary_ = new double[x_len_ + 1];
    }

    // Y  Boundary Data
    {
        {
            if(y_boundary_)
            {
                delete [] y_boundary_;
                y_boundary_ = nullptr;
            }

            y_boundary_ = new double[y_len_ + 1];
        }
    }

}

void ColorMapData::generateBoundaryData()
{
    calculateBoundary(x_data_,x_boundary_,x_len_);
    calculateBoundary(y_data_,y_boundary_,y_len_);
}

