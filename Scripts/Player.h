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

class PlayerMovement
{

};

class Player : public ScriptableEntity
{
private:
	TransformComponent* m_transform = nullptr;
	SpriteAnimatorComponent* m_animator = nullptr;
	GroundDetectionComponent* m_groundDetection = nullptr;
	AudioSourceComponent* m_audioSource = nullptr;

	int horizontal = 0;
	float moveSpeed = 4.5f;
	float jumpPower = 4.5f;

	AudioClip* jumpSound = nullptr;

public:
	EXPORT_CLASS(Player)
	virtual void Start() override
	{
		std::cout << "Player Start()\n";

		m_transform = GetComponent<TransformComponent>();
		m_animator = GetComponent<SpriteAnimatorComponent>();
		m_groundDetection = GetComponent<GroundDetectionComponent>();
		m_audioSource = GetComponent<AudioSourceComponent>();

		/*
		if (Asset* asset = m_app->GetAsset("C:\\BossFight Projects\\bison\\Assets\\bonus_sound.wav", false))
		{
			std::cout << "Found Jump Sound\n";
			jumpSound = ((AudioAsset*)asset)->GetAudioClip();
		}
		else
		{
			std::cout << "Not Found Jump Sound\n";
		}
		*/
		
	}


	void Flip()
	{
		m_transform->scale.x *= -1;
	}

	virtual void Update(float dt) override
	{
		horizontal = 0;

		if (m_app->GetInput().GetKeyDown(Key::A))
		{
			m_animator->controller->SetTrigger("attack");
		}

		if (m_app->GetInput().GetKey(Key::Left))
		{
			horizontal = -1;

			if (m_transform->scale.x > 0)
				Flip();
		}

		if (m_app->GetInput().GetKey(Key::Right))
		{
			horizontal = 1;
			if (m_transform->scale.x < 0)
				Flip();
		}

		if (m_animator && m_animator->controller)
			m_animator->controller->SetBool("running", horizontal != 0);

		if (Rigidbody2DComponent* rb2d = GetComponent<Rigidbody2DComponent>())
		{
			rb2d->SetVelocity(horizontal * moveSpeed, rb2d->GetVerticalY());
		}

		if (m_app->GetInput().GetKeyDown(Key::Space) && m_groundDetection->numGrounds > 0)
		{
			std::cout << "Player Jump!!!\n";

			if (m_audioSource)
				m_audioSource->Play(jumpSound);
			//m_app->GetAudio().PlaySound();
			
			if (Rigidbody2DComponent* rb2d = GetComponent<Rigidbody2DComponent>())
			{
				rb2d->ApplyImpulse(0, jumpPower);
			}
		}
	}

	virtual void OnCollisionEnter(Collision2D collision)
	{
		std::cout << "Player OnCollisionEnter: " << collision.name << std::endl;

		if (collision.name == "Door")
		{
			std::cout << "\n\nENTER THE DOOR\n\n";
			m_app->ChangeScene("Level2");
		}
	}

	virtual void OnCollisionExit(Collision2D collision)
	{
		std::cout << "Player OnCollisionExit: " << collision.name << std::endl;
	}
};
