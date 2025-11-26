#include "piksel/graphics.hh"
#include "piksel/piksel.hh"
#include <GLFW/glfw3.h>
#include <stdexcept>

namespace piksel
{
  Graphics::Graphics(Window& wnd)
    :wnd_(wnd),
    width_(wnd_.width_),height_(wnd_.height_),
    shader_("shaders/default.vert","shaders/default.frag")
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
  }

  void Graphics::AddCube(Cube&& cube)
  {
    cubes_.push_back(std::move(cube));
  }

  void Graphics::Render()
  {
    clear(Color::Black);

    shader_.use();
    cube_manager_.use();

    for( auto& cube : cubes_)
    {
      cube.tex.bind();
      shader_.set("tex",cube.tex.getTextureUnit());

      cube_manager_.use();
      glDrawElements(GL_TRIANGLES,Cube::indices_len,GL_UNSIGNED_INT,0);
      if(glGetError()!=GL_NO_ERROR){
        std::runtime_error("failed to set viewport");
      }
    }
  }

  void Graphics::clear(Color color)
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
