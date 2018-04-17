#include "Player.h"
#include "Headers.h"
#include "Enemy.h"

void Descriptions(Player hero, vector <Enemy*> enemies);

Player::~Player() {};

Player::Player(int position, bool alive, int health, int maxHealth, int magic, int maxMagic, int attack, int magicAttack)
{
	m_position = position;
	m_alive = alive;
	m_health = health;
	m_maxHeatlh = maxHealth;
	m_magic = magic;
	m_maxMagic = maxMagic;
	m_attack = attack;
	m_magicAttack = magicAttack;
};

void Player::Expansion(int position, vector <string>& paths, int MAP[16][16], string rooms[16])
{
	for (int i = 0; i < 16; i++)
	{
		if (MAP[position][i] == 1)
		{
			paths.push_back(rooms[i]);
		}
	}
	cout << endl << "----------------------------------------------------------------------------------------------------------------" << endl;
	if (paths.size() > 1)
	{
		cout << "Puedes ir a estos lugares: " << "\t";
	}
	else if (paths.size() == 1)
	{
		cout << "Solo puedes ir por aqui: " << "\t";
	}
	else
	{
		cout << "No puedes ir a ninguna parte..." << endl;
	}
	for (int i = 0; i < paths.size(); i++)
	{
		cout << paths[i];
		if (i < paths.size() - 1)
			cout << ", ";
	}
	cout << endl;
	if (paths.size() == 0 && position == 5 || position == 6 || position == 14)
	{
		cout << "Pero puedes probar usar la escalera" << endl;
	}
	else if (position == 5 || position == 6 || position == 14)
	{
		cout << "Aunque tambien puedes probar usar la escalera" << endl;
	}
	cout << endl;
}

void Player::Movement(vector <string> words, vector <string> paths, int MAP[16][16], string rooms[16], vector <Room*> map, vector <Enemy*> enemies)
{
	if (Exist(words[1], paths))
	{
		int j = 0;
		while (j < 16)
		{
			if (words[1] == rooms[j])
				break;
			j++;
		}
		m_position = j;
		if (map[m_position]->m_explored == 0)
		{
			map[m_position]->m_explored = 1;
		}
		cout << "Te has movido a " << rooms[m_position] << endl << endl;
		cout << map[m_position]->m_description << endl;
		Descriptions(*this, enemies);
	}
	else
	{
		cout << "No es posible ir a " << words[1] << endl;
	}
	return;
};

void Player::Stairs(vector <string> words, string rooms[16], vector <Room*> map)
{
	if (words[0] == "subir")
	{
		if (m_position == 5 || m_position == 6)
		{
			if (words[1] == "escalera" || words[1] == "escaleras")
			{
				switch (m_position)
				{

				case 5:
					if (map[5]->m_locked == 0)
					{
						m_position = 6;
						map[m_position]->m_explored = 1;
						cout << "Has subido a " << rooms[m_position] << endl;
					}
					else
					{
						cout << "No puedes subir, la puerta esta cerrada" << endl;
					}
					break;
				case 6:
					if (map[6]->m_locked == 0)
					{
						m_position = 14;
						map[m_position]->m_explored = 1;
						cout << "Has subido a " << rooms[m_position] << endl;
					}
					else
					{
						cout << "No puedes subir, la puerta esta cerrada" << endl;
					}
					break;

				default:
					cout << "No puedo subir por aquí..." << endl;
					break;
				}
			}
			else
			{
				cout << "No puedo subir " << words[1] << endl;
			}
		}
		else
		{
			cout << "No hay nada que subir aqui..." << endl;
		}
	}
	else
	{
		if (m_position == 6 || m_position == 14)
		{
			if (words[1] == "escalera" || words[1] == "escaleras")
			{
				switch (m_position)
				{

				case 14:
					m_position = 6;
					cout << "Has bajado a " << rooms[m_position] << endl;
					break;
				case 6:
					m_position = 5;
					cout << "Has bajado a " << rooms[m_position] << endl;
					break;

				default:
					cout << "No puedo bajar por aqui..." << endl;
					break;
				}
			}
			else
			{
				cout << "No puedo subir " << words[1] << endl;
			}
		}
		else
		{
			cout << "No hay nada que bajar aqui..." << endl;
		}
	}
}

void Player::Attack(vector <string> words, string enemyNames[5], Player hero, vector <Enemy*> &enemies, vector <Room*> map)
{
	switch (hero.m_position)
	{
	case 1:
		if (enemies[0]->m_alive == 1)
		{
			if (words[1] == enemyNames[enemies[0]->m_name])
			{
				enemies[0]->m_health = enemies[0]->m_health - hero.m_attack;
				enemies[0]->m_active = 1;
				if (enemies[0]->m_health <= 0)
				{
					cout << "El " << enemyNames[enemies[0]->m_name] << " ha muerto, parece que dejo caer algo..." << endl;
					enemies[0]->m_alive = 0;
					map[1]->m_healthPot = 1;
					map[1]->m_manaPot = 1;
					if (enemies[0]->m_key == 1)
					{
						map[1]->m_key = 1;
					}
				}
				else
				{
					if (enemies[0]->m_health > 1)
					{
						cout << "Atacaste al " << enemyNames[enemies[0]->m_name] << ", le quedan " << enemies[0]->m_health << " puntos de vida" << endl;
					}
					else
					{
						cout << "Atacaste al " << enemyNames[enemies[0]->m_name] << ", le queda " << enemies[0]->m_health << " punto de vida" << endl;
					}
				}
				break;
			}
			else
			{
				cout << "No puedo atacar a " << words[1] << endl;
				break;
			}

		}
	case 4:
		if (enemies[1]->m_alive == 1)
		{
			if (words[1] == enemyNames[enemies[1]->m_name])
			{
				enemies[1]->m_health = enemies[1]->m_health - hero.m_attack;
				enemies[1]->m_active = 1;
				if (enemies[1]->m_health <= 0)
				{
					enemies[1]->m_alive = 0;
					map[4]->m_healthPot = 1;
					map[4]->m_manaPot = 1;
					if (enemies[1]->m_key == 1)
					{
						map[4]->m_key = 1;
					}
					cout << "El " << enemyNames[enemies[1]->m_name] << " ha muerto, parece que dejo caer algo..." << endl;
				}
				else
				{
					if (enemies[1]->m_health > 1)
					{
						cout << "Atacaste al " << enemyNames[enemies[1]->m_name] << ", le quedan " << enemies[1]->m_health << " puntos de vida" << endl;
					}
					else
					{
						cout << "Atacaste al " << enemyNames[enemies[1]->m_name] << ", le queda " << enemies[1]->m_health << " punto de vida" << endl;
					}
				}
				break;
			}
			else
			{
				cout << "No puedo atacar a " << words[1] << endl;
				break;
			}

		}
	case 7:
		if (enemies[2]->m_alive == 1)
		{
			if (words[1] == enemyNames[enemies[2]->m_name])
			{
				enemies[2]->m_health = enemies[2]->m_health - hero.m_attack;
				enemies[2]->m_active = 1;
				if (enemies[2]->m_health <= 0)
				{
					cout << "El " << enemyNames[enemies[2]->m_name] << " ha muerto, parece que dejo caer algo..." << endl;
					enemies[2]->m_alive = 0;
					map[7]->m_healthPot = 1;
					map[7]->m_manaPot = 1;
					if (enemies[2]->m_key == 1)
					{
						map[7]->m_key = 1;
					}
				}
				else
				{
					if (enemies[2]->m_health > 1)
					{
						cout << "Atacaste al " << enemyNames[enemies[2]->m_name] << ", le quedan " << enemies[2]->m_health << " puntos de vida" << endl;
					}
					else
					{
						cout << "Atacaste al " << enemyNames[enemies[2]->m_name] << ", le queda " << enemies[2]->m_health << " punto de vida" << endl;
					}
				}
				break;
			}
			else
			{
				cout << "No puedo atacar a " << words[1] << endl;
				break;
			}
		}
	case 8:
		if (enemies[3]->m_alive == 1)
		{
			if (words[1] == enemyNames[enemies[3]->m_name])
			{
				enemies[3]->m_health = enemies[3]->m_health - hero.m_attack;
				enemies[3]->m_active = 1;
				if (enemies[3]->m_health <= 0)
				{
					cout << "El " << enemyNames[enemies[3]->m_name] << " ha muerto, parece que dejo caer algo..." << endl;
					enemies[3]->m_alive = 0;
					map[8]->m_healthPot = 1;
					map[8]->m_manaPot = 1;
					if (enemies[3]->m_key == 1)
					{
						map[8]->m_key = 1;
					}
				}
				else
				{
					if (enemies[3]->m_health > 1)
					{
						cout << "Atacaste al " << enemyNames[enemies[3]->m_name] << ", le quedan " << enemies[3]->m_health << " puntos de vida" << endl;
					}
					else
					{
						cout << "Atacaste al " << enemyNames[enemies[3]->m_name] << ", le queda " << enemies[3]->m_health << " punto de vida" << endl;
					}
				}
				break;
			}
			else
			{
				cout << "No puedo atacar a " << words[1] << endl;
				break;
			}
		}
	case 10:
		if (enemies[4]->m_alive == 1)
		{
			if (words[1] == enemyNames[enemies[4]->m_name])
			{
				enemies[4]->m_health = enemies[4]->m_health - hero.m_attack;
				if (enemies[4]->m_health <= 0)
				{
					cout << "El " << enemyNames[enemies[4]->m_name] << " ha muerto, parece que dejo caer algo..." << endl;
					enemies[4]->m_alive = 0;
					map[10]->m_healthPot = 1;
					map[10]->m_manaPot = 1;
					if (enemies[4]->m_key == 1)
					{
						map[10]->m_key = 1;
					}
				}
				else
				{
					if (enemies[4]->m_health > 1)
					{
						cout << "Atacaste al " << enemyNames[enemies[4]->m_name] << ", le quedan " << enemies[4]->m_health << " puntos de vida" << endl;
					}
					else
					{
						cout << "Atacaste al " << enemyNames[enemies[4]->m_name] << ", le queda " << enemies[4]->m_health << " punto de vida" << endl;
					}
				}
				break;
			}
			else
			{
				cout << "No puedo atacar a " << words[1] << endl;
				break;
			}
		}
	case 11:
		if (enemies[5]->m_alive == 1)
		{
			if (words[1] == enemyNames[enemies[5]->m_name])
			{
				enemies[5]->m_health = enemies[5]->m_health - hero.m_attack;
				enemies[5]->m_active = 1;
				if (enemies[5]->m_health <= 0)
				{
					cout << "El " << enemyNames[enemies[5]->m_name] << " ha muerto, parece que dejo caer algo..." << endl;
					enemies[5]->m_alive = 0;
					map[11]->m_healthPot = 1;
					map[11]->m_manaPot = 1;
					if (enemies[5]->m_key == 1)
					{
						map[11]->m_key = 1;
					}
				}
				else
				{
					if (enemies[5]->m_health > 1)
					{
						cout << "Atacaste al " << enemyNames[enemies[5]->m_name] << ", le quedan " << enemies[5]->m_health << " puntos de vida" << endl;
					}
					else
					{
						cout << "Atacaste al " << enemyNames[enemies[5]->m_name] << ", le queda " << enemies[5]->m_health << " punto de vida" << endl;
					}
				}
				break;
			}
			else
			{
				cout << "No puedo atacar a " << words[1] << endl;
				break;
			}
		}
	case 12:
		if (enemies[6]->m_alive == 1)
		{
			if (words[1] == enemyNames[enemies[6]->m_name])
			{
				enemies[6]->m_health = enemies[6]->m_health - hero.m_attack;
				enemies[6]->m_active = 1;
				if (enemies[6]->m_health <= 0)
				{
					cout << "El " << enemyNames[enemies[6]->m_name] << " ha muerto, parece que dejo caer algo..." << endl;
					enemies[6]->m_alive = 0;
					map[12]->m_healthPot = 1;
					map[12]->m_manaPot = 1;
					if (enemies[6]->m_key == 1)
					{
						map[12]->m_key = 1;
					}
				}
				else
				{
					if (enemies[6]->m_health > 1)
					{
						cout << "Atacaste al " << enemyNames[enemies[6]->m_name] << ", le quedan " << enemies[6]->m_health << " puntos de vida" << endl;
					}
					else
					{
						cout << "Atacaste al " << enemyNames[enemies[6]->m_name] << ", le queda " << enemies[6]->m_health << " punto de vida" << endl;
					}
				}
				break;
			}
			else
			{
				cout << "No puedo atacar a " << words[1] << endl;
				break;
			}
		}
	case 13:
		if (enemies[7]->m_alive == 1)
		{
			if (words[1] == enemyNames[enemies[7]->m_name])
			{
				enemies[7]->m_health = enemies[7]->m_health - hero.m_attack;
				enemies[7]->m_active = 1;
				if (enemies[7]->m_health <= 0)
				{
					cout << "El " << enemyNames[enemies[7]->m_name] << " ha muerto, parece que dejo caer algo..." << endl;
					enemies[7]->m_alive = 0;
					map[13]->m_healthPot = 1;
					map[13]->m_manaPot = 1;
					if (enemies[7]->m_key == 1)
					{
						map[13]->m_key = 1;
					}
				}
				else
				{
					if (enemies[7]->m_health > 1)
					{
						cout << "Atacaste al " << enemyNames[enemies[7]->m_name] << ", le quedan " << enemies[7]->m_health << " puntos de vida" << endl;
					}
					else
					{
						cout << "Atacaste al " << enemyNames[enemies[7]->m_name] << ", le queda " << enemies[7]->m_health << " punto de vida" << endl;
					}
				}
				break;
			}
			else
			{
				cout << "No puedo atacar a " << words[1] << endl;
				break;
			}
		}
	case 15:
		if (enemies[8]->m_alive == 1)
		{
			if (words[1] == enemyNames[enemies[8]->m_name])
			{
				enemies[8]->m_health = enemies[8]->m_health - hero.m_attack;
				if (enemies[8]->m_health <= 0)
				{
					cout << "El " << enemyNames[enemies[8]->m_name] << " ha muerto... has triunfado!" << endl;
					enemies[8]->m_alive = 0;
				}
				else
				{
					if (enemies[8]->m_health > 1)
					{
						cout << "Atacaste al " << enemyNames[enemies[8]->m_name] << ", le quedan " << enemies[8]->m_health << " puntos de vida" << endl;
					}
					else
					{
						cout << "Atacaste al " << enemyNames[enemies[8]->m_name] << ", le queda " << enemies[8]->m_health << " punto de vida" << endl;
					}
				}
				break;
			}
			else
			{
				cout << "No puedo atacar a " << words[1] << endl;
				break;
			}
		}
	default:
		cout << "Aqui no hay enemigos" << endl;
		break;
	}
}

void Player::Spell(vector <string> words, string enemyNames[5], Player &hero, vector <Enemy*> &enemies, vector <Room*> map)
{
	switch (hero.m_position)
	{
	case 1:
		if (enemies[0]->m_alive == 1)
		{
			if (words[1] == enemyNames[enemies[0]->m_name])
			{
				if (hero.m_magic >= 20)
				{
					enemies[0]->m_health = enemies[0]->m_health - hero.m_magicAttack;
					hero.m_magic = hero.m_magic - 20;
					enemies[0]->m_active = 1;
					if (enemies[0]->m_health <= 0)
					{
						cout << "El " << enemyNames[enemies[0]->m_name] << " ha muerto, parece que dejo caer algo..." << endl;
						enemies[0]->m_alive = 0;
						map[1]->m_healthPot = 1;
						map[1]->m_manaPot = 1;
						if (enemies[0]->m_key == 1)
						{
							map[1]->m_key = 1;
						}
					}
					else
					{
						if (enemies[0]->m_health > 1)
						{
							cout << "Le lanzaste un hechizo al " << enemyNames[enemies[0]->m_name] << ", le quedan " << enemies[0]->m_health << " puntos de vida" << endl;
						}
						else
						{
							cout << "Le lanzaste un hechizo al " << enemyNames[enemies[0]->m_name] << ", le queda " << enemies[0]->m_health << " punto de vida" << endl;
						}
					}
					break;
				}
				else
				{
					cout << "No tienes suficiente energia magica" << endl;
				}
				break;
			}
			else
			{
				cout << "No puedo lanzarle un hechizo a " << words[1] << endl;
				break;
			}
		}
	case 4:
		if (enemies[1]->m_alive == 1)
		{
			if (words[1] == enemyNames[enemies[1]->m_name])
			{
				if (hero.m_magic >= 20)
				{
				enemies[1]->m_health = enemies[1]->m_health - hero.m_magicAttack;
				hero.m_magic = hero.m_magic - 20;
				enemies[1]->m_active = 1;
				if (enemies[1]->m_health <= 0)
				{
					cout << "El " << enemyNames[enemies[1]->m_name] << " ha muerto, parece que dejo caer algo..." << endl;
					enemies[1]->m_alive = 0;
					map[4]->m_healthPot = 1;
					map[4]->m_manaPot = 1;
					if (enemies[1]->m_key == 1)
					{
						map[4]->m_key = 1;
					}
				}
				else
				{
					if (enemies[1]->m_health > 1)
					{
						cout << "Le lanzaste un hechizo al " << enemyNames[enemies[1]->m_name] << ", le quedan " << enemies[1]->m_health << " puntos de vida" << endl;
					}
					else
					{
						cout << "Le lanzaste un hechizo al " << enemyNames[enemies[1]->m_name] << ", le queda " << enemies[1]->m_health << " punto de vida" << endl;
					}
				}
				break;
			}
				else
				{
					cout << "No tienes suficiente energia magica" << endl;
				}
				break;
			}
			else
			{
				cout << "No puedo lanzarle un hechizo a " << words[1] << endl;
				break;
			}
		}
	case 7:
		if (enemies[2]->m_alive == 1)
		{
			if (words[1] == enemyNames[enemies[2]->m_name])
			{
				if (hero.m_magic >= 20)
				{
					enemies[2]->m_health = enemies[2]->m_health - hero.m_magicAttack;
					hero.m_magic = hero.m_magic - 20;
					enemies[2]->m_active = 1;
					if (enemies[2]->m_health <= 0)
					{
						cout << "El " << enemyNames[enemies[2]->m_name] << " ha muerto, parece que dejo caer algo..." << endl;
						enemies[2]->m_alive = 0;
						map[7]->m_healthPot = 1;
						map[7]->m_manaPot = 1;
						if (enemies[2]->m_key == 1)
						{
							map[7]->m_key = 1;
						}
					}
					else
					{
						if (enemies[2]->m_health > 1)
						{
							cout << "Le lanzaste un hechizo al " << enemyNames[enemies[2]->m_name] << ", le quedan " << enemies[2]->m_health << " puntos de vida" << endl;
						}
						else
						{
							cout << "Le lanzaste un hechizo al " << enemyNames[enemies[2]->m_name] << ", le queda " << enemies[2]->m_health << " punto de vida" << endl;
						}
					}
					break;
				}
				else
				{
					cout << "No tienes suficiente energia magica" << endl;
				}
				break;
			}
			else
			{
				cout << "No puedo lanzarle un hechizo a " << words[1] << endl;
				break;
			}

		}
	case 8:
		if (enemies[3]->m_alive == 1)
		{
			if (words[1] == enemyNames[enemies[3]->m_name])
			{
				if (hero.m_magic >= 20)
				{
					enemies[3]->m_health = enemies[3]->m_health - hero.m_magicAttack;
					hero.m_magic = hero.m_magic - 20;
					enemies[3]->m_active = 1;
					if (enemies[3]->m_health <= 0)
					{
						cout << "El " << enemyNames[enemies[3]->m_name] << " ha muerto, parece que dejo caer algo..." << endl;
						enemies[3]->m_alive = 0;
						map[8]->m_healthPot = 1;
						map[8]->m_manaPot = 1;
						if (enemies[3]->m_key == 1)
						{
							map[8]->m_key = 1;
						}
					}
					else
					{
						if (enemies[3]->m_health > 1)
						{
							cout << "Le lanzaste un hechizo al " << enemyNames[enemies[3]->m_name] << ", le quedan " << enemies[3]->m_health << " puntos de vida" << endl;
						}
						else
						{
							cout << "Le lanzaste un hechizo al " << enemyNames[enemies[3]->m_name] << ", le queda " << enemies[3]->m_health << " punto de vida" << endl;
						}
					}
					break;
				}
				else
				{
					cout << "No tienes suficiente energia magica" << endl;
				}
				break;
			}
			else
			{
				cout << "No puedo lanzarle un hechizo a " << words[1] << endl;
				break;
			}

		}
	case 10:
		if (enemies[4]->m_alive == 1)
		{
			if (words[1] == enemyNames[enemies[4]->m_name])
			{
				if (hero.m_magic >= 20)
				{
					enemies[4]->m_health = enemies[4]->m_health - hero.m_magicAttack;
					hero.m_magic = hero.m_magic - 20;
					enemies[4]->m_active = 1;
					if (enemies[4]->m_health <= 0)
					{
						cout << "El " << enemyNames[enemies[4]->m_name] << " ha muerto, parece que dejo caer algo..." << endl;
						enemies[4]->m_alive = 0;
						map[10]->m_healthPot = 1;
						map[10]->m_manaPot = 1;
						if (enemies[4]->m_key == 1)
						{
							map[10]->m_key = 1;
						}
					}
					else
					{
						if (enemies[4]->m_health > 1)
						{
							cout << "Le lanzaste un hechizo al " << enemyNames[enemies[4]->m_name] << ", le quedan " << enemies[4]->m_health << " puntos de vida" << endl;
						}
						else
						{
							cout << "Le lanzaste un hechizo al " << enemyNames[enemies[4]->m_name] << ", le queda " << enemies[4]->m_health << " punto de vida" << endl;
						}
					}
					break;
				}
				else
				{
					cout << "No tienes suficiente energia magica" << endl;
				}
				break;
			}
			else
			{
				cout << "No puedo lanzarle un hechizo a " << words[1] << endl;
				break;
			}

		}
	case 11:
		if (enemies[5]->m_alive == 1)
		{
			if (words[1] == enemyNames[enemies[5]->m_name])
			{
				if (hero.m_magic >= 20)
				{
					enemies[5]->m_health = enemies[5]->m_health - hero.m_magicAttack;
					hero.m_magic = hero.m_magic - 20;
					enemies[5]->m_active = 1;
					if (enemies[5]->m_health <= 0)
					{
						cout << "El " << enemyNames[enemies[5]->m_name] << " ha muerto, parece que dejo caer algo..." << endl;
						enemies[5]->m_alive = 0;
						map[11]->m_healthPot = 1;
						map[11]->m_manaPot = 1;
						if (enemies[5]->m_key == 1)
						{
							map[11]->m_key = 1;
						}
					}
					else
					{
						if (enemies[5]->m_health > 1)
						{
							cout << "Le lanzaste un hechizo al " << enemyNames[enemies[5]->m_name] << ", le quedan " << enemies[5]->m_health << " puntos de vida" << endl;
						}
						else
						{
							cout << "Le lanzaste un hechizo al " << enemyNames[enemies[5]->m_name] << ", le queda " << enemies[5]->m_health << " punto de vida" << endl;
						}
					}
					break;
				}
				else
				{
					cout << "No tienes suficiente energia magica" << endl;
				}
				break;
			}
			else
			{
				cout << "No puedo lanzarle un hechizo a " << words[1] << endl;
				break;
			}

		}
	case 12:
		if (enemies[6]->m_alive == 1)
		{
			if (words[1] == enemyNames[enemies[6]->m_name])
			{
				if (hero.m_magic >= 20)
				{
					enemies[6]->m_health = enemies[6]->m_health - hero.m_magicAttack;
					hero.m_magic = hero.m_magic - 20;
					enemies[6]->m_active = 1;
					if (enemies[6]->m_health <= 0)
					{
						cout << "El " << enemyNames[enemies[6]->m_name] << " ha muerto, parece que dejo caer algo..." << endl;
						enemies[6]->m_alive = 0;
						map[12]->m_healthPot = 1;
						map[12]->m_manaPot = 1;
						if (enemies[6]->m_key == 1)
						{
							map[12]->m_key = 1;
						}
					}
					else
					{
						if (enemies[6]->m_health > 1)
						{
							cout << "Le lanzaste un hechizo al " << enemyNames[enemies[6]->m_name] << ", le quedan " << enemies[6]->m_health << " puntos de vida" << endl;
						}
						else
						{
							cout << "Le lanzaste un hechizo al " << enemyNames[enemies[6]->m_name] << ", le queda " << enemies[6]->m_health << " punto de vida" << endl;
						}
					}
					break;
				}
				else
				{
					cout << "No tienes suficiente energia magica" << endl;
				}
				break;
			}
			else
			{
				cout << "No puedo lanzarle un hechizo a " << words[1] << endl;
				break;
			}

		}
	case 13:
		if (enemies[7]->m_alive == 1)
		{
			if (words[1] == enemyNames[enemies[7]->m_name])
			{
				if (hero.m_magic >= 20)
				{
					enemies[7]->m_health = enemies[7]->m_health - hero.m_magicAttack;
					hero.m_magic = hero.m_magic - 20;
					enemies[7]->m_active = 1;
					if (enemies[7]->m_health <= 0)
					{
						cout << "El " << enemyNames[enemies[7]->m_name] << " ha muerto, parece que dejo caer algo..." << endl;
						enemies[7]->m_alive = 0;
						map[13]->m_healthPot = 1;
						map[13]->m_manaPot = 1;
						if (enemies[7]->m_key == 1)
						{
							map[13]->m_key = 1;
						}
					}
					else
					{
						if (enemies[7]->m_health > 1)
						{
							cout << "Le lanzaste un hechizo al " << enemyNames[enemies[7]->m_name] << ", le quedan " << enemies[7]->m_health << " puntos de vida" << endl;
						}
						else
						{
							cout << "Le lanzaste un hechizo al " << enemyNames[enemies[7]->m_name] << ", le queda " << enemies[7]->m_health << " punto de vida" << endl;
						}
					}
					break;
				}
				else
				{
					cout << "No tienes suficiente energia magica" << endl;
				}
				break;
			}
			else
			{
				cout << "No puedo lanzarle un hechizo a " << words[1] << endl;
				break;
			}

		}
	case 15:
		if (enemies[8]->m_alive == 1)
		{
			if (words[1] == enemyNames[enemies[8]->m_name])
			{
				if (hero.m_magic >= 20)
				{
					enemies[8]->m_health = enemies[8]->m_health - hero.m_magicAttack;
					hero.m_magic = hero.m_magic - 20;
					enemies[8]->m_active = 1;
					if (enemies[8]->m_health <= 0)
					{
						cout << "El " << enemyNames[enemies[8]->m_name] << " ha muerto... has triunfado!" << endl;
						enemies[8]->m_alive = 0;
						map[15]->m_healthPot = 1;
						map[15]->m_manaPot = 1;
						if (enemies[8]->m_key == 1)
						{
							map[15]->m_key = 1;
						}
					}
					else
					{
						if (enemies[8]->m_health > 1)
						{
							cout << "Le lanzaste un hechizo al " << enemyNames[enemies[8]->m_name] << ", le quedan " << enemies[8]->m_health << " puntos de vida" << endl;
						}
						else
						{
							cout << "Le lanzaste un hechizo al " << enemyNames[enemies[8]->m_name] << ", le queda " << enemies[8]->m_health << " punto de vida" << endl;
						}
					}
					break;
				}
				else
				{
					cout << "No tienes suficiente energia magica" << endl;
				}
			}
			else
			{
				cout << "No puedo lanzarle un hechizo a " << words[1] << endl;
				break;
			}
			break;

		}
	default:
		cout << "Aqui no hay enemigos" << endl;
		break;
	}
}

void Player::See(vector<string> words, vector <Room*> map)
{
	if (words[1] == "inventario")
	{
		if (m_inventory.size() == 0)
		{
			cout << "No tienes nada en el inventario" << endl;
		}
		else if (m_inventory.size() == 1)
		{
			cout << "Tienes un elemento en el inventario: " << endl << m_inventory[0] << endl;
		}
		else
		{
			cout << "Tienes los siguientes elementos en el inventario: " << endl;
			for (int i = 0; i < m_inventory.size(); i++)
			{
				cout << m_inventory[i];
				if (i < m_inventory.size() - 1)
				{
					cout << ", ";
				}
			}
			cout << endl;
		}
	}

	else if (words[1] == "ayuda")
	{
		cout << "Como jugar?" << endl;
		cout << "Para ejecutar cualquier accion debes introducir comandos de dos palabras separadas por un espacio" << endl << endl;
		cout << "Que puedo hacer?" << endl;
		cout << "Ir: Esta accion sirve para desplazarte por el mapa, debes escribir el comando y una habitacion, por ejemplo:" << endl;
		cout << "    -Ir explanada" << endl;
		cout << "Subir/Bajar: Esta accion sirve para desplazarte por las escaleras, debes escribir el comando y la palabra 'escalera', por ejemplo:" << endl;
		cout << "    -Subir escalera" << endl;
		cout << "Explorar: Esta accion sirve para explorar la habitacion en la que te encuentras, con esto puedes encontrar objetos, por ejemplo:" << endl;
		cout << "    -Explorar sala" << endl;
		cout << "Tomar: Esta accion sirve para tomar los objetos que encuentres en las habitaciones y añadirlo a tu inventario, por ejemplo:" << endl;
		cout << "    -Tomar medicina" << endl;
		cout << "Usar: Esta accion sirve para usar los objetos que tengas en tu inventario, por ejemplo:" << endl;
		cout << "    -Usar medicina" << endl;
		cout << "Atacar: Esta accion sirve para atacar a los enemigos que encuentres en las habitaciones, por ejemplo:" << endl;
		cout << "    -Atacar gremlin" << endl;
		cout << "Maldecir: Esta accion sirve para lanzar una maldicion que infringe mucho daño al enemigo, por ejemplo:" << endl;
		cout << "    -Maldecir Goblin" << endl;
		cout << "Ver: Esta accion sirve para ver los elementos que ya tienes en tu inventario, por ejemplo:" << endl;
		cout << "    -Ver inventario" << endl;
		cout << "Salvar: Esta accion sirve para guardas tus progresos en el juego, por ejemplo:" << endl;
		cout << "    -Salvar partida" << endl;
		cout << "Cerrar: Esta accion sirve para cerrar el juego y perder la partida, por ejemplo:" << endl;
		cout << "    -Cerrar juego" << endl << endl;
		cout << "Puedes usar mayusculas o minusculas a tu gusto, el juego reconocera las palabras de todos modos" << endl << endl;
	}

	else if (words[1] == "mapa")
	{
		if (map[0]->m_explored == 1)
		{
			cout << "                                         Primer piso:" << endl;
			cout << endl;
			cout << "                                        --------------" << endl;
			cout << "                                        |   Entrada  |" << endl;
			cout << "                                        --------------" << endl;
			cout << "                                               |" << endl;
			cout << "                                               |" << endl;
		}

		if (map[1]->m_explored == 1)
		{
			cout << "                                        --------------" << endl;
			cout << "                                --------|  Explanada |--------" << endl;
			cout << "                                |       --------------       |" << endl;
		}

		if (map[2]->m_explored == 0 && map[3]->m_explored == 1)
		{
			cout << "                        ----------------" << endl;
			cout << "                        |   Almacen    |" << endl;
			cout << "                        ----------------" << endl;
			cout << "                                |" << endl;
		}

		if (map[2]->m_explored == 1 && map[3]->m_explored == 0)
		{
			cout << "                                                      ----------------" << endl;
			cout << "                                                      |    Pasillo   |" << endl;
			cout << "                                                      ----------------" << endl;
			cout << "                                                              |" << endl;
		}

		if (map[2]->m_explored == 1 && map[3]->m_explored == 1)
		{
			cout << "                        ----------------              ----------------" << endl;
			cout << "                        |   Almacen    |              |    Pasillo   |" << endl;
			cout << "                        ----------------              ----------------" << endl;
			cout << "                                |                            |" << endl;
		}

		if (map[4]->m_explored == 1)
		{
			cout << "                                ------------------------------" << endl;
			cout << "                                                |" << endl;
			cout << "                                                |" << endl;
			cout << "                                        ----------------" << endl;
			cout << "                                        |     Sala     |" << endl;
			cout << "                                        ----------------" << endl;
			cout << "                                                |" << endl;
			cout << "                                                |" << endl;
		}

		if (map[5]->m_explored == 1)
		{
			cout << "                                        ----------------" << endl;
			cout << "                                        |  Escalera_pb |" << endl;
			cout << "                                        ----------------" << endl;
		}

		if (map[9]->m_explored == 1)
		{
			cout << "                                       Segundo piso:" << endl;
			cout << endl;
			cout << "                                        ------------" << endl;
			cout << "                                        |  Balcon  |" << endl;
			cout << "                                        ------------" << endl;
		}

		if (map[6]->m_explored == 1 && map[7]->m_explored == 1 && map[8]->m_explored == 1)
		{
			if (map[9]->m_explored == 0)
			{
				cout << "                                       Segundo piso:" << endl;
				cout << endl;
				cout << endl;
				cout << endl;
				cout << endl;
			}
			cout << "                                              |" << endl;
			cout << "                                              |" << endl;
			cout << "                 --------------        --------------           -------------" << endl;
			cout << "		         | Dormitorio |--------| Escalera_1 |-----------|   Cocina  |" << endl;
			cout << "                 --------------        --------------           -------------" << endl;
			cout << "                                              |" << endl;
			cout << "                                              |" << endl;
		}

		if (map[6]->m_explored == 1 && map[7]->m_explored == 0 && map[8]->m_explored == 1)
		{
			if (map[9]->m_explored == 0)
			{
				cout << "                                       Segundo piso:" << endl;
				cout << endl;
				cout << endl;
				cout << endl;
				cout << endl;
			}
			cout << "                                              |" << endl;
			cout << "                                              |" << endl;
			cout << "                 --------------        --------------" << endl;
			cout << "		         | Dormitorio |--------| Escalera_1 |" << endl;
			cout << "                 --------------        --------------" << endl;
			cout << "                                              |" << endl;
			cout << "                                              |" << endl;
		}

		if (map[6]->m_explored == 1 && map[7]->m_explored == 1 && map[8]->m_explored == 0)
		{
			if (map[9]->m_explored == 0)
			{
				cout << "                                       Segundo piso:" << endl;
				cout << endl;
				cout << endl;
				cout << endl;
				cout << endl;
			}
			cout << "                                              |" << endl;
			cout << "                                              |" << endl;
			cout << "                                       --------------           -------------" << endl;
			cout << "		                       --------| Escalera_1 |-----------|   Cocina  |" << endl;
			cout << "                                       --------------           -------------" << endl;
			cout << "                                              |" << endl;
			cout << "                                              |" << endl;
		}

		if (map[6]->m_explored == 1 && map[7]->m_explored == 0 && map[8]->m_explored == 0)
		{
			if (map[9]->m_explored == 0)
			{
				cout << "                                       Segundo piso:" << endl;
				cout << endl;
				cout << endl;
				cout << endl;
				cout << endl;
			}
			cout << "                                              |" << endl;
			cout << "                                              |" << endl;
			cout << "                                       --------------" << endl;
			cout << "		                       --------| Escalera_1 |-----------" << endl;
			cout << "                                       --------------" << endl;
			cout << "                                              |" << endl;
			cout << "                                              |" << endl;
		}

		if (map[11]->m_explored == 1 && map[10]->m_explored == 1 && map[12]->m_explored == 1)
		{
			cout << "                --------------          -------------           ------------" << endl;
			cout << "                |   Arena    |----------|    Bar    |-----------| Calabozo |" << endl;
			cout << "                --------------          -------------           ------------" << endl;
			cout << "                       |                                              |" << endl;
			cout << "                       |                                              |" << endl;
		}

		if (map[11]->m_explored == 1 && map[10]->m_explored == 1 && map[12]->m_explored == 0)
		{
			cout << "                --------------          -------------" << endl;
			cout << "                |   Arena    |----------|    Bar    |-----------" << endl;
			cout << "                --------------          -------------" << endl;
			cout << "                       |" << endl;
			cout << "                       |" << endl;
		}

		if (map[11]->m_explored == 1 && map[10]->m_explored == 0 && map[12]->m_explored == 1)
		{
			cout << "                                        -------------           ------------" << endl;
			cout << "                                        |    Bar    |-----------| Calabozo |" << endl;
			cout << "                                        -------------           ------------" << endl;
			cout << "                                                                      |" << endl;
			cout << "                                                                      |" << endl;
		}

		if (map[13]->m_explored == 1)
		{
			cout << "                       ------------------------------------------------" << endl;
			cout << "                                              |" << endl;
			cout << "                                        -------------" << endl;
			cout << "                                        |  Armeria  |" << endl;
			cout << "                                        -------------" << endl;
		}

		if (map[14]->m_explored == 1)
		{
			cout << "                                         Tercer piso:" << endl;
			cout << endl;
			cout << "                                        --------------" << endl;
			cout << "                                        | Escalera_2 |" << endl;
			cout << "                                        --------------" << endl;
			cout << "                                               |" << endl;
			cout << "                                               |" << endl;
		}

		if (map[15]->m_explored == 1)
		{
			cout << "                                        --------------" << endl;
			cout << "                                        |   Atalaya  |" << endl;
			cout << "                                        --------------" << endl;
		}
	}

	else
	{
		cout << "No existe el comando ver " << words[1] << endl;
	}
}

void Player::Take(vector <string> words, Player &hero, vector <Room*> map, vector <Enemy*> enemies)
{
	if (words[1] == "llave")
	{
		if (map[hero.m_position]->m_key == 1)
		{
			hero.m_inventory.push_back("llave");
			map[hero.m_position]->m_key = 0;
			cout << "Has tomado una llave" << endl;
		}
		else
		{
			cout << "No hay ninguna llave aqui" << endl;
		}
	}
	else if (words[1] == "medicina")
	{
		if (map[hero.m_position]->m_healthPot == 1)
		{
			hero.m_inventory.push_back("medicina");
			map[hero.m_position]->m_healthPot = 0;
			cout << "Has tomado la medicina" << endl;
		}
		else
		{
			cout << "No hay medicina por aqui" << endl;
		}
	}
	else if (words[1] == "magia")
	{
		if (map[hero.m_position]->m_manaPot == 1)
		{
			hero.m_inventory.push_back("magia");
			map[hero.m_position]->m_manaPot = 0;
			cout << "Has absorbido la magia" << endl;
		}
		else
		{
			cout << "No hay rastros de magia por aqui" << endl;
		}
	}
	else
	{
		cout << "No hay " << words[1] << " por aqui" << endl;
	}
}

void Player::HUD(string rooms[16])
{
	cout << "Vida:" << "\t" << m_health << "/" << m_maxHeatlh << "\t" << "\t" << "\t" << "Magia:" << "\t";
	cout << m_magic << "/" << m_maxMagic << "\t" << "\t" << "Posicion: " << rooms[m_position] << "\t" << "\t";
	cout << "Llave:" << "\t";
	bool exist = false;
	for (int i = 0; i < m_inventory.size(); i++)
	{
		if (m_inventory[i] == "llave")
		{
			cout << "Conseguida" << endl;
			exist = true;
		}
	}
	if (!exist)
	{
		cout << "No conseguida" << endl;
	}
}

void Player::Use(vector <string> words, Player &hero, vector <Room*> &map)
{
	if (words[1] == "llave")
	{
		if (hero.m_position == 5)
		{
			if (Exist(words[1], hero.m_inventory))
			{
				Eraser(words[1], hero.m_inventory);
				map[5]->m_locked = 0;
				cout << "Has abierto la puerta" << endl;
			}
			else if (map[5]->m_locked == 0)
			{
				cout << "Ya abriste esta puerta" << endl;
			}
			else
			{
				cout << "No tienes la llave" << endl;
			}
		}
		else if (hero.m_position == 6)
		{
			if (Exist(words[1], hero.m_inventory))
			{
				Eraser(words[1], hero.m_inventory);
				map[6]->m_locked = 0;
				cout << "Has abierto la puerta" << endl;
			}
			else if (map[6]->m_locked == 0)
			{
				cout << "Ya abriste esta puerta" << endl;
			}
		}
		else
		{
			cout << "No puedes usar la llave aqui" << endl;
		}
	}
	if (words[1] == "magia")
	{
		if (Exist(words[1], hero.m_inventory))
		{
			Eraser(words[1], hero.m_inventory);
			hero.m_magic = hero.m_magic + 10;
			cout << "Tu reserva de energia magica se ha incrementado en 10" << endl;
		}
		else
		{
			cout << "No tienes magia en el inventario" << endl;
		}
	}
	if (words[1] == "medicina")
	{
		if (Exist(words[1], hero.m_inventory))
		{
			if (hero.m_health < 100)
			{
				Eraser(words[1], hero.m_inventory);
				if (hero.m_health > 85)
				{
					hero.m_health = 100;
				}
				else
				{
					hero.m_health = hero.m_health + 15;
				}
				cout << "Tus puntos de vida han incrementado a " << hero.m_health << endl;
			}
			else
			{
				cout << "Tu salud ya esta al maximo" << endl;
			}
		}
		else
		{
			cout << "No tienes medicina en el inventario" << endl;
		}
	}
}

void Player::Explore(vector <string> words, vector <Room*> map, string rooms[16])
{
	vector <string> loot;
	bool correct = false;
	for (int i = 0; i < 16; i++)
	{
		if (words[1] == rooms[map[i]->m_position])
		{
			if (map[i]->m_healthPot)
			{
				loot.push_back("medicina");
			}
			if (map[i]->m_manaPot)
			{
				loot.push_back("magia");
			}
			if (map[i]->m_key)
			{
				loot.push_back("llave");
			}
			if (correct == false)
			{
				correct = true;
			}
			break;
		}
	}
	if(correct)
	{
		if (loot.size() == 0)
		{
			cout << "No encontraste nada" << endl;
		}
		else if (loot.size() == 1)
		{
			cout << "Encontraste el siguiente objeto: " << endl << loot[0] << endl;
		}
		else
		{
			cout << "Encontraste los siguientes objetos: " << endl;
			for (int i = 0; i < loot.size(); i++)
			{
				cout << loot[i];
				if (i < loot.size() - 1)
				{
					cout << ", ";
				}
			}
			cout << endl;
		}
	}
	else
	{
		cout << "No puedo explorar " << words[1] << " desde aqui" << endl;
	}
	loot.clear();
}

void Player::Exit(vector <string> words, Player &hero)
{
	if (words[1] == "juego")
	{
		hero.m_alive = 0;
	}
	else
	{
		cout << "Para terminar la partida y cerrar el juego tienes que teclear el comando 'Cerrar juego'" << endl;
	}
}

void Player::Map(vector <Room*> &map, vector <string> words, string name)
{
	ofstream* writer = new ofstream;
	writer->open(name +"_map.txt");

	if (map[0]->m_explored == 1)
	{
		*writer << "                                         Primer piso:" << endl;
		*writer << endl;
		*writer << "                                        --------------" << endl;
		*writer << "                                        |   Entrada  |" << endl;
		*writer << "                                        --------------" << endl;
		*writer << "                                               |" << endl;
		*writer << "                                               |" << endl;
	}

	if (map[1]->m_explored == 1)
	{
		*writer << "                                        --------------" << endl;
		*writer << "                                --------|  Explanada |--------" << endl;
		*writer << "                                |       --------------       |" << endl;
	}

	if (map[2]->m_explored == 0 && map[3]->m_explored == 1)
	{
		*writer << "                        ----------------" << endl;
		*writer << "                        |   Almacen    |" << endl;
		*writer << "                        ----------------" << endl;
		*writer << "                                |" << endl;
	}

	if (map[2]->m_explored == 1 && map[3]->m_explored == 0)
	{
		*writer << "                                                      ----------------" << endl;
		*writer << "                                                      |    Pasillo   |" << endl;
		*writer << "                                                      ----------------" << endl;
		*writer << "                                                              |" << endl;
	}

	if (map[2]->m_explored == 1 && map[3]->m_explored == 1)
	{
		*writer << "                        ----------------              ----------------" << endl;
		*writer << "                        |   Almacen    |              |    Pasillo   |" << endl;
		*writer << "                        ----------------              ----------------" << endl;
		*writer << "                                |                            |" << endl;
	}

	if (map[4]->m_explored == 1)
	{
		*writer << "                                ------------------------------" << endl;
		*writer << "                                                |" << endl;
		*writer << "                                                |" << endl;
		*writer << "                                        ----------------" << endl;
		*writer << "                                        |     Sala     |" << endl;
		*writer << "                                        ----------------" << endl;
		*writer << "                                                |" << endl;
		*writer << "                                                |" << endl;
	}

	if (map[5]->m_explored == 1)
	{
		*writer << "                                        ----------------" << endl;
		*writer << "                                        |  Escalera_pb |" << endl;
		*writer << "                                        ----------------" << endl;
	}

	if (map[9]->m_explored == 1)
	{
		*writer << "                                       Segundo piso:" << endl;
		*writer << endl;
		*writer << "                                        ------------" << endl;
		*writer << "                                        |  Balcon  |" << endl;
		*writer << "                                        ------------" << endl;
	}

	if (map[6]->m_explored == 1 && map[7]->m_explored == 1 && map[8]->m_explored == 1)
	{
		if (map[9]->m_explored == 0)
		{
			*writer << "                                       Segundo piso:" << endl;
			*writer << endl;
			*writer << endl;
			*writer << endl;
			*writer << endl;
		}
		*writer << "                                              |" << endl;
		*writer << "                                              |" << endl;
		*writer << "                 --------------        --------------           -------------" << endl;
		*writer << "		         | Dormitorio |--------| Escalera_1 |-----------|   Cocina  |" << endl;
		*writer << "                 --------------        --------------           -------------" << endl;
		*writer << "                                              |" << endl;
		*writer << "                                              |" << endl;
	}

	if (map[6]->m_explored == 1 && map[7]->m_explored == 0 && map[8]->m_explored == 1)
	{
		if (map[9]->m_explored == 0)
		{
			*writer << "                                       Segundo piso:" << endl;
			*writer << endl;
			*writer << endl;
			*writer << endl;
			*writer << endl;
		}
		*writer << "                                              |" << endl;
		*writer << "                                              |" << endl;
		*writer << "                 --------------        --------------" << endl;
		*writer << "		         | Dormitorio |--------| Escalera_1 |" << endl;
		*writer << "                 --------------        --------------" << endl;
		*writer << "                                              |" << endl;
		*writer << "                                              |" << endl;
	}

	if (map[6]->m_explored == 1 && map[7]->m_explored == 1 && map[8]->m_explored == 0)
	{
		if (map[9]->m_explored == 0)
		{
			*writer << "                                       Segundo piso:" << endl;
			*writer << endl;
			*writer << endl;
			*writer << endl;
			*writer << endl;
		}
		*writer << "                                              |" << endl;
		*writer << "                                              |" << endl;
		*writer << "                                       --------------           -------------" << endl;
		*writer << "		                       --------| Escalera_1 |-----------|   Cocina  |" << endl;
		*writer << "                                       --------------           -------------" << endl;
		*writer << "                                              |" << endl;
		*writer << "                                              |" << endl;
	}

	if (map[6]->m_explored == 1 && map[7]->m_explored == 0 && map[8]->m_explored == 0)
	{
		if (map[9]->m_explored == 0)
		{
			*writer << "                                       Segundo piso:" << endl;
			*writer << endl;
			*writer << endl;
			*writer << endl;
			*writer << endl;
		}
		*writer << "                                              |" << endl;
		*writer << "                                              |" << endl;
		*writer << "                                       --------------" << endl;
		*writer << "		                       --------| Escalera_1 |-----------" << endl;
		*writer << "                                       --------------" << endl;
		*writer << "                                              |" << endl;
		*writer << "                                              |" << endl;
	}

	if (map[11]->m_explored == 1 && map[10]->m_explored == 1 && map[12]->m_explored == 1)
	{
		*writer << "                --------------          -------------           ------------" << endl;
		*writer << "                |   Arena    |----------|    Bar    |-----------| Calabozo |" << endl;
		*writer << "                --------------          -------------           ------------" << endl;
		*writer << "                       |                                              |" << endl;
		*writer << "                       |                                              |" << endl;
	}

	if (map[11]->m_explored == 1 && map[10]->m_explored == 1 && map[12]->m_explored == 0)
	{
		*writer << "                --------------          -------------" << endl;
		*writer << "                |   Arena    |----------|    Bar    |-----------" << endl;
		*writer << "                --------------          -------------" << endl;
		*writer << "                       |" << endl;
		*writer << "                       |" << endl;
	}

	if (map[11]->m_explored == 1 && map[10]->m_explored == 0 && map[12]->m_explored == 1)
	{
		*writer << "                                        -------------           ------------" << endl;
		*writer << "                                        |    Bar    |-----------| Calabozo |" << endl;
		*writer << "                                        -------------           ------------" << endl;
		*writer << "                                                                      |" << endl;
		*writer << "                                                                      |" << endl;
	}

	if (map[13]->m_explored == 1)
	{
		*writer << "                       ------------------------------------------------" << endl;
		*writer << "                                              |" << endl;
		*writer << "                                        -------------" << endl;
		*writer << "                                        |  Armeria  |" << endl;
		*writer << "                                        -------------" << endl;
	}

	if (map[14]->m_explored == 1)
	{
		*writer << "                                         Tercer piso:" << endl;
		*writer << endl;
		*writer << "                                        --------------" << endl;
		*writer << "                                        | Escalera_2 |" << endl;
		*writer << "                                        --------------" << endl;
		*writer << "                                               |" << endl;
		*writer << "                                               |" << endl;
	}

	if (map[15]->m_explored == 1)
	{
		*writer << "                                        --------------" << endl;
		*writer << "                                        |   Atalaya  |" << endl;
		*writer << "                                        --------------" << endl;
	}

	writer->close();
	delete(writer);
}