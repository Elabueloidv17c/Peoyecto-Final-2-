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
	void Movement(vector <string> words, vector <string> paths, int MAP[16][16], string rooms[16], vector <Room*> map, vector <Enemy*> enemies);
	void Stairs(vector <string> words, string rooms[16], vector <Room*> map);
	void Attack(vector <string> words, string enemyNames[5], Player hero, vector <Enemy*> &enemies, vector <Room*> map);
	void Spell(vector <string> words, string enemyNames[5], Player &hero, vector <Enemy*> &enemies, vector <Room*> map);
	void See(vector <string> words, vector <Room*> map);
	void Take(vector <string> words, Player &hero, vector <Room*> map, vector <Enemy*> enemies);
	void HUD(string rooms[16]);
	void Use(vector <string>words, Player &hero, vector <Room*> &map);
	void Explore(vector <string> words,vector <Room*> map, string rooms[16]);
	void Exit(vector <string> words, Player &hero);
	void Map(vector <Room*> &map, vector <string> words, string name);

	Player(int position, bool alive, int health, int maxHealth, int magic, int maxMagic, int attack, int magicAttack);
	~Player();

};

