#include "sspch.h"
#include "IaF.h"

namespace SpikeSim {

  IaF::IaF(const IaFProps& props)
    : m_Capacitance(props.Capacitance),
     m_RestingPotential(props.RestingPotential),
     m_ThresholdPotential(props.ThresholdPotential),
     m_SpikeVoltage(props.SpikeVoltage)
  {
    m_MembranePotential = m_RestingPotential;
    m_SpikeInProgress = false;
  }

  void IaF::OnUpdate(double inputCurrent)
  {
    if (m_SpikeInProgress)
    {
      m_MembranePotential = m_RestingPotential;
      m_SpikeInProgress = false;
    }
    else
    {
      m_MembranePotential += inputCurrent / m_Capacitance;

      if (m_MembranePotential >= m_ThresholdPotential)
      {
        m_SpikeInProgress = true;
        m_MembranePotential = m_SpikeVoltage;
      }
    }
  }

}
