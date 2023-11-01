/// \file    AngularKinematics.h
/// \author  Matthew Green
/// \date    10/30/2023 19:48:21
/// 
/// \section LICENSE
/// 
/// Copyright (c) 2023 Matthew Green - All rights reserved
/// Unauthorized copying of this file, via any medium is strictly prohibited
/// Proprietary and confidential

#pragma once

#include <Math/Vec3.h>

namespace hh {

/// \class AngularKinematics
/// \brief Brief description.
///
/// Rest of description.
struct AngularKinematics {
    engine::Vec3 angularVelocity{engine::Vec3::ZERO};
    engine::Vec3 angularAcceleration{engine::Vec3::ZERO};
};

} // namespace hh
