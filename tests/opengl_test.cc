#include "glm/ext/matrix_transform.hpp"
#include "glm/trigonometric.hpp"

#include "piksel/window.hh"
#include "piksel/graphics.hh"
#include "piksel/cube.hh"
#include "piksel/camera.hh"

#include <GLFW/glfw3.h>
#include <chrono>

using namespace piksel;
using namespace std::chrono_literals;

int main(int argc, char **argv)
{
  constexpr float FPS=120.f;
  constexpr float cam_speed=10.f;

  Window wnd("Test",800,600);

  Camera cam({10.f,0.f,0.f},{0.f,0.f,0.f});
  Graphics gfx(wnd, cam);

  Cube cube({1.f,1.0f,1.f,"textures/container.jpg",0});
  Cube cube2({1.5f,1.5f,1.f,"textures/container.jpg",0});

  gfx.AddCube(cube);
  gfx.AddCube(cube2);

  auto tp=std::chrono::steady_clock::now();
  float last=glfwGetTime();
  while(wnd)
  {
    float right_now=glfwGetTime();
    float dt=right_now-last;
    last=right_now;

    if(wnd.getKey(GLFW_KEY_ESCAPE)==Window::KeyState::Press)
      wnd.close();
    
    if(wnd.getKey(GLFW_KEY_W)==Window::KeyState::Press){
      cam.moveBy(glm::vec3(0.f,0.f,cam_speed*dt));
    }
    if(wnd.getKey(GLFW_KEY_S)==Window::KeyState::Press){
      cam.moveBy(glm::vec3(0.f,0.f,-cam_speed*dt));
    }

    if(wnd.getKey(GLFW_KEY_A)==Window::KeyState::Press){
      cam.moveBy(glm::vec3(cam_speed*dt,0.f,0.f));
    }
    if(wnd.getKey(GLFW_KEY_D)==Window::KeyState::Press){
      cam.moveBy(glm::vec3(-cam_speed*dt,0.f,0.f));
    }

    // Call only every 1/30 seconds.
    auto now=std::chrono::steady_clock::now();
    if(now-tp>1s/FPS){
      tp=now;
      cube.translate=glm::translate(glm::mat4(1.f),{0.f,0.00f,0.0f});
      cube.rotate=glm::rotate(cube.rotate,glm::radians(360.f/FPS),
          {1.f,0.f,1.f});
     
      cube2.translate=glm::translate(glm::mat4(1.f),{0.f,0.00f,3.0f});
      cube2.rotate=glm::rotate(cube.rotate,glm::radians(360.f/FPS),
          {1.f,0.f,1.f});
    }

    gfx.Render();
    wnd.update();
  }

  return 0;
}

