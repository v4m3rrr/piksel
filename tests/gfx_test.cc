#include "piksel/graphics.hh"
#include "piksel/window.hh"
#include "piksel/gui_manager.hh"
#include <GLFW/glfw3.h>
#include <glm/ext/vector_float3.hpp>

#ifdef RASPBERRY_PI
const char* vertex_sh_path=PIKSEL_SHADERS_PATH"/single_color_es.vert";
const char* frag_sh_path=PIKSEL_SHADERS_PATH"/single_color_es.frag";
#else
const char* vertex_sh_path=PIKSEL_SHADERS_PATH"/single_color.vert";
const char* frag_sh_path=PIKSEL_SHADERS_PATH"/single_color.frag";
#endif

using namespace piksel;
Window wnd("window");
Camera cam({0.f,0.f,5.f},{0.f,0.f,0.f});
Graphics gfx(wnd,cam,
    vertex_sh_path,
    frag_sh_path);
GuiManager gui_manager(wnd.getGLFWPointer());

class InfoPanel : public GuiObject
{
public:
  ~InfoPanel() noexcept override=default;
  void draw() override
  {
    GuiObject::text("Jakis tekst");
    GuiObject::checkBox("Checkbox cos tam",&czy);
  } 
  std::string_view getTitle() const override
  {
    return title;
  }
private:
    std::string title="Inforamtion of your mother";
    bool czy=false;
};

void drawLine(
      const glm::vec3& from,
      const glm::vec3& to,
      const glm::vec3& color);
int main()
{
  std::shared_ptr<GuiObject> panel(new InfoPanel());
  gui_manager.addObject(panel);

  float mouse_speed=0.3f;
  float cam_speed=5.f;
  gfx.setBackground(Color::Black);

  float prev=glfwGetTime();
  while(wnd)
  {
    gfx.clearLines();
    gfx.clear();

    float now=glfwGetTime();
    float dt=now-prev;
    prev=now;

    static piksel::Window::MousePos prev_mouse_pos=wnd.getMousePos();

    if(wnd.getKey(GLFW_KEY_ESCAPE)==piksel::Window::KeyState::Press)
      wnd.close();
    
    if(wnd.getKey(GLFW_KEY_W)==piksel::Window::KeyState::Press){
      cam.moveLongitudinal(cam_speed*dt);
    }
    if(wnd.getKey(GLFW_KEY_S)==piksel::Window::KeyState::Press){
      cam.moveLongitudinal(-cam_speed*dt);
    }

    if(wnd.getKey(GLFW_KEY_A)==piksel::Window::KeyState::Press){
      cam.moveLateral(-cam_speed*dt);
    }
    if(wnd.getKey(GLFW_KEY_D)==piksel::Window::KeyState::Press){
      cam.moveLateral(cam_speed*dt);
    }

    piksel::Window::MousePos mouse_pos=wnd.getMousePos();
    if(wnd.getKey(GLFW_KEY_LEFT_SHIFT)==piksel::Window::KeyState::Press){
      wnd.setCursor();
      gui_manager.ignoreInput(false);
    }
    else
    {
      gui_manager.ignoreInput();
      wnd.setCursor(false);
      cam.rotateYaw((float)(prev_mouse_pos.x-mouse_pos.x)*dt*mouse_speed);
      cam.rotatePitch((float)(prev_mouse_pos.y-mouse_pos.y)*dt*mouse_speed);
    }
    prev_mouse_pos.x=mouse_pos.x;
    prev_mouse_pos.y=mouse_pos.y;

    drawLine(
        {0.f,0.f,0.f},
        {10.f,0.f,0.f},
        {1.f,0.f,0.f});
    drawLine(
        {0.f,0.f,0.f},
        {0.f,10.f,0.f},
        {0.f,1.f,0.f});
    drawLine(
        {0.f,0.f,0.f},
        {0.f,0.f,10.f},
        {0.f,0.f,1.f});

    gfx.render();
    gui_manager.render();
    wnd.update();
  }
}

void drawLine(
      const glm::vec3& from,
      const glm::vec3& to,
      const glm::vec3& color)
{
  gfx.drawLine(piksel::Line{from,to,color});
}
