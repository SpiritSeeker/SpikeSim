#pragma once

#include "Core/Core.h"

namespace SpikeSim {

  struct InputNeuronProps {
    float RestingPotential = -70.0f;
    float ThresholdPotential = -40.0f;
    float RefractoryPeriod = 5.0f;

    float Conductance = 1.0f;
    float Capacitance = 10.0f;
    float InputSpikeCharge = 100.0f;
  };

  class InputNeuron
  {
  public:
    InputNeuron(const InputNeuronProps& props);
    ~InputNeuron() = default;

    bool OnUpdate(double currentTime, bool inputSpike);

    void SetTimestep(double timestep) { m_Timestep = timestep; }
    double GetMembranePotential() { return m_MembranePotential; }
    static Ref<InputNeuron> Create(const InputNeuronProps& props = InputNeuronProps());
  private:
    struct InputNeuronProps m_Props;
    double m_Timestep;
    double m_CurrentTime;
    double m_MembranePotential;
    double m_LastSpike;
  };

}
