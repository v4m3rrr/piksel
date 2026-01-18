#include "piksel/window.hh"

#include <GLFW/glfw3.h>

#include <stdexcept>

namespace piksel
{
  Window::Window(const char* title, uint32_t width, uint32_t height)
    :title_(title),width_(width),height_(height)
  {
    glfwInit();
#ifdef RASPBERRY_PI
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,0);
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
#else
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
    // Tells that we only use core features
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#endif

    p_window_=glfwCreateWindow(width_,height_,title_,NULL,NULL);
    if(p_window_==NULL)
    {
      glfwTerminate();
      throw std::runtime_error("Failed to create window");
    }

    glfwMakeContextCurrent(p_window_);

    //if(glfwRawMouseMotionSupported())
    //  glfwSetInputMode(p_window_, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
    //else{
    //  throw std::runtime_error("Unsupported raw mouse motion");
    //}
    glfwSetInputMode(p_window_, GLFW_CURSOR, GLFW_CURSOR_DISABLED);   

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
      throw std::runtime_error("failed to init GLAD");
    }
  }

  Window::KeyState Window::getKey(int glfw_code) const
  {
    return (KeyState)glfwGetKey(p_window_,glfw_code);
  }

  Window::MousePos Window::getMousePos() const
  {
    double x,y;
    glfwGetCursorPos(p_window_,&x,&y);

    return {x,y};
  }

  void Window::setCursor(bool enable)
  {
    if(enable)
      glfwSetInputMode(p_window_, GLFW_CURSOR, GLFW_CURSOR_NORMAL);   
    else
      glfwSetInputMode(p_window_, GLFW_CURSOR, GLFW_CURSOR_DISABLED);   
  }

  void Window::update()
  {
    glfwSwapBuffers(p_window_);
    glfwPollEvents();
  }

  void Window::close()
  {
    glfwSetWindowShouldClose(p_window_, true);
  }

  Window::operator bool() const
  {
    return !glfwWindowShouldClose(p_window_);
  }

  Window::~Window()
  {
    glfwDestroyWindow(p_window_);
    glfwTerminate();
  }
}
