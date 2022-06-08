#ifndef GL_FONT_H_
#define GL_FONT_H_

#include <memory>
#include <string>

#include "glm/vec2.hpp"
#include <QOpenGLFunctions_4_5_Core>

class QOpenGLShaderProgram;
class QOpenGLVertexArrayObject;
class QOpenGLBuffer;
class QOpenGLContext;

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

    void setString(std::string str);
    void draw(const QOpenGLContext& context,QOpenGLShaderProgram& shader);
    void createResources(const QOpenGLContext & context) const;

protected:
    unique_ptr<QOpenGLBuffer> m_fontVertexBuffer{ nullptr };
    unique_ptr<QOpenGLBuffer> m_fontIndexBuffer{ nullptr };
    unique_ptr<QOpenGLVertexArrayObject> m_fontArrayBuffer{ nullptr };

    // QOpenGLBuffer* m_fontVertexBuffer{ nullptr };
    // QOpenGLBuffer* m_fontIndexBuffer{ nullptr };
    // QOpenGLVertexArrayObject* m_fontArrayBuffer{ nullptr };

    std::string m_str;

    glm::vec2 m_position{0.0,0.0};  // 字体的位置 
    GLfloat m_scale{ 1.0 };               // 字体的缩放 

};





#endif 