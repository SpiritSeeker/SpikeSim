#include "sspch.h"
#include "FixedResistor.h"

namespace SpikeSim {

  FixedResistor::FixedResistor(const FixedResistorProps& props)
    : m_Conductance(props.Conductance)
  {
    m_OutputCurrent = 0;
  }

  void FixedResistor::OnUpdate(double inputVoltage, double outputVoltage)
  {
    m_OutputCurrent = (inputVoltage - outputVoltage) * m_Conductance;
  }

}
