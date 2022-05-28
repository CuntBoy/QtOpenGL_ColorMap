#ifndef COLOR_MAP_WIDGET_H
#define COLOR_MAP_WIDGET_H

#include <base/windowcenterwidget.h>
#include <QWidget>
#include <base/drawdata.h>
#include <QMatrix4x4>
#include <array>

// color map center widget

class QOpenGLBuffer;
class QOpenGLVertexArrayObject;
class QOpenGLTexture;
class QOpenGLShaderProgram;

namespace TESTSpace
{

};


class ColorMapWidget final : public WindowCenterWidget
{
    //    Q_OBJECT
public:
    explicit ColorMapWidget(QWidget* parent = nullptr);
    ColorMapWidget(const ColorMapWidget&) = delete;
    ColorMapWidget(const ColorMapWidget&&) = delete;
    ColorMapWidget& operator=(const ColorMapWidget&) = delete;
    ColorMapWidget& operator=(const ColorMapWidget&&) = delete;

    void colorMapData(const std::shared_ptr<DrawData>& data);

    ~ColorMapWidget() override;

private:
    std::weak_ptr<DrawData>  m_drawData;

    // render buffer
    QOpenGLBuffer* m_imageVertexBuffer{ nullptr };
    QOpenGLBuffer* m_imageIndexBuffer{ nullptr };
    QOpenGLVertexArrayObject* m_imageArrayBuffer{ nullptr };

    QOpenGLBuffer* m_axesVertexBuffer{ nullptr };
    QOpenGLBuffer* m_axesIndexBuffer{ nullptr };
    QOpenGLVertexArrayObject* m_axesArrayBuffer{ nullptr };

    // shader program
    QOpenGLShaderProgram* m_imageShaderProgram{ nullptr };
    QOpenGLShaderProgram* m_axesLineShaderProgram{ nullptr };

    // shared with two thread
    QOpenGLTexture* m_texture{ nullptr };  // save off screen result

    // transform matrix
    QMatrix4x4 m_model;
    QMatrix4x4 m_view;
    QMatrix4x4 m_projection;

    std::shared_ptr<std::array<float, 42>> m_testData;

protected:
    void initialize();   // initialize
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int w, int h) override;

private:
    void initGlImageResource();
    void initGlAxesResource();

    void drawImage();
    void drawAxes();
    void drawRect() const;
};



#endif // COLOR_MAP_WIDGET_H
