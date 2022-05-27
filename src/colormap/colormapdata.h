#ifndef COLOR_MAP_DATA_H
#define COLOR_MAP_DATA_H

#include <base/drawdata.h>

// draw color map data

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

    // generate draw data
    void generateDrawData();
    void generateIndexData();

private:
    std::vector<float> m_inputXData;
    std::vector<float> m_inputYData;
    std::vector<float> m_inputZData;

    std::vector<float> m_xData;
    std::vector<float> m_yData;

};

#endif // COLORMAPDATA_H
