#include "sspch.h"
#include "InputNeuron.h"

namespace SpikeSim {

  InputNeuron::InputNeuron(const InputNeuronProps& props)
    : m_Props(props)
  {
    m_MembranePotential = m_Props.RestingPotential;
    m_LastSpike = -m_Props.RefractoryPeriod;
  }

  bool InputNeuron::OnUpdate(double currentTime, bool inputSpike)
  {
    m_CurrentTime = currentTime;

    if (m_CurrentTime - m_LastSpike >= m_Props.RefractoryPeriod)
    {
      // Compute voltage by leaky integrate and fire
      if (inputSpike) m_MembranePotential += m_Props.InputSpikeCharge / m_Props.Capacitance;
      else m_MembranePotential += m_Props.Conductance * (m_Props.RestingPotential - m_MembranePotential) / m_Props.Capacitance;

      if (m_MembranePotential >= m_Props.ThresholdPotential)
      {
        m_LastSpike = m_CurrentTime;
        return true;
      }
      return false;
    }

    m_MembranePotential = m_Props.RestingPotential;
    return false;
  }

  Ref<InputNeuron> InputNeuron::Create(const InputNeuronProps& props)
  {
    return CreateRef<InputNeuron>(props);
  }

}
