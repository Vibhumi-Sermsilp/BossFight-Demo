#pragma once

#include <iostream>
#include "Entity/ScriptableEntity.h"
#include "Scene/Scene.h"
#include "Input/Input.h"
#include "Components/TransformComponent.h"
#include "Components/SpriteRendererComponent.h"
#include "Components/Rigidbody2DComponent.h"
#include "Components/SpriteAnimatorComponent.h"
#include "Components/GroundDetectionComponent.h"
#include "Components/CameraComponent.h"
#include "Entity/Entity.h"

class PlayerCamera : public ScriptableEntity
{
public:
	EXPORT_CLASS(PlayerCamera)
	
	virtual void Start() override
	{
		std::cout << "PlayerCamera Start()\n";
	}

	virtual void LateUpdate(float dt) override
	{
		auto& transform = Get<TransformComponent>();
		auto& camera = Get<CameraComponent>();

		if (camera.targetEntity.IsValid())
		{
			auto& targetTransform = camera.targetEntity.Get<TransformComponent>();
			transform.position.x = targetTransform.position.x;
			transform.position.y = targetTransform.position.y;
		}
	}
};
