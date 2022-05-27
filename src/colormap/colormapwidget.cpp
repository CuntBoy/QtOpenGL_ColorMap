#include "colormapwidget.h"

#include <iostream>
#include <QPainter>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLTexture>
#include <QOpenGLShaderProgram>

// test data
std::array<float,42> vertices {
        -1.0,-1.0,0.0,0.0,0.0,0.0,0.0,
        1.0,-1.0,0.0,0.0,0.0,0.0,0.0,
        -1.0,1.0,0.0,0.0,0.0,0.0,0.0,

        1.0,-1.0,0.0,0.0,0.0,0.0,0.0,
        1.0,1.0,0.0,0.0,0.0,0.0,0.0,
        -1.0,1.0,0.0,0.0,0.0,0.0,0.0
    };

ColorMapWidget::ColorMapWidget(QWidget* parent)
    : WindowCenterWidget(parent)
    , m_vertexBuffer(new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer))
    , m_indexBuffer(new QOpenGLBuffer(QOpenGLBuffer::IndexBuffer))
    , m_arrayBuffer(new QOpenGLVertexArrayObject())
    , m_shaderProgram(new QOpenGLShaderProgram)
    , m_texture(new QOpenGLTexture(QOpenGLTexture::Target2D)) // 2D 纹理
    , m_testData(std::make_shared<std::array<float,42>>(vertices))    // 创建多个窗口的时候会报错 TODO
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
    using std::cout;
    using std::endl;

    makeCurrent();
    initializeOpenGLFunctions();

    m_vertexBuffer->create();
    m_indexBuffer->create();
    m_arrayBuffer->create();

    m_arrayBuffer->bind();
    m_vertexBuffer->bind();

    m_vertexBuffer->allocate(m_testData.get()->data(),sizeof(float) * m_testData.get()->size());
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,sizeof(float) * 7,nullptr);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1,4,GL_FLOAT,GL_FALSE,sizeof(float) * 7,reinterpret_cast<void*>(sizeof(float) * 4));

    m_vertexBuffer->release();
    m_arrayBuffer->release();

    // create shader program
    m_shaderProgram->addCacheableShaderFromSourceFile(QOpenGLShader::Vertex,":shaders/shaders/vertexShader/gl_image.vert");
    m_shaderProgram->addCacheableShaderFromSourceFile(QOpenGLShader::Fragment,":shaders/shaders/fragmentshader/gl_image.frag");

    const auto result = m_shaderProgram->link();
    if(!result)
    {
        cout << m_shaderProgram->log().toStdString() << endl;
    }
    cout<<"link success!"<<endl;

    // depth test
    glEnable(GL_DEPTH_TEST);

}

void ColorMapWidget::paintGL()
{
    // glViewport(10, 10, width() / 2.0, height() / 2.0);
    glClearColor(0.4f, 0.3f, 0.5f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    m_shaderProgram->bind();
    m_arrayBuffer->bind();
    m_shaderProgram->setUniformValue("model",m_model);
    m_shaderProgram->setUniformValue("view",m_view);
    m_shaderProgram->setUniformValue("projection",m_projection);
    glDrawArrays(GL_TRIANGLES,0,6);

}

void ColorMapWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
    // 设置帧缓冲大小
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
