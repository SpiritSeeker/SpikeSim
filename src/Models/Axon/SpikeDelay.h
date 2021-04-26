#pragma once

#include "Core/Core.h"
#include "Models/Axon/Axon.h"

namespace SpikeSim {

  struct AxonModelProps;
  class Axon;

  struct SpikeDelayProps : public AxonModelProps
  {
    double SpikeThreshold = 0;
    double ResetThreshold = -40;
  };

  class SpikeDelay : public Axon
  {
  public:
    SpikeDelay(const SpikeDelayProps& props = SpikeDelayProps());
    virtual ~SpikeDelay() = default;

    virtual void OnUpdate(double inputVoltage) override;

    virtual void SetTimestep(double timestep) override {}
    virtual void SetSpacestep(double spacestep) override {}

    virtual double GetTerminalVoltage() override { return m_Buffer.front(); }
  private:
    int32_t m_Delay;

    double m_RestingPotential;
    double m_SpikeThreshold;
    double m_ResetThreshold;

    bool m_SpikeInProgress;

    std::queue<double> m_Buffer;
  };

}
