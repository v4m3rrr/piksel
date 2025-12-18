#pragma once

#include "piksel/object.hh"

namespace piksel { 
  class Wireframe : public Object{ 
  public:
    struct Vertex
    {
      glm::vec3 pos;
    };
  public:
    Wireframe(float stroke);
    virtual ~Wireframe() noexcept;

    void draw(Shader& shader) const override;
  private:
    GLuint vao_,vbo_,ebo_;
    float stroke_;
  private:
    const static std::array<Vertex,8> s_vertices_;
    const static std::array<unsigned int,36> s_indices_;
  };
}
