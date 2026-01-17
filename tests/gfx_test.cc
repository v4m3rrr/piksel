#include "piksel/graphics.hh"

using namespace piksel;
int main()
{
  Window win("chuj",720,640);
  Camera cam({0.f,0.f,0.f},{0.f,0.f,10.f});
  Graphics gfx(win,cam,
      PIKSEL_SHADERS_PATH"/single_color_es.vert",
      PIKSEL_SHADERS_PATH"/single_color_es.frag");
}
