#include "piksel/model.hh"

#include "piksel/shader.hh"

#include <glm/ext/matrix_transform.hpp>
#include <glm/fwd.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>


namespace piksel
{
  std::vector<Object>& Model::getObjects()
  {
    return objects_;
  }

  void Model::draw(Shader& shader) const
  {
    shader.use();
    for(const auto& object:objects_)
    {
      object.draw(shader);
    }
  }

}
