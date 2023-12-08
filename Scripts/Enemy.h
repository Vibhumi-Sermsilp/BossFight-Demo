#pragma once

#include <iostream>
#include "Scene/ScriptableEntity.h"

class Enemy : public ScriptableEntity
{
private:

public:
	EXPORT_CLASS(Enemy)

	virtual void Start() override
	{
		std::cout << "Enemy Start()\n";
	}

};
