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
    , m_vertexBuffer(new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer))
    , m_indexBuffer(new QOpenGLBuffer(QOpenGLBuffer::IndexBuffer))
    , m_arrayBuffer(new QOpenGLVertexArrayObject())
    , m_shaderProgram(new QOpenGLShaderProgram)
    , m_texture(new QOpenGLTexture(QOpenGLTexture::Target2D)) // 2D 纹理 
{
    initialize();
}

void ColorMapWidget::initialize()
{
    m_model.setToIdentity();
    m_view.setToIdentity();
    m_projection.setToIdentity();

}

void ColorMapWidget::initializeGL()
{
    makeCurrent();
    initializeOpenGLFunctions();
    // 创建绘制使用的资源
    // m_vertexBuffer = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    // m_indexBuffer = new QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
    // m_arrayBuffer = new QOpenGLVertexArrayObject;

    m_vertexBuffer->create();
    m_indexBuffer->create();
    m_arrayBuffer->create();


    // 打开深度测试
    glEnable(GL_DEPTH_TEST);

}

void ColorMapWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
    // 设置帧缓冲大小 


}

void ColorMapWidget::paintGL()
{
    // glViewport(10, 10, width() / 2.0, height() / 2.0);
    glClearColor(0.4f, 0.3f, 0.5f, 1.0f);
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
