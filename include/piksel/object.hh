#pragma once

#include "piksel/shader.hh"

#include <glm/glm.hpp>

namespace piksel
{
  class Object
  {
  public:
    virtual void draw(Shader& shader) const=0;
  public:
    glm::mat4 translate;
    glm::mat4 rotate;
    glm::mat4 scale;
  protected:
    Object()
      :translate(1.f),rotate(1.f),scale(1.f)
    {
    }
    virtual ~Object() noexcept=default;
  };
}
