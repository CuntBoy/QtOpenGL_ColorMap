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
    initializeOpenGLFunctions();
    // ��������ʹ�õ���Դ
    m_vertexBuffer = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    m_indexBuffer = new QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
    m_arrayBuffer = new QOpenGLVertexArrayObject;


                                       


    // ����Ȳ���
    glEnable(GL_DEPTH_TEST);

}

void ColorMapWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
    // glViewport(10, 10, w/2.0, h/2.0);
    // ����֡�����С 


}

void ColorMapWidget::paintGL()
{
    glViewport(10, 10, width() / 2.0, height() / 2.0);
    glClearColor(0.4, 0.3, 0.5, 1.0);
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
