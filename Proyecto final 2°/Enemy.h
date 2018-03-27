//por algún motivo el linker me dice que stoy haciendo una declaración en otro lado y no compila si no pongo esto...
#pragma once 

class Enemy
{
public:
	int m_position;
	bool m_active;
	bool m_alive;
	bool m_key;
	int m_health;
	int m_defense;
	int m_name;
	int m_attack;

	Enemy();
	~Enemy();
};

