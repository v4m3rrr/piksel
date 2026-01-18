#include "piksel/gui_object.hh"

#include <imgui.h>

namespace piksel
{
  void GuiObject::checkBox(std::string_view text,bool* value)
  {
    ImGui::Checkbox(text.data(),value);
  }

  void GuiObject::text(std::string_view text)
  {
    ImGui::Text("%s",text.data());
  }

  void GuiObject::slider(std::string_view label,float min,float max, float* value)
  {
    ImGui::SliderFloat(label.data(),value,min,max);
  }

  bool GuiObject::collapsingHeader(std::string_view label)
  {
    return ImGui::CollapsingHeader(label.data());
  }

  void GuiObject::color(std::string_view label, glm::vec3& color)
  {
    float values[3];
    ImGui::ColorEdit3(label.data(),values);
    color.r=values[0];
    color.g=values[1];
    color.b=values[2];
  }
  
  void GuiObject::sameLine()
  {
    ImGui::SameLine();
  }
}
