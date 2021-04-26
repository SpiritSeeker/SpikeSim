#include "sspch.h"
#include "Soma.h"
#include "Models/Soma/IaF.h"
#include "Models/Soma/LeakyIaF.h"
#include "Models/Soma/HH.h"

namespace SpikeSim {

  Ref<Soma> Soma::Create(SomaType type)
  {
    switch (type)
    {
      case SomaType::IaF:       return CreateRef<IaF>();
      case SomaType::LeakyIaF:  return CreateRef<LeakyIaF>();
      case SomaType::HH:        return CreateRef<HH>();
    }
    return nullptr;
  }

}
