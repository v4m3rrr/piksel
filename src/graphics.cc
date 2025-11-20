#include "piksel/graphics.hh"
#include "piksel/piksel.hh"
#include <GLFW/glfw3.h>
#include <stdexcept>

namespace piksel
{
  Graphics::Graphics(Window& wnd)
    :wnd_(wnd),width_(wnd_.width_),height_(wnd_.height_)
  {
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
      std::runtime_error("Fialed to init GLAD");
    }
    
    // first two params sets postion of lower left corner
    glViewport(0,0,width_,height_);
  }

  void Graphics::clear(Color color)
  {
    glClearColor(color.r,color.g,color.b,color.a);
    glClear(GL_COLOR_BUFFER_BIT);
  }
}
