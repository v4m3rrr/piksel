#pragma once

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

namespace piksel
{
  struct Vertex{
    Vertex(const glm::vec3& pos, const glm::vec3& color, const glm::vec2& tex_cord)
      :pos(pos),color(color),tex_cord(tex_cord)
    {}

    glm::vec3 pos;
    glm::vec3 color;
    glm::vec2 tex_cord;
  };
}
