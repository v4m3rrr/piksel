#include "piksel/gui_manager.hh"

#include "imgui.h"
#include "imgui_impl_opengl3.h"

#include <GLFW/glfw3.h>

namespace piksel
{
  GuiManager::GuiManager(GLFWwindow* p_window)
  {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.IniFilename = NULL;
    io.LogFilename = NULL;

    ImGui::StyleColorsDark();
    float xscale, yscale;
    glfwGetWindowContentScale(p_window, &xscale, &yscale);

    io.Fonts->Clear();
    io.Fonts->AddFontDefault();

    io.FontGlobalScale = xscale;
    io.Fonts->Build();
    ImGui::GetStyle().ScaleAllSizes(xscale);

    // When window switches from one monitor to another
    glfwSetWindowContentScaleCallback(
        p_window,
        [](GLFWwindow*, float xscale, float)
        {
            float dpiScale = xscale;
            ImGui::GetStyle().ScaleAllSizes(dpiScale);
            ImGui::GetIO().FontGlobalScale = dpiScale;
        }
    );

#ifdef RASPBERRY_PI
    const char* glsl_version = "#version 300 es";
#else
    const char* glsl_version = "#version 130";
#endif
    ImGui_ImplGlfw_InitForOpenGL(p_window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);
  }

  GuiManager::~GuiManager() noexcept
  {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
  }

  void GuiManager::render()
  {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    if(ignore_input_)
      ImGui::Begin(
          "Piksel Gui",
          nullptr,
          ImGuiWindowFlags_NoInputs | 
          ImGuiWindowFlags_NoMove | 
          ImGuiWindowFlags_NoResize |
          ImGuiWindowFlags_AlwaysAutoResize);
    else
      ImGui::Begin(
          "Piksel Gui",
          nullptr,
          ImGuiWindowFlags_AlwaysAutoResize);

    for(size_t i=0;i<objects_.size();i++)
    {
      ImGui::PushID(i);
      if (ImGui::CollapsingHeader(
            objects_[i]->getTitle().data(),
            ImGuiTreeNodeFlags_DefaultOpen))
        objects_[i]->draw();
      
      ImGui::PopID();
    }

    ImGui::End();
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
  }
  
  void GuiManager::ignoreInput(bool enable)
  {
    ignore_input_=enable;
  }

  void GuiManager::addObject(std::shared_ptr<GuiObject> object)
  {
    objects_.push_back(object);
  }

  void GuiManager::clear()
  {
    objects_.clear();
  }
}
