#pragma once

#include "piksel/object.hh"
#include "piksel/texture.hh"

#include <string_view>
#include <array>

namespace piksel { 
  class Cube : public Object{ 
  public:
    struct Vertex
    {
      glm::vec3 pos;
      glm::vec2 tex_coords;
    };
  public:
    Cube(
        float width,float height,float depth,
        std::string_view tex_filename);
    Cube(std::string_view tex_filename);
    virtual ~Cube() noexcept;

    void draw(Shader& shader) const override;

  public:
    Texture texture;
  private:
    GLuint vao_,vbo_,ebo_;

    static const std::array<Vertex,24> s_vertices_;
    static const std::array<unsigned int,36> s_indices_;
  };
}
