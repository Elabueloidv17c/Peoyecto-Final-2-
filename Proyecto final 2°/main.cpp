#include <algorithm>
#include <iostream>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <vector>
#include <time.h>

using namespace std;

int MAP[16][16] =
{
	//Primer nivel
	{ 0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
{ 0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0 },
{ 0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0 },
{ 0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0 },
{ 0,0,1,1,0,1,0,0,0,0,0,0,0,0,0,0 },
{ 0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0 },
//Segundo nivel
{ 0,0,0,0,0,0,0,1,1,1,0,1,0,0,1,0 },
{ 0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0 },
{ 0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0 },
{ 0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0 },
{ 0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0 },
{ 0,0,0,0,0,0,1,0,0,0,1,0,1,0,0,0 },
{ 0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0 },
{ 0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0 },
//Tercer nivel
{ 0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1 },
{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0 }
};

vector <string> rooms =
{
	//Primer nivel
	"entrada",
	"explanada",
	"pasillo",
	"almacen",
	"sala",
	"escalera_PB",
	//Segundo nivel
	"escaleras_1",
	"cocina",
	"dormitorio",
	"balcon",
	"arena",
	"bar",
	"calabozo",
	"armeria",
	//Tercer nivel
	"escaleras_2",
	"atalaya"
};

class Room
{
public:
	string m_description;
	int m_position;
	bool m_locked;
	bool m_manaPot;
	bool m_healthPot;
	Room(string description, int position, bool locked, bool manaPot, bool healthPot)
	{
		m_description = description;
		m_position = position;
		m_locked = locked;
		m_manaPot = manaPot;
		m_healthPot = healthPot;
	}
};

class Player
{
public:
	Player() {};
	~Player() {};
	vector <string> m_inventory;
	int m_position;
	bool m_alive;
	int m_health;
	int m_maxHeatlh;
	int m_magic;
	int m_maxMagic;
	int m_defense;
};

class Enemy
{
public:
	int m_position;
	bool m_active;
	bool m_alive;
	bool m_key;
	int m_health;
	int m_defense;

	Enemy(int position, bool active, bool alive, bool key, int health, int defense)
	{
		m_position = position;
		m_active = active;
		m_alive = alive;
		m_key = key;
		m_health = health;
		m_defense = defense;
	}
};

class Boss
{
public:
	int m_position;
	bool m_active;
	bool m_alive;
	int m_health;
	int m_defense;

	Boss(int position, bool active, bool alive, int health, int defense)
	{
		m_position = position;
		m_active = active;
		m_alive = alive;
		m_health = health;
		m_defense = defense;
	}
};

//Busca las posibles expansiones y se las notifica al usuario
void Expansion(int position, vector <string>& paths)
{
	for (int i = 0; i < rooms.size(); i++)
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

//Vacia los vectores
void Cleaner(vector <string>& content)
{
	while (content.size() > 0)
	{
		content.erase(content.begin());
	}
	return;
}

//Te dice si un string existe dentro de un vector
bool Exist(string word, vector <string> paths)
{
	for (int i = 0; i < paths.size(); i++)
	{
		if (paths[i] == word)
		{
			return true;
		}
	}
	return false;
}

//Separador de palabras de un input
void Split(vector <string>& words, const string& str, char space)
{
	string word;
	istringstream separator(str);

	while (getline(separator, word, space))
	{
		words.push_back(word);
	}
	for (int i = 0; i < words.size(); i++)
	{
		for (int j = 0; j < words[i].length(); j++)
		{
			words[i][j] = tolower(words[i][j]);
		}
	}
	return;
}

//Movimiento
void Movement(Player &Hero, vector <string> words, vector <string> paths)
{
	if (Exist(words[1], paths))
	{
		int j = 0;
		while (j < rooms.size())
		{
			if (words[1] == rooms[j])
				break;
			j++;
		}
		Hero.m_position = j;
		cout << "Te has movido a " << rooms[Hero.m_position] << endl;
	}
	else
	{
		cout << "No es posible ir a " << words[1] << endl;
	}
	return;
};

//Cargar partida ver 1.0
void LoadHero(Player &hero, vector <int>& data)
{
	ifstream reader;
	int value;
	reader.open("Default.txt");
	while (!reader.eof())
	{
		reader >> value;
		data.push_back(value);
	}
	hero.m_position = data[0];
	hero.m_alive = data[1];
	hero.m_health = data[2];
	hero.m_maxHeatlh = data[3];
	hero.m_magic = data[4];
	hero.m_maxMagic = data[5];
	hero.m_defense = data[6];
	reader.close();
	return;
}

//Llama a las otras funciones
void Caller(Player hero, vector <string> paths, vector <string> words)
{
	string phrase;
	while (true)
	{
		Expansion(hero.m_position, paths);
		getline(cin, phrase);
		Split(words, phrase, ' ');
		if (words.size() > 0)
		{
			if (words[0] == "ir")
			{
				Movement(hero, words, paths);
			}
			else
			{
				cout << "Operacion invalida" << endl;
			}
		}
		else
		{
			cout << "Operacion invalida" << endl;
		}
		Cleaner(words);
		Cleaner(paths);
	}
	return;
}

int main()
{
	vector <string> paths, words;
	vector <int> data;
	Player hero;
	LoadHero(hero, data);
	Caller(hero, paths, words);
	cin.ignore();
	cin.get();
	return 0;
}

//Uso correcto de los Try/Catch en multiples casos (como loops)
//fstream en puntero