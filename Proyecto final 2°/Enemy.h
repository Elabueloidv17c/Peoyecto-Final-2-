#pragma once
#include "Headers.h"
#include "Player.h"

class Enemy
{
public:
	int m_position;
	bool m_active;
	bool m_alive;
	bool m_key;
	int m_health;
	int m_name;
	int m_attack;

	Enemy();
	~Enemy();

	void Response(vector <string> words, string enemyNames[5], Player &hero, vector <Enemy*> enemies);
};

