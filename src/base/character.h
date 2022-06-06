//
// Created by RanLH on 6/6/2022.
//

#ifndef COLORMAP_CHARACTER_H
#define COLORMAP_CHARACTER_H

#include <glm/vec2.hpp>
#include <iostream>
#include <map>
#include <QOpenGLFunctions_4_5_Core>

using std::map;

struct Character
{
    GLuint TextureID;     // 字形纹理
    glm::ivec2 Size;      // 字形的大小
    glm::ivec2 Bearing;   // 从基准线到字形左部以及到字形顶部的偏移
    GLuint Advance;       // 从当前字形原点到下一个原点的距离
};

std::map<GLchar,Character> m_characters;

#endif //COLORMAP_CHARACTER_H
