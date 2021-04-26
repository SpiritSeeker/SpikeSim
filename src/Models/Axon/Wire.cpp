#include "sspch.h"
#include "Wire.h"

namespace SpikeSim {

  Wire::Wire(const WireProps& props)
    : m_Delay(props.Delay), m_RestingPotential(props.RestingPotential)
  {
    m_Buffer.push(m_RestingPotential);
  }

  void Wire::OnUpdate(double inputVoltage)
  {
    if (m_Buffer.size() > m_Delay)
      m_Buffer.pop();
    m_Buffer.push(inputVoltage);
  }

}
