#pragma once
#include "Enemy.h"
#include "Player.h"

Enemy::Enemy() {};

Enemy::~Enemy() {};

void Enemy::Response(vector <string> words, string enemyNames[5], Player &hero, vector <Enemy*> enemies)
{
	switch (hero.m_position)
	{
	case 1:
		if (enemies[0]->m_active == 1)
		{
			hero.m_health = hero.m_health - enemies[0]->m_attack;
			cout << "El " << enemyNames[enemies[0]->m_name] << " te ataco, redujo tus puntos de vida en " << enemies[0]->m_attack << endl;
		}
		break;
	case 4:
		if (enemies[1]->m_active == 1)
		{
			hero.m_health = hero.m_health - enemies[1]->m_attack;
			cout << "El " << enemyNames[enemies[1]->m_name] << " te ataco, redujo tus puntos de vida en " << enemies[1]->m_attack << endl;
		}
		break;
	case 7:
		if (enemies[2]->m_active == 1)
		{
			hero.m_health = hero.m_health - enemies[2]->m_attack;
			cout << "El " << enemyNames[enemies[2]->m_name] << " te ataco, redujo tus puntos de vida en " << enemies[2]->m_attack << endl;
		}
		break;
	case 8:
		if (enemies[3]->m_active == 1)
		{
			hero.m_health = hero.m_health - enemies[3]->m_attack;
			cout << "El " << enemyNames[enemies[3]->m_name] << " te ataco, redujo tus puntos de vida en " << enemies[3]->m_attack << endl;
		}
		break;
	case 10:
		if (enemies[4]->m_active == 1)
		{
			hero.m_health = hero.m_health - enemies[4]->m_attack;
			cout << "El " << enemyNames[enemies[4]->m_name] << " te ataco, redujo tus puntos de vida en " << enemies[4]->m_attack << endl;
		}
		break;
	case 11:
		if (enemies[5]->m_active == 1)
		{
			hero.m_health = hero.m_health - enemies[5]->m_attack;
			cout << "El " << enemyNames[enemies[5]->m_name] << " te ataco, redujo tus puntos de vida en " << enemies[5]->m_attack << endl;
		}
		break;
	case 12:
		if (enemies[6]->m_active == 1)
		{
			hero.m_health = hero.m_health - enemies[6]->m_attack;
			cout << "El " << enemyNames[enemies[6]->m_name] << " te ataco, redujo tus puntos de vida en " << enemies[6]->m_attack << endl;
		}
		break;
	case 13:
		if (enemies[0]->m_active == 1)
		{
			hero.m_health = hero.m_health - enemies[7]->m_attack;
			cout << "El " << enemyNames[enemies[7]->m_name] << " te ataco, redujo tus puntos de vida en " << enemies[7]->m_attack << endl;
		}
		break;
	case 15:
		if (enemies[8]->m_active == 1)
		{
			hero.m_health = hero.m_health - enemies[8]->m_attack;
			cout << "El " << enemyNames[enemies[8]->m_name] << " te ataco, redujo tus puntos de vida en " << enemies[8]->m_attack << endl;
		}
		break;
	}
}
