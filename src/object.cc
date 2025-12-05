#include "piksel/object.hh"
#include <string_view>

namespace piksel
{
  Object::Object(
      const std::vector<Vertex>& vertices, 
      const std::vector<unsigned int>& indices,
      std::string_view tex_filename)
    :translate(1.f),rotate(1.f),scale(1.f),texture(tex_filename),
    vertices_(vertices),indices_(indices)
  {
    glGenVertexArrays(1, &vao_); 
    glBindVertexArray(vao_);

    glGenBuffers(1,&vbo_);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_);
    glBufferData(
        GL_ARRAY_BUFFER,
        sizeof(Vertex)*vertices_.size(),
        vertices_.data(),
        GL_STATIC_DRAW);

    glGenBuffers(1,&ebo_);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ebo_);
    glBufferData(
        GL_ELEMENT_ARRAY_BUFFER,
        sizeof(unsigned int)*indices_.size(),
        indices_.data(),
        GL_STATIC_DRAW);

    constexpr auto pos_elems=glm::vec3::length();
    constexpr auto tex_elems=glm::vec2::length();
    glVertexAttribPointer(
        0,
        pos_elems,
        GL_FLOAT,
        GL_FALSE,
        sizeof(float)*pos_elems*tex_elems,
        (void*)(sizeof(float)*0));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(
        1,
        tex_elems,
        GL_FLOAT,
        GL_FALSE,
        sizeof(float)*pos_elems*tex_elems,
        (void*)(sizeof(float)*pos_elems));
    glEnableVertexAttribArray(1);
  }

  Object::~Object() noexcept
  {
    glDeleteBuffers(1,&ebo_);
    glDeleteBuffers(1,&vbo_);
    glDeleteVertexArrays(1,&vao_);
  }
}
