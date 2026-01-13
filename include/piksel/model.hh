#pragma once

#include "piksel/IDrawable.hh"
#include "piksel/object.hh"

#include <vector>

namespace piksel
{
  class Model:public IDrawable
  {
  public:
    Model()=default;
    virtual ~Model() noexcept=default;

    virtual void draw(Shader& shader) const override;
    std::vector<Object>& getObjects();
    void addObject(Object&& object);
  protected:
    std::vector<Object> objects_;
  };
}
