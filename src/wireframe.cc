#include "piksel/wireframe.hh"

#include "piksel/object.hh"
#include "piksel/shader.hh"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <stdexcept>
#include <vector>

namespace piksel
{
  Wireframe::Wireframe(float stroke)
    :
      Object(s_mesh),
      stroke_(stroke)
  {
  }

  void Wireframe::draw(Shader& shader) const 
  {
    shader.use();
    shader.set("trans",this->getTransform());
    shader.set("color",this->getColor().rgb());

    glLineWidth(stroke_);
    glBindVertexArray(vao_);
    glDrawElements(GL_LINES, s_indices_.size(), GL_UNSIGNED_INT, nullptr);
    if(glGetError()!=GL_NO_ERROR){
      throw std::runtime_error("failed to set viewport");
    }
    glBindVertexArray(0);
  }

  const std::vector<Mesh::Vertex> Wireframe::s_vertices_={{ 
    {{-0.5f,-0.5f,-0.5f}}, // 0
    {{ 0.5f,-0.5f,-0.5f}}, // 1
    {{ 0.5f, 0.5f,-0.5f}}, // 2
    {{-0.5f, 0.5f,-0.5f}}, // 3

    {{-0.5f,-0.5f, 0.5f}}, // 4
    {{ 0.5f,-0.5f, 0.5f}}, // 5
    {{ 0.5f, 0.5f, 0.5f}}, // 6
    {{-0.5f, 0.5f, 0.5f}}, // 7
  }};

  const std::vector<unsigned int> Wireframe::s_indices_={{
    0,1, 1,2, 2,3, 3,0,   // bottom
    4,5, 5,6, 6,7, 7,4,   // top
    0,4, 1,5, 2,6, 3,7,    // sides
    0,2, 4,6, 0,5, 3,6,
    0,7, 1,6
  }};

  const std::shared_ptr<const Mesh> Wireframe::s_mesh=
    std::make_shared<const Mesh>(s_vertices_,s_indices_);
}
