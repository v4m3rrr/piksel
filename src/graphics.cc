#include "piksel/graphics.hh"

#include "piksel/config.hh"

#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>

#include <memory>
#include <stdexcept>

namespace piksel
{
  Graphics::Graphics(Window& wnd, const Camera& cam)
    :wnd_(wnd),
    width_(wnd_.width_),height_(wnd_.height_),
    shader_(SHADER_PATH"/default.vert",SHADER_PATH"/default.frag"),
    cam_(cam),
    background_(Color::Black)
  {
    
    // first two params sets postion of lower left corner
    glViewport(0,0,width_,height_);
    if(glGetError()!=GL_NO_ERROR){
      std::runtime_error("failed to set viewport");
    }

    glEnable(GL_DEPTH_TEST);
    if(glGetError()!=GL_NO_ERROR){
      std::runtime_error("failed to set viewport");
    }

    shader_.use();
    auto proj=glm::perspective(
        glm::radians(45.0f),(float)wnd_.width_/wnd_.height_,0.1f,100.0f);
    glUniformMatrix4fv(
        glGetUniformLocation(shader_.get(),"proj"),
        1,GL_FALSE,glm::value_ptr(proj));
  }

  void Graphics::addObject(std::shared_ptr<const Object> object)
  {
    objects_.emplace_back(object);
  }

  void Graphics::render()
  {
    clear(background_);

    for(auto p_obj :objects_)
    {
      glm::mat4 transform=p_obj->translate*p_obj->rotate*p_obj->scale;
      glUniformMatrix4fv(
          glGetUniformLocation(shader_.get(),"trans"),
          1,GL_FALSE,glm::value_ptr(transform));

      //const float radius = 10.0f;
      //float camX = cos(glfwGetTime()) * radius;
      //float camZ = sin(glfwGetTime())*radius/2.f;
      //glm::mat4 view;
      //view = glm::lookAt(
      //    glm::vec3(1.0f, 0.0, camZ), 
      //    glm::vec3(0.0, 0.0, camZ), 
      //    glm::vec3(0.0, 1.0, 0.0)); 
      glUniformMatrix4fv(
          glGetUniformLocation(shader_.get(),"view"),
          1,GL_FALSE,glm::value_ptr(cam_.getCameraView()));

      p_obj->draw(shader_);
    }
  }

  void Graphics::setBackground(const Color& color)
  {
    background_=color;
  }

  void Graphics::clear(const Color& color)
  {
    glClearColor(color.c.x,color.c.y,color.c.z,color.c.w);
    if(glGetError()!=GL_NO_ERROR){
      std::runtime_error("failed to set viewport");
    }
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    if(glGetError()!=GL_NO_ERROR){
      std::runtime_error("failed to set viewport");
    }
  }
}
