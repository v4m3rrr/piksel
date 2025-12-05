#include "piksel/texture.hh"


namespace piksel
{
  Texture::Texture(std::string_view path)
    :image_(path,DESIRED_CHANNELS)
  {
    glGenTextures(1,&texture_);
    glBindTexture(GL_TEXTURE_2D,texture_);

    glTexParameteri(
        GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);

    glTexImage2D(
        GL_TEXTURE_2D,0,GL_RGBA,
        image_.width,image_.height,0,
        GL_RGBA,GL_UNSIGNED_BYTE,image_.get());
    glGenerateMipmap(GL_TEXTURE_2D);
  }

  Texture::Texture(Texture&& other) noexcept
    :texture_(other.texture_),image_(std::move(other.image_))
  {
    other.texture_=0;
  }

  Texture& Texture::operator=(Texture&& other) noexcept
  {
    if(this != &other)
    {
      texture_=other.texture_;
      image_=std::move(other.image_);

      other.texture_=0;
    }

    return *this;
  }

  Texture::~Texture() noexcept
  {
    if(texture_!=0)
      glDeleteTextures(1,&texture_);
  }
}
