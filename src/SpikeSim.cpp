#include "sspch.h"
#include "Core/Simulator.h"
#include "Models/NeuronNetwork.h"
#include "matplotlibcpp.h"

namespace plt = matplotlibcpp;

int main()
{
  SpikeSim::Log::Init();
  SS_WARN("Initialized SpikeSim!");

  SpikeSim::Simulator* sim = SpikeSim::CreateSimulator();

  auto network = SpikeSim::NeuronNetwork();
  network.SetTimestep(1e-3);
  SS_TRACE("Timestep set!");

  network.AddNeuron(1, 3, true);
  network.AddNeuron();
  network.AddNeuron();
  network.AddNeuron(2);
  SS_TRACE("Neurons added!");

  network.AddSynapse(0, 0, 1, 0);
  network.AddSynapse(0, 1, 2, 0);
  network.AddSynapse(0, 1, 3, 0);
  network.AddSynapse(0, 2, 3, 1);
  SS_TRACE("Synapses added!");

  network.TracePlot(SpikeSim::PlotType::MembranePotential, 0);
  network.TracePlot(SpikeSim::PlotType::MembranePotential, 1);
  network.TracePlot(SpikeSim::PlotType::MembranePotential, 2);
  network.TracePlot(SpikeSim::PlotType::MembranePotential, 3);
  SS_TRACE("Traces set!");

  for (int i = 0; i < 5e5; i++)
    network.OnUpdate({{5}}, i);

  plt::plot(network.GetPlotData(0).X, network.GetPlotData(0).Y);
  plt::plot(network.GetPlotData(1).X, network.GetPlotData(1).Y);
  plt::plot(network.GetPlotData(2).X, network.GetPlotData(2).Y);
  plt::plot(network.GetPlotData(3).X, network.GetPlotData(3).Y);
  plt::show();

  delete sim;
  return 0;
}
