#include "Player.h"
#include "Headers.h"

Player::Player(int position, bool alive, int health, int maxHealth, int magic, int maxMagic, int attack)
{
	m_position = position;
	m_alive = alive;
	m_health = health;
	m_maxHeatlh = maxHealth;
	m_magic = magic;
	m_maxMagic = maxMagic;
};

Player::~Player() {};

void Player::Movement(Player &hero, vector <string> words, vector <string> paths, int MAP[16][16], string rooms[16], vector <Room*> map)
{
	if (Exist(words[1], paths))
	{
		int j = 0;
		while (j < rooms->length())
		{
			if (words[1] == rooms[j])
				break;
			j++;
		}
		hero.m_position = j;
		cout << "Te has movido a " << rooms[hero.m_position] << endl;
		cout << map[hero.m_position]->m_description << endl;
	}
	else
	{
		cout << "No es posible ir a " << words[1] << endl;
	}
	return;
};

void Player::Expansion(int position, vector <string>& paths, int MAP[16][16], string rooms[16])
{
	for (int i = 0; i < rooms->length(); i++)
	{
		if (MAP[position][i] == 1)
		{
			paths.push_back(rooms[i]);
		}
	}
	if (paths.size() > 1)
	{
		cout << "Puedes ir a estos lugares: " << "\t";
	}
	else
	{
		cout << "Solo puedes ir por aqui: " << "\t";
	}
	for (int i = 0; i < paths.size(); i++)
	{
		cout << paths[i];
		if (i < paths.size() - 1)
			cout << ", ";
	}
	cout << endl;
}

void Player::Stairs(Player &hero, vector <string> words, string rooms[16])
{
	if (words[0] == "subir")
	{
		if (hero.m_position == 5 || hero.m_position == 6 || hero.m_position == 13)
		{
			if (words[1] == "escalera" || words[1] == "escaleras")
			{
				switch (hero.m_position)
				{

				case 5:
					hero.m_position = 6;
					cout << "Has subido a " << rooms[hero.m_position] << endl;
					break;
				case 6:
					hero.m_position = 13;
					cout << "Has subido a " << rooms[hero.m_position] << endl;
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
		if (hero.m_position == 5 || hero.m_position == 6 || hero.m_position == 13)
		{
			if (words[1] == "escalera" || words[1] == "escaleras")
			{
				switch (hero.m_position)
				{

				case 13:
					hero.m_position = 6;
					cout << "Has bajado a " << rooms[hero.m_position] << endl;
					break;
				case 6:
					hero.m_position = 5;
					cout << "Has bajado a " << rooms[hero.m_position] << endl;
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
					cout << "El " << enemyNames[enemies[0]->m_name] << " ha muerto" << endl;
					enemies[0]->m_alive = 0;
					map[1]->m_healthPot = 1;
					map[1]->m_manaPot = 1;
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
					cout << "El " << enemyNames[enemies[1]->m_name] << " ha muerto" << endl;
				}
				else
				{
					if (enemies[1]->m_health > 1)
					{
						cout << "Atacaste al " << enemyNames[enemies[1]->m_name] << ", le quedan " << enemies[0]->m_health << " puntos de vida" << endl;
					}
					else
					{
						cout << "Atacaste al " << enemyNames[enemies[1]->m_name] << ", le queda " << enemies[0]->m_health << " punto de vida" << endl;
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
					cout << "El " << enemyNames[enemies[2]->m_name] << " ha muerto" << endl;
					enemies[2]->m_alive = 0;
					map[7]->m_healthPot = 1;
					map[7]->m_manaPot = 1;
				}
				else
				{
					if (enemies[2]->m_health > 1)
					{
						cout << "Atacaste al " << enemyNames[enemies[2]->m_name] << ", le quedan " << enemies[0]->m_health << " puntos de vida" << endl;
					}
					else
					{
						cout << "Atacaste al " << enemyNames[enemies[2]->m_name] << ", le queda " << enemies[0]->m_health << " punto de vida" << endl;
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
					cout << "El " << enemyNames[enemies[3]->m_name] << " ha muerto" << endl;
					enemies[3]->m_alive = 0;
					map[8]->m_healthPot = 1;
					map[8]->m_manaPot = 1;
				}
				else
				{
					if (enemies[3]->m_health > 1)
					{
						cout << "Atacaste al " << enemyNames[enemies[3]->m_name] << ", le quedan " << enemies[0]->m_health << " puntos de vida" << endl;
					}
					else
					{
						cout << "Atacaste al " << enemyNames[enemies[3]->m_name] << ", le queda " << enemies[0]->m_health << " punto de vida" << endl;
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
					cout << "El " << enemyNames[enemies[4]->m_name] << " ha muerto" << endl;
					enemies[4]->m_alive = 0;
					map[10]->m_healthPot = 1;
					map[10]->m_manaPot = 1;
				}
				else
				{
					if (enemies[4]->m_health > 1)
					{
						cout << "Atacaste al " << enemyNames[enemies[4]->m_name] << ", le quedan " << enemies[0]->m_health << " puntos de vida" << endl;
					}
					else
					{
						cout << "Atacaste al " << enemyNames[enemies[4]->m_name] << ", le queda " << enemies[0]->m_health << " punto de vida" << endl;
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
					cout << "El " << enemyNames[enemies[5]->m_name] << " ha muerto" << endl;
					enemies[5]->m_alive = 0;
					map[11]->m_healthPot = 1;
					map[11]->m_manaPot = 1;
				}
				else
				{
					if (enemies[5]->m_health > 1)
					{
						cout << "Atacaste al " << enemyNames[enemies[5]->m_name] << ", le quedan " << enemies[0]->m_health << " puntos de vida" << endl;
					}
					else
					{
						cout << "Atacaste al " << enemyNames[enemies[5]->m_name] << ", le queda " << enemies[0]->m_health << " punto de vida" << endl;
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
					cout << "El " << enemyNames[enemies[6]->m_name] << " ha muerto" << endl;
					enemies[6]->m_alive = 0;
					map[12]->m_healthPot = 1;
					map[12]->m_manaPot = 1;
				}
				else
				{
					if (enemies[6]->m_health > 1)
					{
						cout << "Atacaste al " << enemyNames[enemies[6]->m_name] << ", le quedan " << enemies[0]->m_health << " puntos de vida" << endl;
					}
					else
					{
						cout << "Atacaste al " << enemyNames[enemies[6]->m_name] << ", le queda " << enemies[0]->m_health << " punto de vida" << endl;
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
					cout << "El " << enemyNames[enemies[7]->m_name] << " ha muerto" << endl;
					enemies[7]->m_alive = 0;
					map[13]->m_healthPot = 1;
					map[13]->m_manaPot = 1;
				}
				else
				{
					if (enemies[7]->m_health > 1)
					{
						cout << "Atacaste al " << enemyNames[enemies[7]->m_name] << ", le quedan " << enemies[0]->m_health << " puntos de vida" << endl;
					}
					else
					{
						cout << "Atacaste al " << enemyNames[enemies[7]->m_name] << ", le queda " << enemies[0]->m_health << " punto de vida" << endl;
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
					cout << "El " << enemyNames[enemies[8]->m_name] << " ha muerto" << endl;
					enemies[8]->m_alive = 0;
					map[15]->m_healthPot = 1;
					map[15]->m_manaPot = 1;
				}
				else
				{
					if (enemies[8]->m_health > 1)
					{
						cout << "Atacaste al " << enemyNames[enemies[8]->m_name] << ", le quedan " << enemies[0]->m_health << " puntos de vida" << endl;
					}
					else
					{
						cout << "Atacaste al " << enemyNames[enemies[8]->m_name] << ", le queda " << enemies[0]->m_health << " punto de vida" << endl;
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
	}
}