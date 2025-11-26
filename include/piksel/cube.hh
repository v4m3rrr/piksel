#pragma once

#include <glm/glm.hpp> 
#include <glm/gtc/matrix_transform.hpp>

#include <string_view>

#include "piksel/texture.hh"

namespace piksel { 
  struct Cube{ 
    Cube(float angle, 
        const glm::vec3& axis, 
        const glm::vec3& pos, 
        std::string_view tex_filename,
        int tex_unit)
      :trans(1.0f),tex(tex_filename,tex_unit)
    {
      trans=glm::translate(trans,pos);
      trans=glm::rotate(trans,glm::radians(angle),axis);
    }

    static constexpr float vertices[24][5] = { 
      {-0.5f,-0.5f,-0.5f, 0.0f,0.0f}, // 0
      { 0.5f,-0.5f,-0.5f, 1.0f,0.0f}, // 1
      { 0.5f, 0.5f,-0.5f, 1.0f,1.0f}, // 2
      {-0.5f, 0.5f,-0.5f, 0.0f,1.0f}, // 3

      {-0.5f,-0.5f, 0.5f, 0.0f,0.0f}, // 4
      { 0.5f,-0.5f, 0.5f, 1.0f,0.0f}, // 5
      { 0.5f, 0.5f, 0.5f, 1.0f,1.0f}, // 6
      {-0.5f, 0.5f, 0.5f, 0.0f,1.0f}, // 7

      {-0.5f, 0.5f, 0.5f, 1.0f,0.0f}, // 8 
      {-0.5f, 0.5f,-0.5f, 1.0f,1.0f}, // 9
      {-0.5f,-0.5f,-0.5f, 0.0f,1.0f}, // 10
      { 0.5f, 0.5f, 0.5f, 1.0f,0.0f}, // 11

      {-0.5f,-0.5f, 0.5f, 0.0f,0.0f}, // 12 
      { 0.5f,-0.5f,-0.5f, 0.0f,1.0f}, // 13
      { 0.5f,-0.5f, 0.5f, 0.0f,0.0f}, // 14
      {-0.5f, 0.5f,-0.5f, 0.0f,1.0f}, // 15
                                      
      {-0.5f,-0.5f, 0.5f, 0.0f,1.0f}, // 16
      {-0.5f,-0.5f,-0.5f, 0.0f,0.0f}, // 17
      { 0.5f,-0.5f, 0.5f, 1.0f,1.0f}, // 18
      { 0.5f,-0.5f,-0.5f, 1.0f,0.0f}, // 19
                                       
      {-0.5f, 0.5f, 0.5f, 0.0f,0.0f}, // 20
      { 0.5f, 0.5f, 0.5f, 1.0f,0.0f}, // 21
      {-0.5f, 0.5f,-0.5f, 0.0f,1.0f}, // 22
      { 0.5f, 0.5f,-0.5f, 1.0f,1.0f}  // 23
    };
    
    static constexpr unsigned int indices[] = {
       0,  1,  2,  2,  3,  0,   // back
       4,  5,  6,  6,  7,  4,   // front
       8,  9, 10, 10,  4,  8,   // left
      11,  2, 13, 13, 14, 11,   // right
      17, 16, 18, 17, 19, 18,   // bottom
      20, 21, 23, 20, 22, 23    // top
    };

    constexpr static unsigned int size=sizeof(vertices);
    constexpr static unsigned int pos_elem=3;
    constexpr static unsigned int tex_elem=2;
    constexpr static unsigned int stride_size=sizeof(float)*(pos_elem+tex_elem);
    constexpr static unsigned int pos_offset=sizeof(float)*0;
    constexpr static unsigned int tex_offset=sizeof(float)*pos_elem;
    constexpr static unsigned int indices_len=sizeof(indices)/sizeof(unsigned int);

    glm::mat4 trans;
    Texture tex;
  };
}
