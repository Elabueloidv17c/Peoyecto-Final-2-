#pragma once
#include "Headers.h"
#include "Room.h"

class Enemy;

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
	int m_magicAttack;
	
	void Expansion(int position, vector <string>& paths, int MAP[16][16], string rooms[16]);
	void Movement(Player &hero, vector <string> words, vector <string> paths, int MAP[16][16], string rooms[16], vector <Room*> map, vector <Enemy*> enemies);
	void Stairs(Player &hero, vector <string> words, string rooms[16], vector <Room*> map);
	void Attack(vector <string> words, string enemyNames[5], Player hero, vector <Enemy*> &enemies, vector <Room*> map);
	void Spell(vector <string> words, string enemyNames[5], Player &hero, vector <Enemy*> &enemies, vector <Room*> map);
	void See(Player hero, vector <string> words);
	void Take(vector <string> words, Player &hero, vector <Room*> map, vector <Enemy*> enemies);
	void HUD(Player hero);
	void Use(vector <string>words, Player &hero, vector <Room*> &map);
	void Explore(vector <string> words,vector <Room*> map, string rooms[16]);
	void Exit(vector <string> words, Player &hero);

	Player(int position, bool alive, int health, int maxHealth, int magic, int maxMagic, int attack, int magicAttack);
	~Player();
};

