#include "piksel/liner.hh"

#include "piksel/shader.hh"

#include <glm/gtc/type_ptr.hpp>

#include <stdexcept>

namespace piksel
{
  Liner::Liner(
      float stroke, 
      std::string_view shader_path_vert,
      std::string_view Shader_path_frag)
    :stroke_(stroke),shader_(shader_path_vert,Shader_path_frag)
  {
    glGenVertexArrays(1,&vao_);
    glGenBuffers(1,&vbo_);

    glBindVertexArray(vao_);
    glBindBuffer(GL_ARRAY_BUFFER,vbo_);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(
        0,
        decltype(Vertex::pos)::length(),
        GL_FLOAT,
        GL_FALSE,
        sizeof(Vertex),
        (void*)0
        );

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(
        1,
        decltype(Vertex::color)::length(),
        GL_FLOAT,
        GL_FALSE,
        sizeof(Vertex),
        (void*)sizeof(Vertex::pos)
        );

    glBindVertexArray(0);
  }

  void Liner::addLine(const Line& line)
  {
    vertices_.emplace_back(line.from,line.color);
    vertices_.emplace_back(line.to,line.color);
  }

  void Liner::draw(const glm::mat4& proj_and_view)
  {
    shader_.use();
    glUniformMatrix4fv(
        glGetUniformLocation(shader_.get(),"proj_view"),
        1,GL_FALSE,glm::value_ptr(proj_and_view));

    glm::mat4 transform(1.f);
    glUniformMatrix4fv(
        glGetUniformLocation(shader_.get(),"trans"),
        1,GL_FALSE,glm::value_ptr(transform));

    glBindVertexArray(vao_);
    glBindBuffer(GL_ARRAY_BUFFER,vbo_);
    glBufferData(
        GL_ARRAY_BUFFER,
        sizeof(Vertex)*vertices_.size(),
        vertices_.data(),
        GL_DYNAMIC_DRAW);
    //glDrawElements(
    //    GL_LINES,indices_.size(),GL_UNSIGNED_INT,0);
    glLineWidth(stroke_);
    glDrawArrays(GL_LINES,0,vertices_.size());
    if(glGetError()!=GL_NO_ERROR){
      throw std::runtime_error("failed to set viewport");
    }
    glBindVertexArray(0);

    vertices_.clear();
  }
}
