#ifndef COLOR_MAP_H
#define COLOR_MAP_H

#include <base/drawdata.h>
#include <base/mainwindow.h>
#include <colormap/colormapcolorscale.h>

#include "colormapdata.h"

// render widget -- main Window
// create menu

class ColorMap final : public MainWindow
{
    //Q_OBJECT
public:
    explicit ColorMap(QWidget* parent_ = nullptr);
    ~ColorMap() override;

    ColorMap(const ColorMap&) = delete;
    ColorMap(const ColorMap&&) = delete;

    ColorMap& operator=(const ColorMap&) = delete;
    ColorMap& operator=(const ColorMap&&) = delete;

    void colorMap(const std::shared_ptr<ColorMapData> & data_) const;  // the API of render   -- call before widget show

private:
    mutable std::weak_ptr<ColorMapData> m_colorMapData{};      // draw data
    CMColorScale* m_colorScale;                                // ColorScale

//signals:


};



#endif // COLORMAP_H
