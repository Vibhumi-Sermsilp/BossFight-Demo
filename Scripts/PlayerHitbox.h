#pragma once

#include <iostream>
#include "Scene/ScriptableEntity.h"

class PlayerHitbox : public ScriptableEntity
{
private:
	float duration = 1.5f;
	float timer;

public:
	EXPORT_CLASS(PlayerHitbox)

	virtual void Start() override
	{
		std::cout << "PlayerHitbox Start()\n";
		timer = 0.0f;
	}

	virtual void Update(float deltaTime) override
	{
		if (timer >= duration)
		{
			Destroy();
			return;
		}

		timer += deltaTime;
	}

	virtual void OnCollisionEnter(Collision2D collision)
	{
		std::cout << "PlayerHitbox OnCollisionEnter: " << collision.name << std::endl;
	}

	virtual void OnCollisionExit(Collision2D collision)
	{
		std::cout << "PlayerHitbox OnCollisionExit: " << collision.name << std::endl;
	}
};
