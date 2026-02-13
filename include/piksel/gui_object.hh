#pragma once

#include <glm/vec3.hpp>

#include <string_view>

namespace piksel
{
  class GuiObject
  {
  public:
    virtual ~GuiObject() noexcept=default;
    virtual std::string_view getTitle() const=0;
    virtual void draw()=0;
  };
}
