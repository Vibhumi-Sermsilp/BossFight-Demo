#pragma once

#include <iostream>
#include "Scene/ScriptableEntity.h"
#include "Scene/Scene.h"
#include "Input/Input.h"
#include "Components/TransformComponent.h"
#include "Components/SpriteRendererComponent.h"
#include "Components/Rigidbody2DComponent.h"
#include "Components/SpriteAnimatorComponent.h"
#include "Components/GroundDetectionComponent.h"
#include "Components/CameraComponent.h"
#include "Core/Entity.h"

class PlayerCamera : public ScriptableEntity
{
private:
	TransformComponent* m_transform = nullptr;
	CameraComponent* m_camera = nullptr;

public:
	EXPORT_CLASS(PlayerCamera)
	
	virtual void Start() override
	{
		std::cout << "PlayerCamera Start()\n";

		m_transform = GetComponent<TransformComponent>();
		m_camera = GetComponent<CameraComponent>();
	}

	virtual void LateUpdate(float dt) override
	{
		if (m_camera->targetEntity.IsValid())
		{
			TransformComponent* targetTransform = m_camera->targetEntity.GetComponent<TransformComponent>();
			m_transform->position.x = targetTransform->position.x;
			m_transform->position.y = targetTransform->position.y;
		}
	}
};
