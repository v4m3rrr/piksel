#pragma once

#include "piksel/model.hh"

namespace piksel
{
  class VehicleModel:public Model
  {
  public:
    enum class WheelPosition : unsigned short
    {
      RearLeft=0,
      RearRight,
      FrontLeft,
      FrontRight,
      Count
    };
  public:
    VehicleModel(
        std::shared_ptr<const Mesh> rear_left_mesh,
        std::shared_ptr<const Mesh> rear_right_mesh,
        std::shared_ptr<const Mesh> front_left_mesh,
        std::shared_ptr<const Mesh> front_right_mesh,
        std::shared_ptr<const Mesh> chassis_mesh);
    VehicleModel(const VehicleModel&)=delete;
    VehicleModel(VehicleModel&&) noexcept=default;

    VehicleModel& operator=(const VehicleModel&)=delete;
    VehicleModel& operator=(VehicleModel&&)=delete;

    virtual void draw(Shader& shader) const override;

    const glm::mat4& getWheelWorldTransform(WheelPosition wheel) const;
    const glm::mat4& getChassisWorldTransform() const;

    void setWheelWorldTransform(WheelPosition wheel,const glm::mat4& transform);
    void setChassisWorldTransform(const glm::mat4& transform);

    void moveVehicleBy(const glm::mat4& transform);
  };
}
