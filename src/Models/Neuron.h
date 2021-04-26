#pragma once

#include "Core/Core.h"

#include "Models/Axon/Axon.h"
#include "Models/Dendrite/Dendrite.h"
#include "Models/Soma/Soma.h"

namespace SpikeSim {

  struct NeuronProps {
    SomaType Soma = SomaType::HH;

    int32_t n_Dendrites = 1;
    std::vector<DendriteType> Dendrites = { DendriteType::Wire };

    int32_t n_Axons = 1;
    std::vector<AxonType> Axons = { AxonType::Wire };
  };

  class Neuron
  {
  public:
    Neuron(const NeuronProps& props);
    ~Neuron() = default;

    void OnUpdate(const std::vector<double>& inputCurrents);

    void SetTimestep(double timestep);
    void SetSpacestep(double spacestep);

    const std::vector<double>& GetTerminalVoltages() { return m_TerminalVoltages; }
    const std::vector<double>& GetInputVoltages() { return m_InputVoltages; }
    double GetDendriteCurrent() { return m_DendriteCurrent; }
    double GetMembranePotential() { return m_Soma->GetMembranePotential(); }
    uint32_t GetDendriteCount() { return m_Props.n_Dendrites; }

    static Ref<Neuron> Create(const NeuronProps& props = NeuronProps());
  private:
    struct NeuronProps m_Props;
    double m_DendriteCurrent;
    Ref<Soma> m_Soma;
    std::vector<Ref<Dendrite>> m_Dendrites;
    std::vector<Ref<Axon>> m_Axons;
    std::vector<double> m_TerminalVoltages;
    std::vector<double> m_InputVoltages;
  };

}
