#include "piksel/window.hh"

#include <GLFW/glfw3.h>

#include "piksel/exception.hh"

namespace piksel
{
  static constexpr Exception::Type kExceptionType=Exception::Type::WindowError;

  Window::Window(const char* title)
    :Window(title,{0,0})
  {
  }

  Window::Window(const char* title, WindowSize size)
    :title_(title)
  {
    glfwInit();
    if(glfwGetError(NULL)!=GLFW_NO_ERROR)
    {
      throw Exception(kExceptionType,"Failed to init glfw");
    }
#ifdef RASPBERRY_PI
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,0);
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
#else
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#endif

    if(size.height==0||size.width==0)
    {
      size=this->getMonitorSize();
      size.height*=0.8;
      size.width*=0.8;
    }
    p_window_=glfwCreateWindow(size.width,size.height,title_,NULL,NULL);
    if(glfwGetError(NULL)!=GLFW_NO_ERROR)
    {
      glfwTerminate();
      throw Exception(kExceptionType,"Failed to create window");
    }

    glfwMakeContextCurrent(p_window_);
    if(glfwGetError(NULL)!=GLFW_NO_ERROR)
    {
      glfwDestroyWindow(p_window_);
      glfwTerminate();
      throw Exception(kExceptionType,"Failed to create window");
    }

    glfwSetInputMode(p_window_, GLFW_CURSOR, GLFW_CURSOR_DISABLED);   
    if(glfwGetError(NULL)!=GLFW_NO_ERROR)
    {
      glfwDestroyWindow(p_window_);
      glfwTerminate();
      throw Exception(kExceptionType,"Failed to create window");
    }

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
      glfwDestroyWindow(p_window_);
      glfwTerminate();
      throw Exception(kExceptionType,"Failed to load glad");
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

  Window::WindowSize Window::getWindowSize() const
  {
    WindowSize size;
    glfwGetFramebufferSize(p_window_,&size.width,&size.height);
    return size;
  }

  Window::WindowSize Window::getMonitorSize() const
  {
    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode=glfwGetVideoMode(monitor);

    return {mode->width,mode->height};
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
