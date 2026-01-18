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
    
  protected:
    void checkBox(std::string_view text, bool* value);
    void text(std::string_view text);
    void slider(std::string_view label,float min, float max,float* value);
    void color(std::string_view label, glm::vec3& color);
    bool collapsingHeader(std::string_view label);
    void sameLine();
  };
}
