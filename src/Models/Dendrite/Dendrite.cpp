#include "sspch.h"
#include "Dendrite.h"
#include "Models/Dendrite/DendriteWire.h"

namespace SpikeSim {

  Ref<Dendrite> Dendrite::Create(DendriteType type)
  {
    switch (type)
    {
      case DendriteType::Wire:  return CreateRef<DendriteWire>();
    }
    return nullptr;
  }

}
