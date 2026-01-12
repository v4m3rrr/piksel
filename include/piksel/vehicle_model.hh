#pragma once

#include "piksel/mesh.hh"

#include <unordered_map>

namespace piksel
{
  class VehicleModel : public Object
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
        Mesh&& rear_left_mesh,
        Mesh&& rear_right_mesh,
        Mesh&& front_left_mesh,
        Mesh&& front_right_mesh,
        Mesh&& chassis_mesh);
    VehicleModel(const VehicleModel&)=delete;
    VehicleModel(VehicleModel&&) noexcept=default;

    VehicleModel& operator=(const VehicleModel&)=delete;
    VehicleModel& operator=(VehicleModel&&)=delete;

    virtual void draw(Shader& shader) const override;

    void setWheelWorldTransform(WheelPosition wheel,const glm::mat4 transform);
  private:
    std::unordered_map<WheelPosition,Mesh> wheel_meshes_;
    Mesh chassis_mesh_;
  };
}
