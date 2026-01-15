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
        float stroke=1.f, 
        std::string_view shader_path_vert=VERTEX_SHADER_PATH,
        std::string_view shader_path_frag=FRAG_SHADER_PATH);
    void addLine(const Line& line);

    void clear();
    void draw(const glm::mat4& proj_and_view);
  private:
    static constexpr std::string_view VERTEX_SHADER_PATH=
      PIKSEL_SHADERS_PATH"/line.vert";
    static constexpr std::string_view FRAG_SHADER_PATH=
      PIKSEL_SHADERS_PATH"/line.frag";
  private:
    float stroke_;
    GLuint vao_,vbo_;

    Shader shader_;
    std::vector<Vertex> vertices_;
  };
}
