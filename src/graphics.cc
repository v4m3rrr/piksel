#include "piksel/graphics.hh"
#include "piksel/IDrawable.hh"

#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>

#include <memory>
#include <stdexcept>

namespace piksel
{
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
    width_(wnd_.width_),height_(wnd_.height_),
    shader_(std::move(shader)),
    cam_(cam),
    background_(Color::Black)
  {
    // first two params sets postion of lower left corner
    glViewport(0,0,width_,height_);
    if(glGetError()!=GL_NO_ERROR){
      throw std::runtime_error("failed to set viewport");
    }

    glEnable(GL_DEPTH_TEST);
    if(glGetError()!=GL_NO_ERROR){
      throw std::runtime_error("failed to set viewport");
    }

    shader_.use();
    project_=glm::perspective(
        glm::radians(45.0f),(float)wnd_.width_/wnd_.height_,0.1f,1000.0f);
    glUniformMatrix4fv(
        glGetUniformLocation(shader_.get(),"proj"),
        1,GL_FALSE,glm::value_ptr(project_));
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
    shader_.use();
    glUniformMatrix4fv(
      glGetUniformLocation(shader_.get(),"view"),
      1,GL_FALSE,glm::value_ptr(cam_.getCameraView()));

    for(auto drawable :drawables_)
    {
      drawable->draw(shader_);
    }

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
    glClearColor(background_.c.x,background_.c.y,background_.c.z,background_.c.w);
    if(glGetError()!=GL_NO_ERROR){
      throw std::runtime_error("failed to set viewport");
    }
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    if(glGetError()!=GL_NO_ERROR){
      throw std::runtime_error("failed to set viewport");
    }
  }
}
