#include "sspch.h"
#include "Examples.h"

int main()
{
  SpikeSim::Log::Init();

  // HHSomaExample(5e4);
  IaFNetwork(200);

  return 0;
}
