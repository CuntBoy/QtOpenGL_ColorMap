#include "colormapwidget.h"

#include <iostream>
#include <QPainter>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLTexture>
#include <QOpenGLShaderProgram>



ColorMapWidget::ColorMapWidget(QWidget* parent)
    : WindowCenterWidget(parent)
    , m_drawData(nullptr)

{
    // initialize();
}

void ColorMapWidget::initialize()
{

}

void ColorMapWidget::initializeGL()
{
    makeCurrent();
    this->initializeOpenGLFunctions();

    // 创建绘制使用的资源



    // 打开深度测试
    glEnable(GL_DEPTH_TEST);

}

void ColorMapWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
}

void ColorMapWidget::paintGL()
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClearColor(0.0, 1.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}

void ColorMapWidget::colorMapData(const std::shared_ptr<DrawData>& data)
{
    m_drawData = data;
}

ColorMapWidget::~ColorMapWidget()
{
    m_drawData.reset();

    makeCurrent();
    if (m_vertexBuffer)
    {
        m_vertexBuffer->destroy();
        delete m_vertexBuffer;
        m_vertexBuffer = nullptr;
    }

    if (m_arrayBuffer)
    {
        m_arrayBuffer->destroy();
        delete m_arrayBuffer;
        m_arrayBuffer = nullptr;
    }

    if (m_shaderProgram)
    {
        delete m_shaderProgram;
        m_shaderProgram = nullptr;
    }

    if (m_texture)
    {
        m_texture->destroy();
        delete m_texture;
        m_texture = nullptr;
    }

    doneCurrent();

}
