#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stdexcept>

namespace piksel{

  class GladInitializer{
  public:
    GladInitializer()
    {
      if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
      {
        std::runtime_error("failed to init GLAD");
      }
    }
  };
}
