#include "piksel/window.hh"
#include "piksel/graphics.hh"
#include "piksel/camera.hh"
#include "piksel/color.hh"

using namespace piksel;



int main()
{
  Window wnd("Model load test", 1280,720);
  Camera cam({0.f,0.f,10.f},{0.f,0.f,0.f});
  Graphics gfx(wnd,cam);
  gfx.setBackground(Color::Blue);

  while(wnd)
  {

    if(wnd.getKey(GLFW_KEY_ESCAPE)==Window::KeyState::Press){
      wnd.close();
    }

    gfx.render();
    wnd.update();
  }
  return 0;
}
