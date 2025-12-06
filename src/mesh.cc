#include "piksel/mesh.hh"
#include "piksel/shader.hh"

#include <stdexcept>
#include <vector>

namespace piksel
{
  Mesh::Mesh(
      const std::vector<Vertex>& vertices,
      const std::vector<unsigned int>& indices)
    : vertices_(vertices),indices_(indices)
  {
    glGenVertexArrays(1,&vao_);
    glBindVertexArray(vao_);

    glGenBuffers(1,&vbo_);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_);
    glBufferData(
        GL_ARRAY_BUFFER,
        sizeof(Vertex)*vertices_.size(),
        vertices_.data(),
        GL_STATIC_DRAW);

    glGenBuffers(1,&ebo_);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_);
    glBufferData(
        GL_ELEMENT_ARRAY_BUFFER,
        sizeof(unsigned int)*indices_.size(),
        indices_.data(),
        GL_STATIC_DRAW);

    glVertexAttribPointer(
        0,
        decltype(Vertex::pos)::length(),
        GL_FLOAT,
        GL_FALSE,
        sizeof(Vertex),
        (void *)0);
    //glEnableVertexArrayAttrib(vao_,0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(
        1,
        decltype(Vertex::uv)::length(),
        GL_FLOAT,
        GL_FALSE,
        sizeof(Vertex),
        (void *)sizeof(Vertex::pos));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
  }

  Mesh::~Mesh() noexcept
  {
    glDeleteBuffers(1,&ebo_);
    glDeleteBuffers(1,&vbo_);
    glDeleteVertexArrays(1,&vao_);
  }

  void Mesh::draw(Shader& shader) const
  {
    shader.use();
    glDrawElements(
        GL_TRIANGLES,indices_.size(),GL_UNSIGNED_INT,0);
    if(glGetError()!=GL_NO_ERROR){
      std::runtime_error("failed to set viewport");
    }
  }
}
