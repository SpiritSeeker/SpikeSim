#include "sspch.h"
#include "LeakyIaF.h"

namespace SpikeSim {

  LeakyIaF::LeakyIaF(const LeakyIaFProps& props)
    : m_Capacitance(props.Capacitance),
     m_Conductance(props.Conductance),
     m_RestingPotential(props.RestingPotential),
     m_ThresholdPotential(props.ThresholdPotential),
     m_SpikeVoltage(props.SpikeVoltage)
  {
    m_MembranePotential = m_RestingPotential;
    m_SpikeInProgress = false;
  }

  void LeakyIaF::OnUpdate(double inputCurrent)
  {
    if (m_SpikeInProgress)
    {
      m_MembranePotential = m_RestingPotential;
      m_SpikeInProgress = false;
    }
    else
    {
      m_MembranePotential += inputCurrent / m_Capacitance;
      m_MembranePotential += m_Conductance * (m_RestingPotential - m_MembranePotential) / m_Capacitance;

      if (m_MembranePotential >= m_ThresholdPotential)
      {
        m_SpikeInProgress = true;
        m_MembranePotential = m_SpikeVoltage;
      }
    }
  }

}
