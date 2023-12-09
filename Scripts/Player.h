#pragma once

#include <iostream>
#include "Scene/ScriptableEntity.h"
#include "Scene/Scene.h"
#include "Input/Input.h"
#include "Audio/Audio.h"
#include "Core/Application.h"
#include "Asset/AssetManager.h"
#include "Asset/AudioAsset.h"
#include "Components/TransformComponent.h"
#include "Components/SpriteRendererComponent.h"
#include "Components/Rigidbody2DComponent.h"
#include "Components/SpriteAnimatorComponent.h"
#include "Components/GroundDetectionComponent.h"
#include "Components/AudioSourceComponent.h"

class Player : public ScriptableEntity
{
private:
	Rigidbody2DComponent* m_rigidbody2d = nullptr;
	TransformComponent* m_transform = nullptr;
	GroundDetectionComponent* m_groundDetection = nullptr;
	SpriteAnimatorComponent* m_animator = nullptr;
	AudioSourceComponent* m_audioSource = nullptr;

	/* Movement */
	glm::vec2 velocity = { 0.0f, 0.0f };
	int horizontal = 0;
	float moveSpeed = 3.5f;
	float movementSmoothing = 0.05f;
	bool airControl = true;
	float airControlMultiplier = 0.9f;

	/* Jump */
	bool isGrounded;
	bool jump = false;
	float jumpForce = 4.5f;
	int maxBonusJump = 1;
	int currentBonusJump;

	/* Attack */
	Entity hitboxPrefab;

	/* Audio */
	AudioClip* jumpSound = nullptr;

public:
	EXPORT_CLASS(Player)

	virtual void Start() override
	{
		std::cout << "Player Start()\n";

		m_rigidbody2d = GetComponent<Rigidbody2DComponent>();
		m_transform = GetComponent<TransformComponent>();
		m_groundDetection = GetComponent<GroundDetectionComponent>();
		m_animator = GetComponent<SpriteAnimatorComponent>();
		m_audioSource = GetComponent<AudioSourceComponent>();

		hitboxPrefab = m_app->GetPrefabByName("PlayerHitbox");
	}

	virtual void Update(float dt) override
	{
		/*--Handle Ground Check--*/
		bool wasGrounded = isGrounded;
		isGrounded = false;

		if (m_groundDetection->numGrounds > 0)
		{
			isGrounded = true;
			currentBonusJump = maxBonusJump;
		}
		/*-----------------------*/

		/*-----Handle Input-----*/
		horizontal = 0;
		if (m_app->GetInput().GetKey(Key::A))
		{
			horizontal = -1;
		}
		if (m_app->GetInput().GetKey(Key::D))
		{
			horizontal = 1;
		}
		if (m_app->GetInput().GetKeyDown(Key::Space))
		{
			jump = true;
			std::cout << "Jump Bonus Left: " << currentBonusJump;
		}

		if (m_app->GetInput().GetKeyDown(Key::X) && hitboxPrefab.IsValid())
		{
			int direction = m_transform->scale.x > 0 ? 1 : -1;
			glm::vec3 offset = { direction * 1.0f, 0.0f, 0.0f };
			m_scene->InstantiateEntity(hitboxPrefab, m_transform->position + offset);
		}
		/*----------------------*/
	}

	virtual void LateUpdate(float dt) override
	{
		Move(horizontal * moveSpeed, jump);
		jump = false;
	}

	void Move(float move, bool jump)
	{
		if (!isGrounded && airControl)
		{
			move *= airControlMultiplier;
		}

		if (isGrounded || airControl)
		{
			glm::vec2 targetVelocity{ move, m_rigidbody2d->GetVerticalY() };
			m_rigidbody2d->SetVelocity(move, m_rigidbody2d->GetVerticalY());

			if (move > 0 && m_transform->scale.x < 0)
			{
				Flip();
			}
			else if (move < 0 && m_transform->scale.x > 0)
			{
				Flip();
			}
		}

		if ((isGrounded || currentBonusJump > 0) && jump)
		{
			if (!isGrounded)
			{
				m_rigidbody2d->SetVelocity(m_rigidbody2d->GetVelocityX(), 0);
				currentBonusJump--;
			}

			isGrounded = false;
			m_rigidbody2d->ApplyImpulse(0.1f, jumpForce);
		}
	}

	void Flip()
	{
		m_transform->scale.x *= -1;
	}

	void Foo()
	{
		std::cout << "Player::Foo() !!!\n";
		Flip();
	}

	virtual void ExportFunctions() override
	{
		EXPORT_FUNCTION(Player::Foo);
	}

	virtual void OnCollisionEnter(Collision2D collision)
	{
		std::cout << "Player OnCollisionEnter: " << collision.name << std::endl;
	}

	virtual void OnCollisionExit(Collision2D collision)
	{
		std::cout << "Player OnCollisionExit: " << collision.name << std::endl;
	}
};
