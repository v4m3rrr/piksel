#pragma once

#include "piksel/object.hh"
#include <vector>

namespace piksel { 
  class Wireframe : public Object{ 
  public:
    Wireframe(float stroke);

    void draw(Shader& shader) const override;
  private:
    GLuint vao_,vbo_,ebo_;
    float stroke_;
  private:
    const static std::vector<Mesh::Vertex> s_vertices_;
    const static std::vector<unsigned int> s_indices_;

    const static std::shared_ptr<const Mesh> s_mesh;
  };
}
