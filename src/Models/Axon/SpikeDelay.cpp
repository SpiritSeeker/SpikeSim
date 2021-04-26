#include "sspch.h"
#include "SpikeDelay.h"

namespace SpikeSim {

  SpikeDelay::SpikeDelay(const SpikeDelayProps& props)
    : m_Delay(props.Delay), m_RestingPotential(props.RestingPotential), m_SpikeThreshold(props.SpikeThreshold), m_ResetThreshold(props.ResetThreshold)
  {
    m_Buffer.push(m_RestingPotential);
    m_SpikeInProgress = false;
  }

  void SpikeDelay::OnUpdate(double inputVoltage)
  {
    if (m_Buffer.size() > m_Delay)
      m_Buffer.pop();

    if (inputVoltage >= m_SpikeThreshold) m_SpikeInProgress = true;
    if (inputVoltage < m_ResetThreshold) m_SpikeInProgress = false;

    if (m_SpikeInProgress)
      m_Buffer.push(inputVoltage);
    else
      m_Buffer.push(m_RestingPotential);
  }

}
