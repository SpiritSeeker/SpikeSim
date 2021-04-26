#pragma once

#include "Core/Core.h"
#include "Models/Synapse/Synapse.h"

namespace SpikeSim {

  struct FixedResistorProps : public SynapseModelProps {
    double Conductance = 10;
  };

  class FixedResistor : public Synapse
  {
  public:
    FixedResistor(const FixedResistorProps& props = FixedResistorProps());
    virtual ~FixedResistor() = default;

    virtual void OnUpdate(double inputVoltage, double outputVoltage) override;

    virtual void SetTimestep(double timestep) override {}
    virtual void SetSpacestep(double spacestep) override {}

    virtual double GetOutputCurrent() override { return m_OutputCurrent; }
  private:
    double m_Conductance;
    double m_OutputCurrent;
  };

}
