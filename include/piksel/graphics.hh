#pragma once

#include "piksel/window.hh"
#include "piksel/color.hh"
#include "piksel/shader.hh"
#include "piksel/cube.hh"
#include "piksel/cube_manager.hh"

#include <vector>

namespace piksel
{
  class Graphics
  {
  public:
    Graphics(Window& wnd);
    void AddCube(Cube&& cube);
    void Render();
    void clear(Color color);
  private:
    Window& wnd_;
    
    const uint32_t width_;
    const uint32_t height_;

    Shader shader_;
    CubeManager cube_manager_;

    std::vector<Cube> cubes_;
  };
}
