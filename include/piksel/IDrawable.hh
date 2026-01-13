#pragma once

#include "piksel/shader.hh"

namespace piksel
{
  class IDrawable
  {
  public:
    virtual void draw(Shader& shader) const=0;
  protected:
    IDrawable()=default;
    virtual ~IDrawable() noexcept=default;
  }; 
}
