#pragma once

#include "piksel/window.hh"
#include "piksel/color.hh"

namespace piksel
{
  class Graphics
  {
  public:
    Graphics(Window& wnd);

    void clear(Color color);
  private:
    Window& wnd_;
    
    const uint32_t width_;
    const uint32_t height_;
  };
}
