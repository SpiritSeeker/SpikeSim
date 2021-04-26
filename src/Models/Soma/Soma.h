#pragma once

#include "Core/Core.h"

namespace SpikeSim {

  enum class SomaType {
    IaF = 0, LeakyIaF = 1, HH = 2
  };

  struct SomaModelProps {
    double RestingPotential = -70;
  };

  class Soma
  {
  public:
    virtual ~Soma() = default;

    virtual void OnUpdate(double inputCurrent) = 0;

    virtual void SetTimestep(double timestep) = 0;
    virtual void SetSpacestep(double spacestep) = 0;

    virtual double GetMembranePotential() = 0;

    static Ref<Soma> Create(SomaType type);
  };

}
