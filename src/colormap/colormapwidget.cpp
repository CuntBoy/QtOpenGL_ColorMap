#include "colormapwidget.h"

#include <iostream>
#include <QPainter>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLTexture>
#include <QOpenGLShaderProgram>
#include <QOpenGLContext>
#include <QOffscreenSurface>
#include <memory>
#include "base/character.h"
#include "RenderThread.h"
#include "base/character.h"
#include "ft2build.h"
#include FT_FREETYPE_H


// test data
std::array<float, 42> vertices{
    -1.0, -1.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    1.0, -1.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    -1.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0,

    1.0, -1.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    1.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    -1.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0
};

// draw axes line data
std::array<float, 18> lines_vertices
{
    -1.5, -1.5, 0.0,
    -1.5, 1.5, 0.0,

    -1.5, -1.5, 0.0,
    1.5, -1.5, 0.0,

    -1.5, 1.5, 0.0,
    1.5, -1.5, 0.0

};


ColorMapWidget::ColorMapWidget(QWidget* parent)
    : WindowCenterWidget(parent)
    , m_imageVertexBuffer(new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer))
    , m_imageIndexBuffer(new QOpenGLBuffer(QOpenGLBuffer::IndexBuffer))
    , m_imageArrayBuffer(new QOpenGLVertexArrayObject)
    , m_axesVertexBuffer(new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer))
    , m_axesIndexBuffer(new QOpenGLBuffer(QOpenGLBuffer::IndexBuffer))
    , m_axesArrayBuffer(new QOpenGLVertexArrayObject)
    , m_imageShaderProgram(new QOpenGLShaderProgram)
    , m_axesLineShaderProgram(new QOpenGLShaderProgram)
    , m_fontShaderProgram(new QOpenGLShaderProgram)
    , m_texture(new QOpenGLTexture(QOpenGLTexture::Target2D)) // 2D ����
    , m_testData(std::make_shared<std::array<float, 42>>(vertices)) // ����������ڵ�ʱ��ᱨ�� TODO
{
    initialize();
}

void ColorMapWidget::initialize()
{
    m_model.setToIdentity();
    m_view.setToIdentity();
    m_projection.setToIdentity();
    m_words.clear();
}

void ColorMapWidget::initializeGL()
{
    using std::cout;
    using std::endl;

    makeCurrent();
    initializeOpenGLFunctions();
    initRenderThread();

    initGlImageResource();
    initGlAxesResource();
    initGlFontResource();

    // ��������
#ifdef TEST_FONT

    m_words.clear();
    const auto font = std::make_shared<GlFont>();
    const auto context = QOpenGLContext::currentContext();
    font->setString("hello");
    font->createResources(*context);
    m_words.push_back(font);

#endif

    // depth test
    glEnable(GL_DEPTH_TEST);
}

void ColorMapWidget::paintGL()
{
    //    glClearColor(0.4f, 0.3f, 0.5f, 1.0f);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    drawImage();
    drawAxes();
    drawFont();

    // draw ѡ��
    drawRect();
}

void ColorMapWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
    // ����֡�����С
}

void ColorMapWidget::initGlImageResource()
{
    using std::cout;
    using std::endl;

    m_imageVertexBuffer->create();
    m_imageIndexBuffer->create();
    m_imageArrayBuffer->create();

    m_imageArrayBuffer->bind();
    m_imageVertexBuffer->bind();

    m_imageVertexBuffer->allocate(m_testData.get()->data(), sizeof(float) * m_testData.get()->size());
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 7, nullptr);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 7, reinterpret_cast<void*>(sizeof(float) * 4));

    m_imageVertexBuffer->release();
    m_imageArrayBuffer->release();

    // create shader program
    m_imageShaderProgram->addCacheableShaderFromSourceFile(QOpenGLShader::Vertex,
        ":shaders/shaders/vertexShader/gl_image.vert");
    m_imageShaderProgram->addCacheableShaderFromSourceFile(QOpenGLShader::Fragment,
        ":shaders/shaders/fragmentshader/gl_image.frag");

#if _DEBUG   // debug �������Ϣ

    const auto result = m_imageShaderProgram->link();
    if (!result)
    {
        cout << m_imageShaderProgram->log().toStdString() << endl;
    }
    cout << "link success!" << endl;

#else

    m_imageShaderProgram->link();

#endif
}

void ColorMapWidget::initGlAxesResource()
{
    using std::cout;
    using std::endl;

    m_axesVertexBuffer->create();
    m_axesIndexBuffer->create();
    m_axesArrayBuffer->create();

    m_axesArrayBuffer->bind();
    m_axesVertexBuffer->bind();

    m_axesVertexBuffer->allocate(lines_vertices.data(), sizeof(float) * lines_vertices.size());
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, nullptr);

    m_axesArrayBuffer->release();
    m_axesVertexBuffer->release();

    m_axesLineShaderProgram->addCacheableShaderFromSourceFile(QOpenGLShader::Vertex,
        ":shaders/shaders/vertexShader/gl_axes_line.vert");

    m_axesLineShaderProgram->addCacheableShaderFromSourceFile(QOpenGLShader::Fragment,
        ":shaders/shaders/fragmentshader/gl_axes_line.frag");

#if _DEBUG   // debug �������Ϣ 

    const auto result = m_axesLineShaderProgram->link();
    if (!result)
    {
        cout << m_axesLineShaderProgram->log().toStdString() << endl;
    }
    cout << "link success!" << endl;

#else

    m_imageShaderProgram->link();

#endif
}

void ColorMapWidget::drawImage()
{
    // do calcute viewport
    glViewport(width() / 4.0, height() / 4.0, width() / 2.0, height() / 2.0);

    m_imageShaderProgram->bind();
    m_imageArrayBuffer->bind();
    m_imageShaderProgram->setUniformValue("model", m_model);
    m_imageShaderProgram->setUniformValue("view", m_view);
    m_imageShaderProgram->setUniformValue("projection", m_projection);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void ColorMapWidget::drawAxes()
{
    glViewport(0, 0, width(), height());

    m_axesLineShaderProgram->bind();
    m_axesArrayBuffer->bind();

    QMatrix4x4 pro;
    pro.setToIdentity();
    pro.ortho(-2.0, 2.0, -2.0, 2.0, -1.0, 1.0);

    m_axesLineShaderProgram->setUniformValue("model", m_model);
    m_axesLineShaderProgram->setUniformValue("view", m_view);
    m_axesLineShaderProgram->setUniformValue("projection", pro);
    glDrawArrays(GL_LINES, 0, 4);
}

void ColorMapWidget::drawRect() const
{
    assert(this);
}

void ColorMapWidget::colorMapData(const std::shared_ptr<DrawData>& data)
{
    m_drawData = data;
}

ColorMapWidget::~ColorMapWidget()
{
    m_drawData.reset();

    makeCurrent();
    if (m_imageVertexBuffer)
    {
        m_imageVertexBuffer->destroy();
        delete m_imageVertexBuffer;
        m_imageVertexBuffer = nullptr;
    }

    if (m_imageArrayBuffer)
    {
        m_imageArrayBuffer->destroy();
        delete m_imageArrayBuffer;
        m_imageArrayBuffer = nullptr;
    }

    if (m_imageShaderProgram)
    {
        delete m_imageShaderProgram;
        m_imageShaderProgram = nullptr;
    }

    if (m_texture)
    {
        m_texture->destroy();
        delete m_texture;
        m_texture = nullptr;
    }

    doneCurrent();
}

void ColorMapWidget::initRenderThread()
{
    auto context = QOpenGLContext::currentContext();
    const auto mainSurface = context->surface();

    // ����������Ⱦʹ�õ� - ��Ⱦ�豸
    auto renderSurface = std::make_shared<QOffscreenSurface>(nullptr, this);
    renderSurface->setFormat(mainSurface->format());
    renderSurface->create();

    // ���ǰ�󶨵���ǰ�̵߳���Ⱦ��������
    context->doneCurrent();
    m_renderThread = std::make_unique<RenderThread>(renderSurface, context, this);
    context->makeCurrent(mainSurface);

    connect(m_renderThread.get(), &RenderThread::imageReady, this, [this]()
        {
            update();
        }, Qt::QueuedConnection);

    m_renderThread->start();
}

// ��ʼ��������ļ�
void ColorMapWidget::initGlFontResource()
{
    using std::cout;
    using std::endl;

    FT_Library ft;
    if (FT_Init_FreeType(&ft)) // ��ʼ��FreeType��
    {
        cout << "ERROR::FREETYPE: Could not init FreeType Library" << endl;
    }

    FT_Face face; // ������������Ϊһ��FreeType��֮Ϊ��(Face)
    if (FT_New_Face(ft, "./../../../resources/Fonts/arial.ttf", 0, &face))
    {
        cout << "ERROR::FREETYPE: Failed to load font" << endl;
    }
    // ����������֮��������Ҫ���������С�����ʾ������Ҫ�������������ɶ������Σ�
    // �����ֵ��Ϊ0��ʾ����Ҫ��������ͨ�������ĸ߶��ж�̬��������εĿ��
    FT_Set_Pixel_Sizes(face, 0, 48);

    // ����һ������
    // ��FT_LOAD_RENDER��Ϊ���ر��֮һ�����Ǹ���FreeTypeȥ����һ��8λ�ĻҶ�λͼ�����ǿ���ͨ��face->glyph->bitmap������
    if (FT_Load_Char(face, 'x', FT_LOAD_RENDER))
    {
        cout << "ERROR::FREETYPE: Failed to load Glyph" << endl;
    }

    // ���� 128���ַ� ����Character����map��
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    auto& charactermanager = CharacterManager::getSingleton();
    for (GLubyte c = 0; c < 128; c++)
    {
        // ��������
        if (FT_Load_Char(face, c, FT_LOAD_RENDER))
        {
            cout << "ERROR::FREETYTPE: Failed to load Glyph" << endl;
            continue;
        }
        // ��������
        GLuint texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        const auto width = face->glyph->bitmap.width;
        const auto height = face->glyph->bitmap.rows;
        glTexImage2D(
            texture,
            0,
            GL_RED,
            width,
            height,
            0,
            GL_RED,
            GL_UNSIGNED_BYTE,
            face->glyph->bitmap.buffer
        );
        // ��������Ļ�Ȼ��ʽ
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        // �����ַ���֮��ʹ��
        Character character = {
            texture,
            glm::ivec2(width, height),
            glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
            static_cast<GLuint>(face->glyph->advance.x)

        };
        charactermanager.insertCharacter(c, character);
    }

    // ���FreeType��Դ
    FT_Done_Face(face);
    FT_Done_FreeType(ft);


    m_fontShaderProgram->addCacheableShaderFromSourceFile(QOpenGLShader::Vertex,
        ":shaders/shaders/vertexShader/gl_draw_font.vert");

    m_fontShaderProgram->addCacheableShaderFromSourceFile(QOpenGLShader::Fragment,
        ":shaders/shaders/fragmentshader/gl_draw_font.frag");

#if _DEBUG   // debug �������Ϣ

    const auto result = m_fontShaderProgram->link();
    if (!result)
    {
        cout << m_fontShaderProgram->log().toStdString() << endl;
    }
    cout << "link success!" << endl;

#else

    m_imageShaderProgram->link();

#endif

}

void ColorMapWidget::drawFont() const
{
    for(const auto & ptr: m_words)
    {
        if (!ptr)
            break;

        ptr->draw(*QOpenGLContext::currentContext(), *m_fontShaderProgram);
    }

}
