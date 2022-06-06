#ifndef GL_FONT_H_
#define GL_FONT_H_

#include <memory>

class QOpenGLShaderProgram;
class QOpenGLVertexArrayObject;
class QOpenGLBuffer;

using std::unique_ptr;

class GlFont
{
public:
    explicit GlFont();
    ~GlFont() = default;

    GlFont(const GlFont& another) = delete;
    GlFont(GlFont&& another) = delete;
    GlFont operator=(const GlFont& another) = delete;
    GlFont operator=(GlFont&& another) = delete;

    void draw(QOpenGLShaderProgram& shader) const;

protected:
    unique_ptr<QOpenGLBuffer> m_fontVertexBuffer{ nullptr };
    unique_ptr<QOpenGLBuffer> m_fontIndexBuffer{ nullptr };
    unique_ptr<QOpenGLVertexArrayObject> m_fontArrayBuffer{ nullptr };
};





#endif 