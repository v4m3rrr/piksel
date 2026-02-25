#include "piksel/graphics.hh"
#include "piksel/IDrawable.hh"

#include "piksel/exception.hh"

#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>

#include <memory>

namespace piksel
{
  static constexpr Exception::Type kExceptionType=Exception::Type::GraphicsError;
  Graphics::Graphics(
        Window& wnd,const Camera& cam, 
        std::string_view vertex_shader, std::string_view fragement_shader)
    :
      Graphics(wnd,cam,Shader(vertex_shader,fragement_shader))
  {
  }

  Graphics::Graphics(
      Window& wnd,const Camera& cam,
      Shader&& shader)
    :wnd_(wnd),
    shader_(std::move(shader)),
    cam_(cam),
    background_(Color::Black)
  {
    glEnable(GL_DEPTH_TEST);
    if(glGetError()!=GL_NO_ERROR){
      throw Exception(kExceptionType,"Failed to enable depth test");
    }
  }

  void Graphics::addDrawable(std::shared_ptr<const IDrawable> drawable)
  {
    drawables_.emplace_back(drawable);
  }

  void Graphics::clearLines()
  {
    liner_.clear();
  }

  void Graphics::render()
  {
    // manage resizable window
    // first two params sets postion of lower left corner
    Window::WindowSize window_size=wnd_.getWindowSize();
    glViewport(0,0,window_size.width,window_size.height);

    shader_.use();

    project_=glm::perspective(
        glm::radians(45.0f),(float)window_size.width/window_size.height,0.1f,1000.0f);
    glUniformMatrix4fv(
        glGetUniformLocation(shader_.get(),"proj"),
        1,GL_FALSE,glm::value_ptr(project_));
    if(glGetError()!=GL_NO_ERROR){
      throw Exception(kExceptionType,"Failed to set project uniform");
    }

    glUniformMatrix4fv(
      glGetUniformLocation(shader_.get(),"view"),
      1,GL_FALSE,glm::value_ptr(cam_.getCameraView()));
    if(glGetError()!=GL_NO_ERROR){
      throw Exception(kExceptionType,"Failed to set view uniform");
    }

    for(auto drawable :drawables_)
    {
      drawable->draw(shader_);
    }
    drawables_.clear();

    liner_.draw(project_*cam_.getCameraView());
  }

  void Graphics::drawLine(const Line& line)
  {
    liner_.addLine(line);
  }

  void Graphics::setBackground(const Color& color)
  {
    background_=color;
  }

  void Graphics::clear()
  {
    // Raerly throws
    glClearColor(background_.c.x,background_.c.y,background_.c.z,background_.c.w);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  }
}
