#include "colormapdata.h"
#include <QDebug>

ColorMapData::ColorMapData()
{
    resizeVerticesData(0);
    resizeIndicesData(0);

}

ColorMapData::ColorMapData(const double *xdata, const double *ydata, int xlen, int ylen, const double *zdata)
{
    // 拷贝一份是数据
    saveDrawData(xdata,ydata,zdata,xlen,ylen);
    // 计算新的X&Y的数据

    // 计算绘制的数据
}

ColorMapData::ColorMapData(const int xsize, const int ysize, const double * data_)
{

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

}

