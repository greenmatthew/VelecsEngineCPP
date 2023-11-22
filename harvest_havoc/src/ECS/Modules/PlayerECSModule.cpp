/// @file    PlayerECSModule.cpp
/// @author  Matthew Green
/// @date    2023-11-14 16:32:44
/// 
/// @section LICENSE
/// 
/// Copyright (c) 2023 Matthew Green - All rights reserved
/// Unauthorized copying of this file, via any medium is strictly prohibited
/// Proprietary and confidential

#include "ECS/Modules/PlayerECSModule.h"

#include "ECS/ECSManager.h"

#include <algorithm>

using namespace velecs;

namespace hh {

// Public Fields

// Constructors and Destructors

PlayerECSModule::PlayerECSModule(flecs::world& ecs)
    : IECSModule(ecs)
{
    ecs.import<InputECSModule>();
    ecs.import<RenderingECSModule>();
    ecs.import<PhysicsECSModule>();

    // CreatePlayerEntity("Player");

    flecs::entity cameraEntity = RenderingECSModule::CreatePerspectiveCamera(ecs, Vec3{0.0f, 0.0f,-2.0f}, Vec3::ZERO, Vec2{1700.0f, 900.0f});
    ecs.set<MainCamera>({cameraEntity});

    flecs::entity trianglePrefab = CommonECSModule::GetPrefab(ecs, "velecs::RenderingECSModule::PR_TriangleRender");
    flecs::entity player = ecs.entity()
        .is_a(trianglePrefab)
        .set_name("Player")
        .add<Player>()
        .add<LinearKinematics>()
        ;
    
    cameraEntity.child_of(player);

    ecs.entity()
        .is_a(trianglePrefab)
        .set_name("Entity1")
        .set<Transform>({Vec3::UP + Vec3::RIGHT, Vec3::ZERO, Vec3::ONE * 0.1f})
        ;

    ecs.entity()
        .is_a(trianglePrefab)
        .set_name("Entity2")
        .set<Transform>({Vec3::UP + Vec3::LEFT, Vec3::ZERO, Vec3::ONE * 0.1f})
        ;
    
    ecs.entity()
        .is_a(trianglePrefab)
        .set_name("Entity3")
        .set<Transform>({Vec3::DOWN + Vec3::RIGHT, Vec3::ZERO, Vec3::ONE * 0.1f})
        ;
    
    ecs.entity()
        .is_a(trianglePrefab)
        .set_name("Entity4")
        .set<Transform>({Vec3::DOWN + Vec3::LEFT, Vec3::ZERO, Vec3::ONE * 0.1f})
        ;
    
    ecs.system<Player, Transform, LinearKinematics>()
        .kind(stages->Update)
        .iter([this](flecs::iter& it, Player* players, Transform* transforms, LinearKinematics* linearKinematics)
        {
            float deltaTime = it.delta_time();

            flecs::world ecs = it.world();
            
            flecs::entity mainCameraEntity = ecs.singleton<MainCamera>();
            flecs::entity cameraEntity = mainCameraEntity.get<MainCamera>()->camera;
            Transform * const cameraTransform = cameraEntity.get_mut<Transform>();

            flecs::entity inputEntity = ecs.singleton<Input>();
            const Input* const input = inputEntity.get<Input>();

            for (auto i : it)
            {
                Player& player = players[i];
                Transform& transform = transforms[i];
                LinearKinematics& linear = linearKinematics[i];

                HandleInput(deltaTime, input, cameraTransform, player, transform, linear);
            }
        });
}

// Public Methods

// Protected Fields

// Protected Methods

// Private Fields

// Private Methods

// flecs::entity PlayerECSModule::CreatePlayerEntity
// (
//     const std::string& name,
//     const velecs::Vec3 position /* = velecs::Vec3::ZERO */,
//     const velecs::Vec3 rotation /* = velecs::Vec3::ZERO */
// )
// {
//     auto playerEntity = ECSManager::CreateEntity(ecs(), name, position, rotation);
//     playerEntity.set<Mesh>({})
//         .set<Material>({})
//         .set<LinearKinematics>({})
//         .set<AngularKinematics>({});

//     return playerEntity;
// }

void PlayerECSModule::HandleInput
(
    const float deltaTime,
    const Input* const input,
    Transform* const cameraTransform,
    Player& player,
    Transform& transform,
    LinearKinematics& linear
)
{
    Vec3 velDir = (((input->IsHeld(SDLK_d)) ? Vec3::RIGHT : Vec3::ZERO) +
        ((input->IsHeld(SDLK_a)) ? Vec3::LEFT : Vec3::ZERO) +
        ((input->IsHeld(SDLK_w)) ? Vec3::UP : Vec3::ZERO) +
        ((input->IsHeld(SDLK_s)) ? Vec3::DOWN : Vec3::ZERO)).Normalize();

    linear.velocity = 1.0f * (velDir);


    player.targetCamPos = player.targetCamPos + (input->mouseWheel.y * Vec3::K);
    // Max and min are flipped and negative bc of the coordinate system
    player.targetCamPos.z = std::clamp(player.targetCamPos.z, -player.camMaxZoom, -player.camMinZoom);
    cameraTransform->position = Vec3::Lerp(cameraTransform->position, player.targetCamPos, player.camZoomSpeed * deltaTime);
}

} // namespace hh
