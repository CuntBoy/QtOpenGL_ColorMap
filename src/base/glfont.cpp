#include "glfont.h"
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLFunctions>
#include <QOpenGLContext>
#include "character.h"

using std::make_unique;

GlFont::GlFont()
    : m_fontVertexBuffer(make_unique<QOpenGLBuffer>(QOpenGLBuffer::VertexBuffer))
    , m_fontIndexBuffer(make_unique<QOpenGLBuffer>(QOpenGLBuffer::IndexBuffer))
    , m_fontArrayBuffer(make_unique<QOpenGLVertexArrayObject>())
{


}

void GlFont::setString(const std::string str)
{
    m_str = str;
}

void GlFont::draw(const QOpenGLContext& context, QOpenGLShaderProgram& shader)
{
    const auto functions = context.functions();
    shader.bind();
    shader.setUniformValue("textColor",
        QVector3D(0, 0, 0));

    m_fontArrayBuffer->bind();
    functions->glActiveTexture(GL_TEXTURE0);

    auto it = m_str.begin();
    auto& manager = CharacterManager::getSingleton();
    for (auto& c : m_str)
    {
        Character ch = manager.getCharacter(c);
        if (!ch.isViald())
        {
            break;
        }

        GLfloat xpos = m_position.x + ch.Bearing.x * m_scale;
        GLfloat ypos = m_position.y - (ch.Size.y - ch.Bearing.y) * m_scale;

        GLfloat w = ch.Size.x;
        GLfloat h = ch.Size.y;

        GLfloat vertices[6][4] = {
          { xpos,     ypos + h,   0.0, 0.0 },
          { xpos,     ypos,       0.0, 1.0 },
          { xpos + w, ypos,       1.0, 1.0 },

          { xpos,     ypos + h,   0.0, 0.0 },
          { xpos + w, ypos,       1.0, 1.0 },
          { xpos + w, ypos + h,   1.0, 0.0 }
        };

        functions->glBindTexture(GL_TEXTURE_2D, ch.TextureID);
        m_fontArrayBuffer->bind();
        functions->glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
        m_fontArrayBuffer->release();
        m_fontVertexBuffer->release();

        m_position.x += (ch.Advance >> 6) * m_scale;
    }

}

void GlFont::createResources(const QOpenGLContext& context) const
{
    m_fontVertexBuffer->create();
    m_fontArrayBuffer->create();

    m_fontArrayBuffer->bind();
    m_fontVertexBuffer->bind();
    m_fontVertexBuffer->allocate(nullptr, sizeof(float) * 6 * 4);

    const auto functions = (context.functions());
    functions->glEnableVertexAttribArray(0);
    functions->glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), nullptr);

    m_fontVertexBuffer->release();
    m_fontArrayBuffer->release();
}
