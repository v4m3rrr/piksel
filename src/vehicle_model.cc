#include "piksel/vehicle_model.hh"
#include "piksel/shader.hh"

#include <glm/gtc/type_ptr.hpp>

namespace piksel
{
  VehicleModel::VehicleModel(
      Mesh&& rear_left_mesh,
      Mesh&& rear_right_mesh,
      Mesh&& front_left_mesh,
      Mesh&& front_right_mesh,
      Mesh&& chassis_mesh)
    :chassis_mesh_(std::move(chassis_mesh))
  {
    wheel_meshes_.insert(
        {WheelPosition::RearLeft,std::move(rear_left_mesh)});
    wheel_meshes_.insert(
        {WheelPosition::RearRight,std::move(rear_right_mesh)});
    wheel_meshes_.insert(
        {WheelPosition::FrontLeft,std::move(front_left_mesh)});
    wheel_meshes_.insert(
        {WheelPosition::FrontRight,std::move(front_right_mesh)});
  }

  void VehicleModel::draw(Shader& shader) const
  {
    shader.use();
    for(const auto& [_,mesh]:wheel_meshes_)
    {
      glm::mat4 mesh_transform=mesh.getTransform();
      glm::mat4 transform=this->getTransform()*mesh_transform;
      glUniformMatrix4fv(
          glGetUniformLocation(shader.get(),"trans"),
          1,GL_FALSE,glm::value_ptr(transform));
      glUniform3f(
          glGetUniformLocation(shader.get(),"color"),
          color.r(),color.g(),color.b());

      glLineWidth(1.f);
      mesh.draw(shader);
    }
  }

  void VehicleModel::setWheelWorldTransform(
      WheelPosition wheel,const glm::mat4 transform)
  {
    auto it = wheel_meshes_.find(wheel);
    if (it != wheel_meshes_.end())
    {
        it->second.setTransform(transform);
    }
  }
}
