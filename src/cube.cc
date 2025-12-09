#include "piksel/cube.hh"

#include <glm/gtc/matrix_transform.hpp>

#include <stdexcept>

namespace piksel
{
  Cube::Cube(
      float width,float height,float depth,
      std::string_view tex_filename)
    :texture(tex_filename)
  {
    glGenVertexArrays(1, &vao_); 
    glBindVertexArray(vao_);

    glGenBuffers(1,&vbo_);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_);
    glBufferData(
        GL_ARRAY_BUFFER,
        sizeof(Vertex)*s_vertices_.size(),
        s_vertices_.data(),
        GL_STATIC_DRAW);

    glGenBuffers(1,&ebo_);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ebo_);
    glBufferData(
        GL_ELEMENT_ARRAY_BUFFER,
        sizeof(unsigned int)*s_indices_.size(),
        s_indices_.data(),
        GL_STATIC_DRAW);

    glVertexAttribPointer(
        0,
        decltype(Vertex::pos)::length(),
        GL_FLOAT,
        GL_FALSE,
        sizeof(Vertex),
        (void*)(sizeof(float)*0));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(
        1,
        decltype(Vertex::tex_coords)::length(),
        GL_FLOAT,
        GL_FALSE,
        sizeof(Vertex),
        (void*)(sizeof(Vertex::pos)));
    glEnableVertexAttribArray(1);
    glBindVertexArray(0);

    scale=glm::scale(scale,{width,height,depth});
  }

  Cube::Cube(std::string_view tex_filename)
    :Cube(1.f,1.f,1.f,tex_filename)
  {}

  void Cube::draw(Shader& shader) const 
  {
    shader.use();
    glBindVertexArray(vao_);
    glDrawElements(GL_TRIANGLES,s_indices_.size(),GL_UNSIGNED_INT,0);
    if(glGetError()!=GL_NO_ERROR){
      throw std::runtime_error("failed to set viewport");
    }
    glBindVertexArray(0);
  }

  Cube::~Cube() noexcept
  {
    glDeleteBuffers(1,&ebo_);
    glDeleteBuffers(1,&vbo_);
    glDeleteVertexArrays(1,&vao_);
  }
  const std::array<Cube::Vertex,24> Cube::s_vertices_={{ 
    {{-0.5f,-0.5f,-0.5f}, {0.0f,0.0f}}, // 0
    {{ 0.5f,-0.5f,-0.5f}, {1.0f,0.0f}}, // 1
    {{ 0.5f, 0.5f,-0.5f}, {1.0f,1.0f}}, // 2
    {{-0.5f, 0.5f,-0.5f}, {0.0f,1.0f}}, // 3

    {{-0.5f,-0.5f, 0.5f}, {0.0f,0.0f}}, // 4
    {{ 0.5f,-0.5f, 0.5f}, {1.0f,0.0f}}, // 5
    {{ 0.5f, 0.5f, 0.5f}, {1.0f,1.0f}}, // 6
    {{-0.5f, 0.5f, 0.5f}, {0.0f,1.0f}}, // 7

    {{-0.5f, 0.5f, 0.5f}, {1.0f,0.0f}}, // 8 
    {{-0.5f, 0.5f,-0.5f}, {1.0f,1.0f}}, // 9
    {{-0.5f,-0.5f,-0.5f}, {0.0f,1.0f}}, // 10
    {{ 0.5f, 0.5f, 0.5f}, {1.0f,0.0f}}, // 11

    {{-0.5f,-0.5f, 0.5f}, {0.0f,0.0f}}, // 12 
    {{ 0.5f,-0.5f,-0.5f}, {0.0f,1.0f}}, // 13
    {{ 0.5f,-0.5f, 0.5f}, {0.0f,0.0f}}, // 14
    {{-0.5f, 0.5f,-0.5f}, {0.0f,1.0f}}, // 15
                                    
    {{-0.5f,-0.5f, 0.5f}, {0.0f,1.0f}}, // 16
    {{-0.5f,-0.5f,-0.5f}, {0.0f,0.0f}}, // 17
    {{ 0.5f,-0.5f, 0.5f}, {1.0f,1.0f}}, // 18
    {{ 0.5f,-0.5f,-0.5f}, {1.0f,0.0f}}, // 19
                                     
    {{-0.5f, 0.5f, 0.5f}, {0.0f,0.0f}}, // 20
    {{ 0.5f, 0.5f, 0.5f}, {1.0f,0.0f}}, // 21
    {{-0.5f, 0.5f,-0.5f}, {0.0f,1.0f}}, // 22
    {{ 0.5f, 0.5f,-0.5f}, {1.0f,1.0f}}  // 23
  }};
  
  const std::array<unsigned int,36> Cube::s_indices_ = {
     0,  1,  2,  2,  3,  0,   // back
     4,  5,  6,  6,  7,  4,   // front
     8,  9, 10, 10,  4,  8,   // left
    11,  2, 13, 13, 14, 11,   // right
    17, 16, 18, 17, 19, 18,   // bottom
    20, 21, 23, 20, 22, 23    // top
  };
}
