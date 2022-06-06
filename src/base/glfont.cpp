#include "glfont.h"
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>

using std::make_unique;

GlFont::GlFont()
    : m_fontVertexBuffer(make_unique<QOpenGLBuffer>(QOpenGLBuffer::VertexBuffer))
    , m_fontIndexBuffer(make_unique<QOpenGLBuffer>(QOpenGLBuffer::IndexBuffer))
    , m_fontArrayBuffer(make_unique<QOpenGLVertexArrayObject>())
{

}

void GlFont::draw(QOpenGLShaderProgram& shader) const
{
    shader.bind();
    m_fontArrayBuffer->bind();
    // glDrawArrays(GL_TRIANGLES, 0, 6);
}
