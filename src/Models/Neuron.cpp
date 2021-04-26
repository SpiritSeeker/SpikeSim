#include "sspch.h"
#include "Neuron.h"

namespace SpikeSim {

  Neuron::Neuron(const NeuronProps& props)
    : m_Props(props)
  {
    m_Soma = Soma::Create(m_Props.Soma);

    for (int i = 0; i < m_Props.n_Dendrites; i++)
    {
      m_Dendrites.push_back(Dendrite::Create(m_Props.Dendrites[i]));
      m_InputVoltages.push_back(m_Dendrites[i]->GetInputVoltage());
    }

    for (int i = 0; i < m_Props.n_Axons; i++)
    {
      m_Axons.push_back(Axon::Create(m_Props.Axons[i]));
      m_TerminalVoltages.push_back(m_Axons[i]->GetTerminalVoltage());
    }
  }

  void Neuron::OnUpdate(const std::vector<double>& inputCurrents)
  {
    m_DendriteCurrent = 0;
    for (int i = 0; i < m_Props.n_Dendrites; i++)
    {
      m_Dendrites[i]->OnUpdate(inputCurrents[i]);
      m_Dendrites[i]->SetInputVoltage(m_Soma->GetMembranePotential());
      m_DendriteCurrent += m_Dendrites[i]->GetOutputCurrent();
    }

    m_Soma->OnUpdate(m_DendriteCurrent);

    for (int i = 0; i < m_Props.n_Axons; i++)
    {
      m_Axons[i]->OnUpdate(m_Soma->GetMembranePotential());
      m_TerminalVoltages[i] = m_Axons[i]->GetTerminalVoltage();
    }
  }

  void Neuron::SetTimestep(double timestep)
  {
    m_Soma->SetTimestep(timestep);
    for (auto dendrite : m_Dendrites)
      dendrite->SetTimestep(timestep);
    for (auto axon : m_Axons)
      axon->SetTimestep(timestep);
  }

  void Neuron::SetSpacestep(double spacestep)
  {
      m_Soma->SetSpacestep(spacestep);
      for (auto dendrite : m_Dendrites)
          dendrite->SetSpacestep(spacestep);
    for (auto axon : m_Axons)
      axon->SetSpacestep(spacestep);
  }

  Ref<Neuron> Neuron::Create(const NeuronProps& props)
  {
    return CreateRef<Neuron>(props);
  }

}
