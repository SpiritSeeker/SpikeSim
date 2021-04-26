#pragma once

#include "Core/Core.h"
#include "Models/Soma/Soma.h"

namespace SpikeSim {

  struct IaFProps : public SomaModelProps {
    double ThresholdPotential = -40;
    double SpikeVoltage = 10;
    double Capacitance = 10;
  };

  class IaF : public Soma
  {
  public:
    IaF(const IaFProps& props = IaFProps());
    virtual ~IaF() = default;

    virtual void OnUpdate(double inputCurrent) override;

    virtual void SetTimestep(double timestep) override {}
    virtual void SetSpacestep(double spacestep) override {}

    virtual double GetMembranePotential() override { return m_MembranePotential; }
  private:
    double m_Capacitance;
    double m_RestingPotential;
    double m_ThresholdPotential;
    double m_MembranePotential;
    double m_SpikeVoltage;
    bool m_SpikeInProgress;
  };

}
