#pragma once

#include <glad/glad.h>

#include "piksel/image.hh"

#include <string_view>

namespace piksel
{
  class Texture{
  public:
    Texture(std::string_view path);
    Texture(const Texture&)=delete;
    Texture(Texture&& other) noexcept;

    Texture& operator=(const Texture&)=delete;
    Texture& operator=(Texture&& other) noexcept;

    ~Texture() noexcept;

    GLuint getId() const {return texture_;}
  private:
    static constexpr int DESIRED_CHANNELS=4;
  private:
    GLuint texture_;

    Image image_;
  };
}
  

