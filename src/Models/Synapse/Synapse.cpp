#include "sspch.h"
#include "Synapse.h"
#include "Models/Synapse/FixedResistor.h"

namespace SpikeSim {

  Ref<Synapse> Synapse::Create(SynapseType type)
  {
    switch (type)
    {
      case SynapseType::FixedResistor:  return CreateRef<FixedResistor>();
    }
    return nullptr;
  }

}
