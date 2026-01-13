#include "piksel/vehicle_model.hh"
#include "piksel/shader.hh"

#include <glm/gtc/type_ptr.hpp>

namespace piksel
{
  VehicleModel::VehicleModel(
      std::shared_ptr<const Mesh> rear_left_mesh,
      std::shared_ptr<const Mesh> rear_right_mesh,
      std::shared_ptr<const Mesh> front_left_mesh,
      std::shared_ptr<const Mesh> front_right_mesh,
      std::shared_ptr<const Mesh> chassis_mesh)
  {
    // Order matters must math with WheelPostion enum
    this->objects_.push_back(rear_left_mesh);
    this->objects_.push_back(rear_right_mesh);
    this->objects_.push_back(front_left_mesh);
    this->objects_.push_back(front_right_mesh);

    // Last element is always chassis.
    this->objects_.push_back(chassis_mesh);
  }

  void VehicleModel::draw(Shader& shader) const
  {
    Model::draw(shader);
  }

  const glm::mat4& VehicleModel::getWheelWorldTransform(
      WheelPosition wheel) const
  {
    return this->objects_.at(int(wheel)).getTransform();
  }

  const glm::mat4& VehicleModel::getChassisWorldTransform() const
  {
    return this->objects_.at((int)(WheelPosition::Count)).getTransform();
  }

  void VehicleModel::setWheelWorldTransform(
      WheelPosition wheel,const glm::mat4& transform)
  {
    // Assumes that order on creation match order
    // of WheelPosition
    this->objects_[(int)wheel].setTransform(transform);
  }

  void VehicleModel::setChassisWorldTransform(const glm::mat4& transform)
  {
    this->objects_[(int)WheelPosition::Count].setTransform(transform);
  }

  void VehicleModel::moveVehicleBy(const glm::mat4& transform)
  {
    for(uint16_t i=0;i<(uint16_t)WheelPosition::Count;i++)
    {
      WheelPosition wheel=(WheelPosition)i;
      auto wheel_transform=getWheelWorldTransform(wheel);
      wheel_transform=transform*wheel_transform;

      setWheelWorldTransform(wheel,wheel_transform);
    }

    auto chassis_transform=getChassisWorldTransform();
    chassis_transform=transform*chassis_transform;
    setChassisWorldTransform(chassis_transform);
  }
}
