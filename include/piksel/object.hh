#pragma once

#include "piksel/shader.hh"
#include "piksel/color.hh"

#include <glm/glm.hpp>

namespace piksel
{
  class Object
  {
  public:
    virtual void draw(Shader& shader) const=0;
    glm::mat4 getTransform() const { return translate*rotate*scale;}
  public:
    glm::mat4 translate;
    glm::mat4 rotate;
    glm::mat4 scale;
    Color color;
  protected:
    Object()
      :translate(1.f),rotate(1.f),scale(1.f),color(Color::White)
    {
    }
    virtual ~Object() noexcept=default;
  };
}
