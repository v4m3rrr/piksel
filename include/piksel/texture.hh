#pragma once

#include "piksel/piksel.hh"
#include "piksel/image.hh"

#include <string_view>

namespace piksel
{
  class Texture{
  public:
    Texture(std::string_view path, int texture_unit);
    Texture(const Texture&)=delete;
    Texture(Texture&& other) noexcept;

    Texture& operator=(const Texture&)=delete;
    Texture& operator=(Texture&& other) noexcept;

    ~Texture() noexcept;

    void bind();
    void setActiveTexture(int texture_unit);
    int getTextureUnit() const;
  private:
    static constexpr int DESIRED_CHANNELS=4;
  private:
    GLuint texture_;
    int texture_unit_;

    Image image_;
  };
}
  

