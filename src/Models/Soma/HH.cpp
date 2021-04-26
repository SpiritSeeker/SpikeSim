#include "sspch.h"
#include "HH.h"

namespace SpikeSim {

  HH::HH(const HHProps& props)
    : m_Props(props)
  {
    m_MembranePotential = m_Props.RestingPotential;
    m_ProbabilityN = Inf_n(m_MembranePotential);
    m_ProbabilityM = Inf_m(m_MembranePotential);
    m_ProbabilityH = Inf_h(m_MembranePotential);
  }

  void HH::OnUpdate(double inputCurrent)
  {
    double dv = Get_dv(inputCurrent);
    double dn = Get_dn();
    double dm = Get_dm();
    double dh = Get_dh();

    m_MembranePotential += dv * m_Timestep;
    m_ProbabilityN += dn * m_Timestep;
    m_ProbabilityM += dm * m_Timestep;
    m_ProbabilityH += dh * m_Timestep;
  }

  double HH::Get_dv(double inputCurrent)
  {
    double currentK = m_Props.ConductanceK * pow(m_ProbabilityN, 4) * (m_MembranePotential - m_Props.ReversalK);
    double currentNa = m_Props.ConductanceNa * pow(m_ProbabilityM, 3) * m_ProbabilityH * (m_MembranePotential - m_Props.ReversalNa);
    double currentL = m_Props.ConductanceL * (m_MembranePotential - m_Props.ReversalL);
    return (inputCurrent - currentK - currentNa - currentL) / m_Props.Capacitance;
  }

  double HH::Get_dn()
  {
    return Alpha_n(m_MembranePotential) * (1 - m_ProbabilityN) - (Beta_n(m_MembranePotential) * m_ProbabilityN);
  }

  double HH::Get_dm()
  {
    return Alpha_m(m_MembranePotential) * (1 - m_ProbabilityM) - (Beta_m(m_MembranePotential) * m_ProbabilityM);
  }

  double HH::Get_dh()
  {
    return Alpha_h(m_MembranePotential) * (1 - m_ProbabilityH) - (Beta_h(m_MembranePotential) * m_ProbabilityH);
  }

  double HH::Alpha_n(double vm)
  {
    if (abs(vm - 10) < 1e-5) vm -= 1e-3;
    return -0.01 * (50 + vm) / (exp(-(50 + vm) / 10) - 1);
  }

  double HH::Beta_n(double vm)
  {
    return 0.125 * exp(-(60 + vm) / 80);
  }

  double HH::Alpha_m(double vm)
  {
    if (abs(vm - 25) < 1e-5) vm -= 1e-3;
    return -0.1 * (35 + vm) / (exp(-(35 + vm) / 10) - 1);
  }

  double HH::Beta_m(double vm)
  {
    return 4 * exp(-(60 + vm) / 18);
  }

  double HH::Alpha_h(double vm)
  {
    return 0.07 * exp(-(60 + vm) / 20);
  }

  double HH::Beta_h(double vm)
  {
    return 1 / (exp(-(30 + vm) / 10) + 1);
  }

  double HH::Inf_n(double vm)
  {
    double alpha_n = Alpha_n(vm);
    return alpha_n / (alpha_n + Beta_n(vm));
  }

  double HH::Inf_m(double vm)
  {
    double alpha_m = Alpha_m(vm);
    return alpha_m / (alpha_m + Beta_m(vm));
  }

  double HH::Inf_h(double vm)
  {
    double alpha_h = Alpha_h(vm);
    return alpha_h / (alpha_h + Beta_h(vm));
  }

}
