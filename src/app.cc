#include "piksel/app.hh"

namespace piksel
{
  App::App(std::string_view title, int width, int height)
    :wnd(title.data(),width,height),gfx(wnd)
  {
  }
}
