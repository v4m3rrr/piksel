#include "piksel/window.hh"
#include "piksel/graphics.hh"
#include "piksel/camera.hh"
#include "piksel/color.hh"
#include "piksel/config.hh"
#include "piksel/line.hh"

#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace piksel;

int main()
{
  constexpr float cam_speed=10.f; 
  Window wnd("Model load test", 1280,720);
  Camera cam({0.f,0.f,5.f},{0.f,0.f,0.f});
  Graphics gfx(
      wnd,cam,
      PIKSEL_SHADERS_PATH"/line.vert",
      PIKSEL_SHADERS_PATH"/line.frag");
  gfx.setBackground(Color::Black);

  Line x_axis{
    glm::vec3(0.f,0.f,0.f),
    glm::vec3(10.f,0.f,0.f),
    glm::vec3(1.0f,0.0f,0.f)};

  Line y_axis{
    glm::vec3(0.f,0.f,0.f),
    glm::vec3(0.f,10.f,0.f),
    glm::vec3(0.0f,1.0f,0.f)};

  Line z_axis{
    glm::vec3(0.f,0.f,0.f),
    glm::vec3(0.f,0.f,10.f),
    glm::vec3(0.0f,0.0f,1.f)};


  float last=glfwGetTime();
  Window::MousePos prev_mouse_pos=wnd.getMousePos();
  // Atleast on wayland glfw behaves stragy and moves
  // mouse once which rotates unexpectldl
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

    gfx.drawLine(x_axis);
    gfx.drawLine(y_axis);
    gfx.drawLine(z_axis);
    gfx.render();
    wnd.update();
  }
  return 0;
}
