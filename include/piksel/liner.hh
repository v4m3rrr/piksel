#pragma once

#include <glm/glm.hpp>
#include <glad/glad.h>

#include "piksel/line.hh"
#include "piksel/shader.hh"
#include "piksel/config.hh"

#include <string_view>
#include <vector>

namespace piksel
{
  class Liner
  {
  public:
    struct Vertex{
      glm::vec3 pos;
      glm::vec3 color;
    };
  public:
    Liner(
      float stroke = 1.f);
    void addLine(const Line& line);

    void clear();
    void draw(const glm::mat4& proj_and_view);
  private:
    static std::string_view src_code_vertex_sh;
    static std::string_view src_code_frag_sh;
  private:
    float stroke_;
    GLuint vao_,vbo_;

    Shader shader_;
    std::vector<Vertex> vertices_;
  };
}
