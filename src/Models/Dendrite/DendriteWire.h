#pragma once

#include "sspch.h"
#include "Core/Core.h"
#include "Models/Dendrite/Dendrite.h"

namespace SpikeSim {

  struct DendriteWireProps : public DendriteModelProps
  {};

  class DendriteWire : public Dendrite
  {
  public:
    DendriteWire(const DendriteWireProps& props = DendriteWireProps());
    virtual ~DendriteWire() = default;

    virtual void OnUpdate(double inputCurrent) override;

    virtual void SetTimestep(double timestep) override {}
    virtual void SetSpacestep(double spacestep) override {}

    virtual double GetOutputCurrent() override { return m_Buffer.front(); }

    virtual void SetInputVoltage(double inputVoltage) override { m_InputVoltage = inputVoltage; }
    virtual double GetInputVoltage() override { return m_InputVoltage; }
  private:
    int32_t m_Delay;
    double m_RestingPotential;
    double m_InputVoltage;
    std::queue<double> m_Buffer;
  };

}
