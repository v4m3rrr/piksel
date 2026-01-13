#include "piksel/mesh.hh"

#include <glm/ext/matrix_transform.hpp>
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
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
  }

  Mesh::Mesh(Mesh&& other) noexcept
    : vao_(other.vao_),
      vbo_(other.vbo_),
      ebo_(other.ebo_),
      vertices_(std::move(other.vertices_)),
      indices_(std::move(other.indices_))
  {
    other.vao_ = 0;
    other.vbo_ = 0;
    other.ebo_ = 0;
  }

  Mesh& Mesh::operator=(Mesh&& other)
  {
    vao_=other.vao_;
    vbo_=other.vbo_;
    ebo_=other.ebo_;
    vertices_=std::move(other.vertices_);
    indices_=std::move(other.indices_);

    other.vao_ = 0;
    other.vbo_ = 0;
    other.ebo_ = 0;

    return *this;
  }

  Mesh::~Mesh() noexcept
  {
    glDeleteBuffers(1,&ebo_);
    glDeleteBuffers(1,&vbo_);
    glDeleteVertexArrays(1,&vao_);
  }

}
