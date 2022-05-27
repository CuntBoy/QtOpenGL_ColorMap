#ifndef CM_COLOR_SCALE_H
#define CM_COLOR_SCALE_H

#include <base/colorscale.h>

// draw Color Scale
// TODO make it  hover on RenderWidget

class CMColorScale final : public ColorScale
{
public:
    CMColorScale(QWidget* parent = nullptr);
    ~CMColorScale() override;



};

#endif // CMCOLORSCALE_H
