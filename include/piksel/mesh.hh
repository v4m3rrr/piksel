#pragma once

#include "piksel/object.hh"

#include <glm/glm.hpp>
#include <glad/glad.h>

#include <vector>

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
        const std::vector<Vertex>& vertices,
        const std::vector<unsigned int>& indices);
    virtual ~Mesh() noexcept;

    virtual void draw(Shader& shader) const override;
  private:
    GLuint vao_,vbo_,ebo_;

    std::vector<Vertex> vertices_;
    std::vector<unsigned int> indices_;
  };
}
