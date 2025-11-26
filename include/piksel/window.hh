#pragma once 

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <cstdint>

namespace piksel
{
  class Window
  {
  public:
    friend class Graphics;
  public:
    enum class KeyState
    {
      Release=GLFW_RELEASE,
      Press=GLFW_PRESS
    };
  public:
    Window(const char* title, uint32_t width, uint32_t height);
    Window(const Window&)=delete;
    
    Window& operator=(const Window&)=delete;
    KeyState getKey(int glfw_code) const;

    void update();
    void close();

    explicit operator bool() const;

    ~Window();
  private:
    const char* title_;

    const uint32_t width_;
    const uint32_t height_;

    GLFWwindow* p_window_;
  };
}
