#include "piksel/window.hh"
#include "piksel/graphics.hh"
#include "piksel/cube.hh"

using namespace piksel;

int main(int argc, char **argv)
{
  Window wnd("Test",800,600);

  if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
  {
    std::runtime_error("failed to init GLAD");
  }
  Graphics gfx(wnd);

  gfx.AddCube({0.f,{0.f,0.f,1.f},{0.f,0.f,0.f},"textures/container.jpg",0});
  while(wnd)
  {
    if(wnd.getKey(GLFW_KEY_ESCAPE)==Window::KeyState::Press)
      wnd.close();

    gfx.Render();
    wnd.update();
  }

  return 0;
}

