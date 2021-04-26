#include "sspch.h"
#include "NeuronNetwork.h"

namespace SpikeSim {

  NeuronNetwork::NeuronNetwork()
  {}

  void NeuronNetwork::OnUpdate(const std::vector<std::vector<double>>& inputCurrents, uint32_t nIter)
  {
    uint32_t inputCounter = 0;
    for (int i = 0; i < m_Neurons.size(); i++)
    {
      if (m_InputNeuron[i])
        m_Neurons[i]->OnUpdate(inputCurrents[inputCounter++]);
      else
      {
        std::vector<double> inputCurrent(m_Neurons[i]->GetDendriteCount(), 0);
        for (int j = 0; j < m_Connections.size(); j++)
        {
          if (m_Connections[j].PostNeuron == i)
            inputCurrent[m_Connections[j].Dendrite] = m_Synapses[m_Connections[j].SynapseID]->GetOutputCurrent();
        }
      }
    }

    for (int i = 0; i < m_Synapses.size(); i++)
    {
      double inputVoltage = m_Neurons[m_Connections[i].PreNeuron]->GetTerminalVoltages()[m_Connections[i].Axon];
      double outputVoltage = m_Neurons[m_Connections[i].PostNeuron]->GetInputVoltages()[m_Connections[i].Dendrite];
      m_Synapses[i]->OnUpdate(inputVoltage, outputVoltage);
    }

    for (int i = 0; i < m_PlotInfo.size(); i++)
    {
      m_PlotData[i].X.push_back(nIter * m_Timestep);
      if (m_PlotInfo[i].Type == 0)
      {
        switch (m_PlotInfo[i].Component)
        {
          case 0:
          {
            m_PlotData[i].Y.push_back(m_Neurons[m_PlotInfo[i].ID]->GetDendriteCurrent());
            break;
          }
          case 1:
          {
            m_PlotData[i].Y.push_back(m_Neurons[m_PlotInfo[i].ID]->GetMembranePotential());
            break;
          }
          case 2:
          {
            m_PlotData[i].Y.push_back(m_Neurons[m_PlotInfo[i].ID]->GetTerminalVoltages()[m_PlotInfo[i].Index]);
            break;
          }
        }
      }
      else
        m_PlotData[i].Y.push_back(m_Synapses[m_PlotInfo[i].ID]->GetOutputCurrent());
    }
  }

  void NeuronNetwork::AddNeuron(uint32_t dendrites, uint32_t axons, bool input)
  {
    struct NeuronProps props;
    props.n_Dendrites = dendrites;
    props.n_Axons = axons;
    auto neuron = Neuron::Create(props);
    neuron->SetTimestep(m_Timestep);
    m_Neurons.push_back(neuron);
    m_InputNeuron.push_back(input);
  }

  void NeuronNetwork::AddSynapse(uint32_t fromNeuronID, uint32_t fromAxonID, uint32_t toNeuronID, uint32_t toDendriteID)
  {
    auto synapse = Synapse::Create(SynapseType::FixedResistor);
    synapse->SetTimestep(m_Timestep);
    m_Synapses.push_back(synapse);
    m_Connections.push_back({ (uint32_t)m_Connections.size(), fromNeuronID, fromAxonID, toNeuronID, toDendriteID });
  }

  void NeuronNetwork::TracePlot(PlotType type, uint32_t id)
  {
    switch (type)
    {
      case PlotType::MembranePotential:
      {
        m_PlotInfo.push_back({ 0, id, 1, 0 });
        m_PlotData.push_back({ {0}, {-70} });
      }
      case PlotType::SynapticCurrent:
      {
        m_PlotInfo.push_back({ 1, id, 0, 0 });
        m_PlotData.push_back({ {0}, {0} });
      }
      case PlotType::DendriteCurrent:
      {
        m_PlotInfo.push_back({ 0, id, 0, 0 });
        m_PlotData.push_back({ {0}, {0} });
      }
    }
  }

  void NeuronNetwork::TracePlot(PlotType type, uint32_t neuronID, uint32_t id)
  {
    m_PlotInfo.push_back({ 0, neuronID, 2, id });
    m_PlotData.push_back({ {0}, {-70} });
  }

  void NeuronNetwork::SetTimestep(double timestep)
  {
    m_Timestep = timestep;
    for (auto neuron : m_Neurons)
      neuron->SetTimestep(m_Timestep);
    for (auto synapse : m_Synapses)
      synapse->SetTimestep(m_Timestep);
  }

}
