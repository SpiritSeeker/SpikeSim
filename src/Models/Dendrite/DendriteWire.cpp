#include "sspch.h"
#include "DendriteWire.h"

namespace SpikeSim {

  DendriteWire::DendriteWire(const DendriteWireProps& props)
    : m_Delay(props.Delay), m_RestingPotential(props.RestingPotential)
  {
    m_Buffer.push(0);
    m_InputVoltage = m_RestingPotential;
  }

  void DendriteWire::OnUpdate(double inputCurrent)
  {
    if (m_Buffer.size() > m_Delay)
      m_Buffer.pop();
    m_Buffer.push(inputCurrent);
  }

}
