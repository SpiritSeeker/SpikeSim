#pragma once

#include "Core/Core.h"
#include "Models/Soma/Soma.h"

namespace SpikeSim {

  struct HHProps : public SomaModelProps {
    double Capacitance = 1;
    double ConductanceK = 36;
    double ConductanceNa = 120;
    double ConductanceL = 0.3;
    double ReversalK = -72;
    double ReversalNa = 55;
    double ReversalL = -50;
  };

  class HH : public Soma
  {
  public:
    HH(const HHProps& props = HHProps());
    virtual ~HH() = default;

    virtual void OnUpdate(double inputCurrent) override;

    virtual void SetTimestep(double timestep) override { m_Timestep = timestep; }
    virtual void SetSpacestep(double spacestep) override {}

    virtual double GetMembranePotential() override { return m_MembranePotential; }
  private:
    struct HHProps m_Props;
    double m_Timestep;
    double m_MembranePotential;
    double m_ProbabilityN;
    double m_ProbabilityM;
    double m_ProbabilityH;
  private:
    double Get_dv(double inputCurrent);
    double Get_dn();
    double Get_dm();
    double Get_dh();

    double Alpha_n(double vm);
    double Beta_n(double vm);
    double Alpha_m(double vm);
    double Beta_m(double vm);
    double Alpha_h(double vm);
    double Beta_h(double vm);

    double Inf_h(double vm);
    double Inf_n(double vm);
    double Inf_m(double vm);
  };

}
