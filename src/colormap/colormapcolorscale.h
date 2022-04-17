#ifndef CM_COLOR_SCALE_H
#define CM_COLOR_SCALE_H

#include <base/colorscale.h>

// 用于绘制 Color Scale

class CMColorScale final : public ColorScale
{
public:
    CMColorScale(QWidget * parent = nullptr);
    ~CMColorScale() override;
};

#endif // CMCOLORSCALE_H
