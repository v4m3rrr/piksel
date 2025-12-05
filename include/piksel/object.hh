#pragma once

#include "piksel/texture.hh"

#include <glm/glm.hpp>
#include <glad/glad.h>

#include <vector>
#include <string_view>

namespace piksel
{
  class Object
  {
  public:
    struct Vertex
    {
      glm::vec3 pos;
      glm::vec2 tex_coords;
    };
  public:
    glm::mat4 translate;
    glm::mat4 rotate;
    glm::mat4 scale;
    Texture texture;
  protected:
    Object(
        const std::vector<Vertex>& vertices, 
        const std::vector<unsigned int>& indices,
        std::string_view tex_filename);
    virtual ~Object() noexcept;
  private:
    // TODO
    // There is memory optimalization
    // for example when we create cube we need only one 
    // verteicies array and indices for ALL cubes
    // maybe somekind of shared ptr to resources
    // for now we keep it simple
    const std::vector<Vertex> vertices_;
    const std::vector<unsigned int> indices_;

    GLuint vao_,vbo_,ebo_;
  };
}
