#pragma once

#include "Core/Core.h"

namespace SpikeSim {

  enum class DendriteType {
    Wire = 0
  };

  struct DendriteModelProps {
    int32_t Delay = 0;
    double RestingPotential = -70;
  };

  class Dendrite
  {
  public:
    virtual ~Dendrite() = default;

    virtual void OnUpdate(double inputCurrent) = 0;

    virtual void SetTimestep(double timestep) = 0;
    virtual void SetSpacestep(double spacestep) = 0;

    virtual double GetOutputCurrent() = 0;

    virtual void SetInputVoltage(double inputVoltage) = 0;
    virtual double GetInputVoltage() = 0;

    static Ref<Dendrite> Create(DendriteType type);
  };

}
