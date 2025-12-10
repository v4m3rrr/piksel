#pragma once

#include "piksel/glad_initializer.hh"
#include "piksel/window.hh"
#include "piksel/color.hh"
#include "piksel/shader.hh"
#include "piksel/camera.hh"
#include "piksel/object.hh"

#include <vector>
#include <memory>
#include <string_view>

namespace piksel
{
  class Graphics
  {
  public:
    Graphics(
        Window& wnd,const Camera& cam, 
        std::string_view vertex_shader, std::string_view fragement_shader);
    void addObject(std::shared_ptr<const Object> object);
    void render();
    void setBackground(const Color& color);
  private:
    void clear(const Color& color);
  private:
    Window& wnd_;
    GladInitializer glad_init_;
    
    const uint32_t width_;
    const uint32_t height_;

    Shader shader_;

    std::vector<std::shared_ptr<const Object>> objects_;
    const Camera& cam_;

    Color background_;
  };
}
