#pragma once

#include "piksel/object.hh"

#include <glm/gtc/matrix_transform.hpp>

#include <string_view>
#include <array>
#include <vector>

namespace piksel { 
  class Cube : public Object{ 
  public:
    Cube(
        float width,float height,float depth,
        std::string_view tex_filename)
      :Object(
          std::vector<Vertex>(vertices.begin(),vertices.end()),
          std::vector<unsigned int>(indices.begin(),indices.end()),
          tex_filename)
    {
      scale=glm::scale(scale,{width,height,depth});
    }

    Cube(
        std::string_view tex_filename)
      :Cube(1.f,1.f,1.f,tex_filename)
    {}

  private:
    static constexpr std::array<Object::Vertex,24> vertices={{ 
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
    
    static constexpr std::array<unsigned int,36> indices = {
       0,  1,  2,  2,  3,  0,   // back
       4,  5,  6,  6,  7,  4,   // front
       8,  9, 10, 10,  4,  8,   // left
      11,  2, 13, 13, 14, 11,   // right
      17, 16, 18, 17, 19, 18,   // bottom
      20, 21, 23, 20, 22, 23    // top
    };
  };
}
