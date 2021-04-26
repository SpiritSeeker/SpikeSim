#pragma once

#include "Core/Core.h"

namespace SpikeSim {

  enum class SynapseType {
    FixedResistor = 0
  };

  struct SynapseModelProps {
    double RestingPotential = -70;
  };

  class Synapse
  {
  public:
    virtual ~Synapse() = default;

    virtual void OnUpdate(double inputVoltage, double outputVoltage) = 0;

    virtual void SetTimestep(double timestep) = 0;
    virtual void SetSpacestep(double spacestep) = 0;

    virtual double GetOutputCurrent() = 0;

    static Ref<Synapse> Create(SynapseType type);
  };

}
