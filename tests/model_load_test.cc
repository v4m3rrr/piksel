#include "piksel/model.hh"
#include "piksel/window.hh"
#include "piksel/graphics.hh"
#include "piksel/camera.hh"
#include "piksel/color.hh"
#include "piksel/config.hh"

#include <glm/gtc/matrix_transform.hpp>

#include <memory>

using namespace piksel;

int main()
{
  constexpr float cam_speed=10.f; 
  Window wnd("Model load test", 1280,720);
  Camera cam({0.f,0.f,10.f},{0.f,0.f,0.f});
  Graphics gfx(
      wnd,cam,PIKSEL_SHADERS_PATH"/single_color.vert",PIKSEL_SHADERS_PATH"/single_color.frag");
  gfx.setBackground(Color::Blue);

  auto fox = std::make_shared<Model>(PIKSEL_ASSETS_PATH"/models/Fox.glb");

  fox->color=Color::Green;

  double scale_factor=0.25;

  gfx.addObject(fox);
  
  float last=glfwGetTime();
  Window::MousePos prev_mouse_pos=wnd.getMousePos();
  while(wnd)
  {
    float right_now=glfwGetTime();
    float dt=right_now-last;
    last=right_now;

    if(wnd.getKey(GLFW_KEY_ESCAPE)==Window::KeyState::Press)
      wnd.close();
    
    if(wnd.getKey(GLFW_KEY_W)==Window::KeyState::Press){
      cam.moveLongitudinal(cam_speed*dt);
    }
    if(wnd.getKey(GLFW_KEY_S)==Window::KeyState::Press){
      cam.moveLongitudinal(-cam_speed*dt);
    }

    if(wnd.getKey(GLFW_KEY_A)==Window::KeyState::Press){
      cam.moveLateral(-cam_speed*dt);
    }
    if(wnd.getKey(GLFW_KEY_D)==Window::KeyState::Press){
      cam.moveLateral(cam_speed*dt);
    }

    Window::MousePos mouse_pos=wnd.getMousePos();
    cam.rotateYaw((prev_mouse_pos.x-mouse_pos.x)*dt/3.f);
    prev_mouse_pos.x=mouse_pos.x;
    cam.rotatePitch((prev_mouse_pos.y-mouse_pos.y)*dt/3.f);
    prev_mouse_pos.y=mouse_pos.y;

    gfx.render();
    wnd.update();
  }
  return 0;
}
