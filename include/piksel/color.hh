#pragma once

#include <glm/vec4.hpp>
#include <glm/vec3.hpp>

namespace piksel 
{

struct Color 
{
    glm::vec4 c;

    operator glm::vec4&() {return c;}
    operator glm::vec4() const {return c;}

    inline glm::vec3 rgb() const{return glm::vec3(c.x,c.y,c.z);}

    static const Color Red;
    static const Color Green;
    static const Color Blue;
    static const Color Black;
    static const Color White;
};
} 
