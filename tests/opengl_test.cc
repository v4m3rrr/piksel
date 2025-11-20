#include "piksel/piksel.hh"
#include "piksel/window.hh"
#include "piksel/graphics.hh"
#include "piksel/shader.hh"
#include "piksel/texture.hh"

using namespace piksel;

int main(int argc, char **argv)
{

  Window wnd("Test",800,600);
  Graphics gfx(wnd);

  float vertices[] = {
      // positions          // colors           // texture coords
       0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
       0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
      -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
      -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
  };
  unsigned int indices[] = {
      0, 1, 3, // first triangle
      1, 2, 3  // second triangle
  };
  GLuint vao;
  glGenVertexArrays(1, &vao); 
  glBindVertexArray(vao);

  GLuint vbo;
  glGenBuffers(1,&vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);

  GLuint ebo;
  glGenBuffers(1,&ebo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices),indices,GL_STATIC_DRAW);

  // pos
  glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,8*sizeof(float),(void*)0);
  glEnableVertexAttribArray(0);

  // colors
  glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,8*sizeof(float),(void*)(3*sizeof(float)));
  glEnableVertexAttribArray(1);

  // tex cords
  glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE,8*sizeof(float),(void*)(6*sizeof(float)));
  glEnableVertexAttribArray(2);

  Texture tex0("textures/container.jpg",0);
  Texture tex1("textures/awesomeface.png",1);

  Shader shader("shaders/default.vert","shaders/default.frag");
  shader.use();

  shader.set("texture0",tex0.getTextureUnit());
  shader.set("texture1",tex1.getTextureUnit());

  while(wnd)
  {
    if(wnd.getKey(GLFW_KEY_ESCAPE)==Window::KeyState::Press)
      wnd.close();

    gfx.clear(Color::Black);

    tex0.bind();
    tex1.bind();
    shader.use();
    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);
    wnd.update();
  }

  glDeleteBuffers(1,&ebo);
  glDeleteBuffers(1,&vbo);
  glDeleteVertexArrays(1,&vao);

  return 0;
}

