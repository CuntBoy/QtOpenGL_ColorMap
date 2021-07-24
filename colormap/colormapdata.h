#ifndef COLORMAPDATA_H
#define COLORMAPDATA_H

#include <drawdata.h>

class ColorMapData : public DrawData
{
public:
    ColorMapData();
    ColorMapData(const double * xdata,const double * ydata,int xlen,int ylen,const double * zdata);
    ColorMapData(const int xsize,const int ysize,const double * data_);
};

#endif // COLORMAPDATA_H
