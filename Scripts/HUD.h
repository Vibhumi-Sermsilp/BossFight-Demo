#pragma once

#include "Entity/ScriptableEntity.h"
#include "Components/UIComponents.h"
#include "Player.h"

class HUD : public ScriptableEntity
{
public:
	EXPORT_CLASS(HUD)

	Player* m_player = nullptr;

	virtual void Start() override
	{
		std::cout << "HUD Start()\n";
		m_player = dynamic_cast<Player*>(m_scene->GetScriptableEntity("Player"));
	}

	virtual void Update(float deltaTime) override
	{
		if (m_player != nullptr)
		{
			auto& text = Get<TextComponent>();
			text.text = "HP: " + std::to_string(m_player->health);
		}
	}
};