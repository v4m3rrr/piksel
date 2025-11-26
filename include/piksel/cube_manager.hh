#pragma once

#include <glad/glad.h>

namespace piksel
{
  class CubeManager
  {
  public:
    CubeManager();
    void use();
    ~CubeManager() noexcept;
  private:
    GLuint vao_;
    GLuint vbo_;
    GLuint ebo_;
  };
}
