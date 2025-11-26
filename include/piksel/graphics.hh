#pragma once

#include "piksel/glad_initializer.hh"
#include "piksel/window.hh"
#include "piksel/color.hh"
#include "piksel/shader.hh"
#include "piksel/cube.hh"
#include "piksel/cube_manager.hh"
#include "piksel/camera.hh"

#include <vector>
#include <functional>

namespace piksel
{
  class Graphics
  {
  public:
    Graphics(Window& wnd,const Camera& cam);
    void AddCube(const Cube& cube);
    void Render();

    void clear(Color color);
  private:
    Window& wnd_;
    GladInitializer glad_init_;
    
    const uint32_t width_;
    const uint32_t height_;

    Shader shader_;
    CubeManager cube_manager_;

    std::vector<std::reference_wrapper<const Cube>> cubes_;
    const Camera& cam_;
  };
}
