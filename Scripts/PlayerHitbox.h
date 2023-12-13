#pragma once

#include <iostream>
#include "Entity/ScriptableEntity.h"

class PlayerHitbox : public ScriptableEntity
{
private:
	float duration = 0.25f;
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
};
