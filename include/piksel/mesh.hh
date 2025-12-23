#pragma once

#include "piksel/object.hh"

#include <glm/glm.hpp>
#include <glad/glad.h>

#include <vector>
#include <string>

namespace piksel
{
  class Mesh : public Object
  {
  public:
    struct Vertex
    {
      glm::vec3 pos;
      glm::vec2 uv;
    };
  public:
    Mesh(
        std::string_view name,
        const std::vector<Vertex>& vertices,
        const std::vector<unsigned int>& indices);
    Mesh(
        std::string_view name,
        const std::vector<Vertex>& vertices,
        const std::vector<unsigned int>& indices,
        const glm::mat4& transform);
    Mesh(const Mesh& other)=delete;
    Mesh(Mesh&& other) noexcept;

    Mesh& operator=(const Mesh&)=delete;
    Mesh& operator=(Mesh&&)=delete;
    virtual ~Mesh() noexcept;

    virtual void draw(Shader& shader) const override;

    std::vector<Vertex> getVertices() const
    {
      return vertices_;
    }

    std::vector<unsigned int> getIndices() const
    {
      return indices_;
    }

    std::string_view getName() const
    {
      return name_;
    }

  private:
    GLuint vao_,vbo_,ebo_;

    std::vector<Vertex> vertices_;
    std::vector<unsigned int> indices_;

    std::string name_;
  };
}
