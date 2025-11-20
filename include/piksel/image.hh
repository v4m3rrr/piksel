#pragma once

#include <string_view>
#include <memory>

namespace piksel
{
  class Image
  {
  public:
    Image(std::string_view path, int desired_channels=0, bool should_flip=true);
    const unsigned char* get() const;
  public:
    int width;
    int height;
    int channels;
  private:
    std::unique_ptr<unsigned char,void(*)(void*)>p_data_;
  };
}
