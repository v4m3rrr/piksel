#pragma once 

#include "piksel/gui_object.hh"

#include "imgui.h"
#include "imgui_impl_glfw.h"

#include <memory>
#include <vector>

namespace piksel
{
  class GuiManager
  {
  public:
    GuiManager(GLFWwindow* p_window);
    GuiManager(const GuiManager&)=delete;
    GuiManager(GuiManager&&)=delete;
    ~GuiManager() noexcept;

    GuiManager& operator=(const GuiManager&)=delete;
    GuiManager& operator=(GuiManager&&)=delete;

    void render();
    void ignoreInput(bool enable=true);
    void addObject(std::shared_ptr<GuiObject> object);
  private:
    std::vector<std::shared_ptr<GuiObject>> objects_;
    bool ignore_input_=false;
  };
}
