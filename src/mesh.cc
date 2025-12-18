#include "piksel/mesh.hh"
#include "piksel/shader.hh"

#include <glm/ext/matrix_transform.hpp>
#include <stdexcept>
#include <vector>

namespace piksel
{
  Mesh::Mesh(
      const std::vector<Vertex>& vertices,
      const std::vector<unsigned int>& indices,
      const glm::mat4& transform)
    :Mesh(vertices,indices)
  {
    const glm::mat4& M=transform;

    glm::vec3 translation = glm::vec3(M[3]);

    glm::vec3 scale;
    scale.x = glm::length(glm::vec3(M[0]));
    scale.y = glm::length(glm::vec3(M[1]));
    scale.z = glm::length(glm::length(glm::vec3(M[2])));

    glm::mat3 rotation;
    rotation[0] = glm::vec3(M[0]) / scale.x;
    rotation[1] = glm::vec3(M[1]) / scale.y;
    rotation[2] = glm::vec3(M[2]) / scale.z;

    this->translate=glm::translate(glm::mat4(1.f),translation);
    this->rotate=glm::mat4(rotation);
    this->scale=glm::scale(glm::mat4(1.f),scale);
  }

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

  Mesh::Mesh(Mesh&& other) noexcept
    :Object(std::move(other))
  {
    if(this != &other)
    {
      vao_=other.vao_;
      vbo_=other.vbo_;
      ebo_=other.ebo_;

      vertices_=std::move(other.vertices_);
      indices_=std::move(other.indices_);

      other.vao_=0;
      other.vbo_=0;
      other.ebo_=0;
    }
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
    glBindVertexArray(vao_);
    glDrawElements(
        GL_LINES,indices_.size(),GL_UNSIGNED_INT,0);
    if(glGetError()!=GL_NO_ERROR){
      std::runtime_error("failed to set viewport");
    }
    glBindVertexArray(0);
  }
}
