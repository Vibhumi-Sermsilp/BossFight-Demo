#pragma once

#include <iostream>
#include "Scene/ScriptableEntity.h"

class Enemy : public ScriptableEntity
{
private:
	int hp = 1;

public:
	EXPORT_CLASS(Enemy)

	virtual void Start() override
	{
		std::cout << "Enemy Start()\n";
	}

	virtual void Update(float dt) override
	{
		if (hp <= 0)
		{
			Die();
		}
	}

	void Die()
	{
		Destroy();
		return;
	}

	virtual void OnCollisionEnter(Collision2D collision)
	{
		std::cout << "Enemy OnCollisionEnter: " << collision.name << std::endl;

		if (collision.name == "PlayerHitbox")
		{
			std::cout << "\n\nEnemy Hit!!!\n\n";
			hp--;
		}
	}

	virtual void OnCollisionExit(Collision2D collision)
	{
		std::cout << "Enemy OnCollisionExit: " << collision.name << std::endl;
	}

};
