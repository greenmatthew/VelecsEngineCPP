/// \file    Main.cpp
/// \author  Matthew Green
/// \date    10/15/2023 15:30:21
/// 
/// \section LICENSE
/// 
/// Copyright (c) 2023 Matthew Green - All rights reserved
/// Unauthorized copying of this file, via any medium is strictly prohibited
/// Proprietary and confidential

#include <VelECSEngine.h>

#include "ECS/ECSManager.h"

int main(int argc, char* argv[])
{
     auto& engine = velecs::VelECSEngine::GetInstance();

     engine.SetECS(std::make_unique<hh::ECSManager>(engine))
           // .SetInput(hh::Input::Create())
           .Init()
           .Run()
           .Cleanup();

    return 0;
}