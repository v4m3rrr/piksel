#pragma once 

#include <glad/glad.h>
#include <GLFW/glfw3.h>

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
    struct MousePos
    {
      double x;
      double y;
    };
    struct WindowSize
    {
      int width;
      int height;
    };
  public:
    Window(const char* title);
    Window(const char* title, WindowSize size);
    Window(const Window&)=delete;
    
    Window& operator=(const Window&)=delete;
    KeyState getKey(int glfw_code) const;
    MousePos getMousePos() const;
    void setCursor(bool enable=true);
    WindowSize getWindowSize() const;
    WindowSize getMonitorSize() const;

    GLFWwindow* getGLFWPointer() {return p_window_;}

    void update();
    void close();

    explicit operator bool() const;

    ~Window();
  private:
    const char* title_;

    GLFWwindow* p_window_;
  };
}
