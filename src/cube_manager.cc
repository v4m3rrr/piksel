#include "piksel/cube_manager.hh"

#include "piksel/cube.hh"

namespace piksel
{
  CubeManager::CubeManager()
  {
    glGenVertexArrays(1, &vao_); 
    glBindVertexArray(vao_);

    glGenBuffers(1,&vbo_);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_);
    glBufferData(GL_ARRAY_BUFFER,sizeof(Cube::vertices),Cube::vertices,GL_STATIC_DRAW);

    glGenBuffers(1,&ebo_);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ebo_);
    glBufferData(
        GL_ELEMENT_ARRAY_BUFFER,sizeof(Cube::indices),Cube::indices,GL_STATIC_DRAW);

    // pos
    glVertexAttribPointer(
        0,Cube::pos_elem,GL_FLOAT,GL_FALSE,Cube::stride_size,(void*)Cube::pos_offset);
    glEnableVertexAttribArray(0);

    // tex cords
    glVertexAttribPointer(
        1,Cube::tex_elem,GL_FLOAT,GL_FALSE,Cube::stride_size,(void*)Cube::tex_offset);
    glEnableVertexAttribArray(1);
  }

  void CubeManager::use()
  {
    glBindVertexArray(vao_);
  }

  CubeManager::~CubeManager() noexcept
  {
    glDeleteBuffers(1,&ebo_);
    glDeleteBuffers(1,&vbo_);
    glDeleteVertexArrays(1,&vao_);
  }
}
