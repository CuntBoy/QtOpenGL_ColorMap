#include "character.h"


CharacterManager& CharacterManager::getSingleton()
{
    static  CharacterManager obj;
    return obj;
}

void CharacterManager::insertCharacter(GLchar c, Character& obj)
{
    m_characters.insert(std::pair<GLchar, Character>(c, obj));
}

Character CharacterManager::getCharacter(GLchar c)
{
    const auto res = m_characters.find(c);
    if (res != m_characters.end())
    {
        return res->second;
    }

    return {};  // 没有找到返回一个空的变量 
}

CharacterManager::CharacterManager()
{
    m_characters.clear();
}
