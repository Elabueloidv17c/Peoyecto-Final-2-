#pragma once
#include "Headers.h"
#include "Enemy.h"
#include "Room.h"

class Player
{
public:
	vector <string> m_inventory;
	int m_position;
	bool m_alive;
	int m_health;
	int m_maxHeatlh;
	int m_magic;
	int m_maxMagic;
	int m_attack;
	
	void Movement(Player &hero, vector <string> words, vector <string> paths, int MAP[16][16], string rooms[16], vector <Room*> map);
	void Expansion(int position, vector <string>& paths, int MAP[16][16], string rooms[16]);
	void Stairs(Player &hero, vector <string> words, string rooms[16]);
	void Attack(vector <string> words, string enemyNames[5], Player hero, vector <Enemy*> &enemies, vector <Room*> map);

	Player(int position, bool alive, int health, int maxHealth, int magic, int maxMagic, int attack);
	~Player();
};

