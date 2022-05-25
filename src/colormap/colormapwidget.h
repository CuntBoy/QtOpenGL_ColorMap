#ifndef COLOR_MAP_WIDGET_H
#define COLOR_MAP_WIDGET_H

#include <base/windowcenterwidget.h>
#include <QWidget>
#include <base/drawdata.h>

// color map center widget

class QOpenGLBuffer;
class QOpenGLVertexArrayObject;
class QOpenGLTexture;
class QOpenGLShaderProgram;


class ColorMapWidget final : public WindowCenterWidget
{
    Q_OBJECT
public:
    explicit ColorMapWidget(QWidget* parent = nullptr);

    ColorMapWidget(const ColorMapWidget&) = delete;
    ColorMapWidget(const ColorMapWidget&&) = delete;
    ColorMapWidget& operator=(const ColorMapWidget&) = delete;
    ColorMapWidget& operator=(const ColorMapWidget&&) = delete;

    void colorMapData(const std::shared_ptr<DrawData>& data);

    ~ColorMapWidget() override;

protected:
    void initialize();   // 初始化
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

private:
    std::shared_ptr<DrawData>  m_drawData{ nullptr };
    QOpenGLBuffer* m_vertexBuffer{ nullptr };
    QOpenGLVertexArrayObject* m_arrayBuffer{ nullptr };
    QOpenGLShaderProgram* m_shaderProgram{ nullptr };

    // 在两个线程之间共享
    QOpenGLTexture* m_texture{nullptr};  // 保存离屏渲染的结果 



};



#endif // COLORMAPWIDGET_H
