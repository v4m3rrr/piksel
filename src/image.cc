#include "piksel/image.hh"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <stdexcept>

namespace piksel
{
  Image::Image(std::string_view path, int desired_channels,bool should_flip)
    : p_data_(nullptr,stbi_image_free)
  {
    stbi_set_flip_vertically_on_load(should_flip);

    p_data_.reset(
        stbi_load(path.data(),&width,&height,&channels,desired_channels));
    if(p_data_.get()==nullptr)
    {
      throw std::runtime_error("Failed to load image");
    }
  }

  const unsigned char* Image::get() const
  {
    return p_data_.get();
  }
}
