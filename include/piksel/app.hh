#pragma once

#include "piksel/window.hh"
#include "piksel/graphics.hh"

#include <string_view>

namespace piksel
{
  class App{
  public:
    App(std::string_view title, int width, int height);


  private:
    Window wnd;
    Graphics gfx;
  };
}
