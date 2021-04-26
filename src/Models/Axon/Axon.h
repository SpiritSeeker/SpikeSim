#pragma once

#include "Core/Core.h"

namespace SpikeSim {

  enum class AxonType {
    Wire = 0, SpikeDelay = 1
  };

  struct AxonModelProps {
    int32_t Delay = 0;
    double RestingPotential = -70;
  };

  class Axon
  {
  public:
    virtual ~Axon() = default;

    virtual void OnUpdate(double inputVoltage) = 0;

    virtual void SetTimestep(double timestep) = 0;
    virtual void SetSpacestep(double spacestep) = 0;

    virtual double GetTerminalVoltage() = 0;

    static Ref<Axon> Create(AxonType type);
  };

}
