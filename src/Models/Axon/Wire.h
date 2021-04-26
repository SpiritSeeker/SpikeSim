#pragma once

#include "sspch.h"
#include "Core/Core.h"
#include "Models/Axon/Axon.h"

namespace SpikeSim {

  struct WireProps : public AxonModelProps
  {};

  class Wire : public Axon
  {
  public:
    Wire(const WireProps& props = WireProps());
    virtual ~Wire() = default;

    virtual void OnUpdate(double inputVoltage) override;

    virtual void SetTimestep(double timestep) override {}
    virtual void SetSpacestep(double spacestep) override {}

    virtual double GetTerminalVoltage() override { return m_Buffer.front(); }
  private:
    int32_t m_Delay;
    double m_RestingPotential;
    std::queue<double> m_Buffer;
  };

}
