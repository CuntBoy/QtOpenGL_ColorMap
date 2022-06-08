//
// Created by RanLH on 6/6/2022.
//

#ifndef COLORMAP_CHARACTER_H
#define COLORMAP_CHARACTER_H

#include <glm/vec2.hpp>
#include <map>
#include <QOpenGLFunctions_4_5_Core>   |

using std::map;

struct Character
{
    GLuint TextureID{ 0 };             // 字形纹理
    glm::ivec2 Size{ 0,0 };      // 字形的大小
    glm::ivec2 Bearing{ 0,0 };   // 从基准线到字形左部以及到字形顶部的偏移
    GLuint Advance{ 0 };               // 从当前字形原点到下一个原点的距离

    bool isViald()  const
    {
        return TextureID;
    }

};

// 初始化渲染使用的字体
class CharacterManager
{
public:
    CharacterManager(const CharacterManager& another) = delete;
    CharacterManager(CharacterManager&& another) = delete;
    CharacterManager& operator=(const CharacterManager& another) = delete;
    CharacterManager& operator=(CharacterManager&& another) = delete;

    static CharacterManager& getSingleton();
    void  insertCharacter(GLchar c, Character& obj);
    Character getCharacter(GLchar c);

protected:
    explicit CharacterManager();
    ~CharacterManager() = default;

private:
    std::map<GLchar, Character> m_characters;

};





#endif //COLORMAP_CHARACTER_H
