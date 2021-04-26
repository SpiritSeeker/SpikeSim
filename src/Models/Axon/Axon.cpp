#include "sspch.h"
#include "Axon.h"
#include "Models/Axon/Wire.h"
#include "Models/Axon/SpikeDelay.h"

namespace SpikeSim {

  Ref<Axon> Axon::Create(AxonType type)
  {
    switch (type)
    {
      case AxonType::Wire:          return CreateRef<Wire>();
      case AxonType::SpikeDelay:    return CreateRef<SpikeDelay>();
    }
    return nullptr;
  }

}
