#include "matplotlibcpp.h"
#include "stdlib.h"
#include "Models/Soma/HH.h"
#include "Models/Soma/LeakyIaF.h"
#include "Models/Synapse/FixedResistor.h"

namespace plt = matplotlibcpp;

void HHSomaExample(uint32_t nIter)
{
  std::vector<double> currents = { -2, 5, 10 };
  int index = 0;

  for (double current : currents)
  {
    auto soma = SpikeSim::HH();
    double timestep = 1e-3;
    soma.SetTimestep(timestep);

    std::vector<double> time;
    std::vector<double> voltage;

    for (int i = 0; i < nIter; i++)
    {
      soma.OnUpdate(current);
      time.push_back(timestep * i);
      voltage.push_back(soma.GetMembranePotential());
    }
    std::string label = std::to_string((int)current) + " nA";
    plt::named_plot(label, time, voltage);
    plt::ylim(-85, 70);
  }
  std::map<std::string, std::string> params;
  params.insert(std::pair<std::string, std::string>("labelsize", "14"));
  plt::tick_params(params);
  params.erase("labelsize");
  params.insert(std::pair<std::string, std::string>("fontsize", "16"));
  plt::xlabel("Time (in ms)", params);
  plt::ylabel("Membrane Potential (in mV)", params);
  plt::legend(params);
  plt::show();
}

void IaFNetwork(uint32_t nIter)
{
  auto neuron1 = SpikeSim::LeakyIaF();
  auto neuron2 = SpikeSim::LeakyIaF();
  auto neuron3 = SpikeSim::LeakyIaF();
  auto neuron4 = SpikeSim::LeakyIaF();

  auto param1 = SpikeSim::FixedResistorProps();
  param1.Conductance = 1;
  auto param2 = SpikeSim::FixedResistorProps();
  param2.Conductance = 3;
  auto param3 = SpikeSim::FixedResistorProps();
  param3.Conductance = -1;
  auto synapse1 = SpikeSim::FixedResistor(param1);
  auto synapse2 = SpikeSim::FixedResistor(param2);
  auto synapse3 = SpikeSim::FixedResistor(param3);

  std::vector<double> time;
  std::vector<double> voltage1;
  std::vector<double> voltage2;
  std::vector<double> voltage3;
  std::vector<double> voltage4;

  srand(42);
  double prob1 = 0.4;
  double prob2 = 0.3;
  double prob3 = 0.3;
  double spikeCurrent = 80;

  for (int i = 0; i < nIter; i++)
  {
    double outputCurrent = synapse1.GetOutputCurrent() + synapse2.GetOutputCurrent() + synapse3.GetOutputCurrent();

    neuron4.OnUpdate(outputCurrent);

    double spikeProb = rand() * 1.0 / RAND_MAX;
    neuron1.OnUpdate((spikeProb < prob1) ? spikeCurrent : 0);
    spikeProb = rand() * 1.0 / RAND_MAX;
    neuron2.OnUpdate((spikeProb < prob2) ? spikeCurrent : 0);
    spikeProb = rand() * 1.0 / RAND_MAX;
    neuron3.OnUpdate((spikeProb < prob3) ? spikeCurrent : 0);

    synapse1.OnUpdate((neuron1.GetMembranePotential() > 0) ? 10 : -70, -70);
    synapse2.OnUpdate((neuron2.GetMembranePotential() > 0) ? 10 : -70, -70);
    synapse3.OnUpdate((neuron3.GetMembranePotential() > 0) ? 10 : -70, -70);

    time.push_back(i);
    voltage1.push_back((neuron1.GetMembranePotential() > 0) ? 10 : -70);
    voltage2.push_back((neuron2.GetMembranePotential() > 0) ? 10 : -70);
    voltage3.push_back((neuron3.GetMembranePotential() > 0) ? 10 : -70);
    voltage4.push_back(neuron4.GetMembranePotential());
  }
  std::map<std::string, std::string> params;
  params.insert(std::pair<std::string, std::string>("labelsize", "14"));
  plt::tick_params(params);
  params.erase("labelsize");
  params.insert(std::pair<std::string, std::string>("fontsize", "16"));
  plt::named_plot("Neuron 1", time, voltage1);
  plt::named_plot("Neuron 2", time, voltage2);
  plt::named_plot("Neuron 3", time, voltage3);
  plt::named_plot("Neuron 4", time, voltage4);
  plt::xlabel("Time (in ms)", params);
  plt::ylabel("Membrane Potential (in mV)", params);
  plt::legend(params);
  plt::ylim(-80, 40);
  plt::show();
}
