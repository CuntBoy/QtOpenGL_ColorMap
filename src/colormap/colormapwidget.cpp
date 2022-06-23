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
    , m_texture(new QOpenGLTexture(QOpenGLTexture::Target2D)) // 2D 纹理
    , m_testData(std::make_shared<std::array<float, 42>>(vertices)) // 创建多个窗口的时候会报错 TODO
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

    // 创建字体
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

    // draw 选框
    drawRect();
}

void ColorMapWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
    // 设置帧缓冲大小
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

#if _DEBUG   // debug 下输出信息

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

#if _DEBUG   // debug 下输出信息 

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

    // 创建离屏渲染使用的 - 渲染设备
    auto renderSurface = std::make_shared<QOffscreenSurface>(nullptr, this);
    renderSurface->setFormat(mainSurface->format());
    renderSurface->create();

    // 解绑当前绑定到当前线程的渲染的上下文
    context->doneCurrent();
    m_renderThread = std::make_unique<RenderThread>(renderSurface, context, this);
    context->makeCurrent(mainSurface);

    connect(m_renderThread.get(), &RenderThread::imageReady, this, [this]()
        {
            update();
        }, Qt::QueuedConnection);

    m_renderThread->start();
}

// 初始化字体的文件
void ColorMapWidget::initGlFontResource()
{
    using std::cout;
    using std::endl;

    FT_Library ft;
    if (FT_Init_FreeType(&ft)) // 初始化FreeType库
    {
        cout << "ERROR::FREETYPE: Could not init FreeType Library" << endl;
    }

    FT_Face face; // 将这个字体加载为一个FreeType称之为面(Face)
    if (FT_New_Face(ft, "./../../../resources/Fonts/arial.ttf", 0, &face))
    {
        cout << "ERROR::FREETYPE: Failed to load font" << endl;
    }
    // 当面加载完成之后，我们需要定义字体大小，这表示着我们要从字体面中生成多大的字形：
    // 将宽度值设为0表示我们要从字体面通过给定的高度中动态计算出字形的宽度
    FT_Set_Pixel_Sizes(face, 0, 48);

    // 激活一个字形
    // 将FT_LOAD_RENDER设为加载标记之一，我们告诉FreeType去创建一个8位的灰度位图，我们可以通过face->glyph->bitmap来访问
    if (FT_Load_Char(face, 'x', FT_LOAD_RENDER))
    {
        cout << "ERROR::FREETYPE: Failed to load Glyph" << endl;
    }

    // 生成 128个字符 保存Character对象到map中
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    auto& charactermanager = CharacterManager::getSingleton();
    for (GLubyte c = 0; c < 128; c++)
    {
        // 加载字形
        if (FT_Load_Char(face, c, FT_LOAD_RENDER))
        {
            cout << "ERROR::FREETYTPE: Failed to load Glyph" << endl;
            continue;
        }
        // 创建纹理
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
        // 设置纹理的焕然方式
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        // 储存字符供之后使用
        Character character = {
            texture,
            glm::ivec2(width, height),
            glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
            static_cast<GLuint>(face->glyph->advance.x)

        };
        charactermanager.insertCharacter(c, character);
    }

    // 清空FreeType资源
    FT_Done_Face(face);
    FT_Done_FreeType(ft);


    m_fontShaderProgram->addCacheableShaderFromSourceFile(QOpenGLShader::Vertex,
        ":shaders/shaders/vertexShader/gl_draw_font.vert");

    m_fontShaderProgram->addCacheableShaderFromSourceFile(QOpenGLShader::Fragment,
        ":shaders/shaders/fragmentshader/gl_draw_font.frag");

#if _DEBUG   // debug 下输出信息

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
