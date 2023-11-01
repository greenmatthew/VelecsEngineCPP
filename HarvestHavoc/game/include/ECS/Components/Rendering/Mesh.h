/// \file    Mesh.h
/// \author  Matthew Green
/// \date    10/31/2023 12:45:23
/// 
/// \section LICENSE
/// 
/// Copyright (c) 2023 Matthew Green - All rights reserved
/// Unauthorized copying of this file, via any medium is strictly prohibited
/// Proprietary and confidential

#pragma once

#include <Graphics/Vertex.h>

#include <Engine/AllocatedBuffer.h>

#include <vector>

namespace hh {

/// \class Material
/// \brief Brief description.
///
/// Rest of description.
struct Mesh {
    std::vector<engine::Vertex> _vertices;
    engine::AllocatedBuffer _vertexBuffer;
};

} // namespace hh
