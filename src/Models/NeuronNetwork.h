#pragma once

#include "Core/Core.h"

#include "Models/Neuron.h"
#include "Models/Synapse/Synapse.h"

namespace SpikeSim {

  enum class PlotType {
    MembranePotential = 0, DendriteCurrent = 1, AxonTerminalVoltage = 2, SynapticCurrent = 3
  };

  struct PlotData {
    std::vector<double> X;
    std::vector<double> Y;
  };

  struct Connection {
    uint32_t SynapseID;
    uint32_t PreNeuron;
    uint32_t Axon;
    uint32_t PostNeuron;
    uint32_t Dendrite;
  };

  struct PlotInfo {
    uint32_t Type;        // 0 - Neuron, 1 - Synapse
    uint32_t ID;          // ID of neuron/synapse
    uint32_t Component;   // Dendrite/Soma/Axon
    uint32_t Index;       // Index of Dendrite/Axon
  };

  class NeuronNetwork
  {
  public:
    NeuronNetwork();
    ~NeuronNetwork() = default;

    void OnUpdate(const std::vector<std::vector<double>>& inputCurrents, uint32_t nIter);

    void AddNeuron(uint32_t dendrites = 1, uint32_t axons = 1, bool input = false);
    void AddSynapse(uint32_t fromNeuronID, uint32_t fromAxonID, uint32_t toNeuronID, uint32_t toDendriteID);

    void TracePlot(PlotType type, uint32_t id);
    void TracePlot(PlotType type, uint32_t neuronID, uint32_t id);

    void SetTimestep(double timestep);

    const PlotData& GetPlotData(uint32_t id) { return m_PlotData[id]; }
  private:
    double m_Timestep = 1e-3;

    std::vector<Ref<Neuron>> m_Neurons;
    std::vector<bool> m_InputNeuron;

    std::vector<Ref<Synapse>> m_Synapses;
    std::vector<Connection> m_Connections;

    std::vector<PlotData> m_PlotData;
    std::vector<PlotInfo> m_PlotInfo;
  };

}
