#include "piksel/wireframe.hh"

#include "piksel/shader.hh"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <stdexcept>

namespace piksel
{
  Wireframe::Wireframe(float stroke)
    :stroke_(stroke)
  {
    glGenVertexArrays(1, &vao_); 
    glBindVertexArray(vao_);

    glGenBuffers(1,&vbo_);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_);
    glBufferData(
        GL_ARRAY_BUFFER,
        sizeof(Vertex)*s_vertices_.size(),
        s_vertices_.data(),
        GL_STATIC_DRAW);

    glGenBuffers(1,&ebo_);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ebo_);
    glBufferData(
        GL_ELEMENT_ARRAY_BUFFER,
        sizeof(unsigned int)*s_indices_.size(),
        s_indices_.data(),
        GL_STATIC_DRAW);

    glVertexAttribPointer(
        0,
        decltype(Vertex::pos)::length(),
        GL_FLOAT,
        GL_FALSE,
        sizeof(Vertex),
        (void*)(sizeof(float)*0));
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
  }

  void Wireframe::draw(Shader& shader) const 
  {
    shader.use();
    glm::mat4 transform=this->getTransform();
    glUniformMatrix4fv(
        glGetUniformLocation(shader.get(),"trans"),
        1,GL_FALSE,glm::value_ptr(transform));
    glUniform3f(
        glGetUniformLocation(shader.get(),"color"),
        color.r(),color.g(),color.b());
    glLineWidth(stroke_);
    glBindVertexArray(vao_);
    glDrawElements(GL_LINES, s_indices_.size(), GL_UNSIGNED_INT, nullptr);
    if(glGetError()!=GL_NO_ERROR){
      throw std::runtime_error("failed to set viewport");
    }
    glBindVertexArray(0);
  }

  Wireframe::~Wireframe() noexcept
  {
    glDeleteBuffers(1,&ebo_);
    glDeleteBuffers(1,&vbo_);
    glDeleteVertexArrays(1,&vao_);
  }

  const std::array<Wireframe::Vertex,8> Wireframe::s_vertices_={{ 
    {{-0.5f,-0.5f,-0.5f}}, // 0
    {{ 0.5f,-0.5f,-0.5f}}, // 1
    {{ 0.5f, 0.5f,-0.5f}}, // 2
    {{-0.5f, 0.5f,-0.5f}}, // 3

    {{-0.5f,-0.5f, 0.5f}}, // 4
    {{ 0.5f,-0.5f, 0.5f}}, // 5
    {{ 0.5f, 0.5f, 0.5f}}, // 6
    {{-0.5f, 0.5f, 0.5f}}, // 7
  }};

  const std::array<unsigned int,36> Wireframe::s_indices_={{
    0,1, 1,2, 2,3, 3,0,   // bottom
    4,5, 5,6, 6,7, 7,4,   // top
    0,4, 1,5, 2,6, 3,7,    // sides
    0,2, 4,6, 0,5, 3,6,
    0,7, 1,6
  }};
}
