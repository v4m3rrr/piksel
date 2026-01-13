#pragma once

#include <glm/glm.hpp>
#include <glad/glad.h>

#include <vector>

namespace piksel
{
  class Mesh
  {
  public:
    struct Vertex
    {
      glm::vec3 pos;
    };
  public:
    Mesh(
        const std::vector<Vertex>& vertices,
        const std::vector<unsigned int>& indices);
    Mesh(const Mesh& other)=delete;
    Mesh(Mesh&& other) noexcept;

    Mesh& operator=(const Mesh&)=delete;
    Mesh& operator=(Mesh&&);
    virtual ~Mesh() noexcept;

    const std::vector<Vertex>& getVertices() const
    {
      return vertices_;
    }

    const std::vector<unsigned int>& getIndices() const
    {
      return indices_;
    }

    void bind() const{glBindVertexArray(vao_);}
  private:
    GLuint vao_,vbo_,ebo_;

    std::vector<Vertex> vertices_;
    std::vector<unsigned int> indices_;
  };
}
