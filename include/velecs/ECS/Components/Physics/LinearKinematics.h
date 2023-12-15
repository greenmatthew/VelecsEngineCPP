/// @file    LinearKinematics.h
/// @author  Matthew Green
/// @date    10/30/2023 19:48:10
/// 
/// @section LICENSE
/// 
/// Copyright (c) 2023 Matthew Green - All rights reserved
/// Unauthorized copying of this file, via any medium is strictly prohibited
/// Proprietary and confidential

#pragma once

#include "velecs/Math/Vec3.h"

namespace velecs {

/// @struct LinearKinematics
/// @brief Brief description.
///
/// Rest of description.
struct LinearKinematics {
    Vec3 velocity{Vec3::ZERO};
    Vec3 acceleration{Vec3::ZERO};
};

} // namespace velecs
