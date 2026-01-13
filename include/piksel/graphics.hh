#pragma once

#include "piksel/glad_initializer.hh"
#include "piksel/window.hh"
#include "piksel/color.hh"
#include "piksel/shader.hh"
#include "piksel/IDrawable.hh"
#include "piksel/camera.hh"
#include "piksel/line.hh"
#include "piksel/liner.hh"

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
    void addDrawable(std::shared_ptr<const IDrawable> object);
    void render();
    void setBackground(const Color& color);
    void drawLine(const Line& line);
  private:
    void clear(const Color& color);
  private:
    Window& wnd_;
    GladInitializer glad_init_;
    
    const uint32_t width_;
    const uint32_t height_;

    Shader shader_;
    Liner liner_;

    std::vector<std::shared_ptr<const IDrawable>> drawables_;
    const Camera& cam_;
    glm::mat4 project_;

    Color background_;
  };
}
