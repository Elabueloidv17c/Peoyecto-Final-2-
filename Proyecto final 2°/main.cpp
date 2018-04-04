#pragma once
#include "Headers.h"
#include "Player.h"
#include "Room.h"
#include "Enemy.h"

string rooms [16] = {
	//Primer nivel
	"entrada",
	"explanada",
	"pasillo",
	"almacen",
	"sala",
	"escalera_pb",
	//Segundo nivel
	"escalera_1",
	"cocina",
	"dormitorio",
	"balcon",
	"arena",
	"bar",
	"calabozo",
	"armeria",
	//Tercer nivel
	"escalera_2",
	"atalaya"
};

string enemyNames [5] = {
	"gremlin",
	"goblin",
	"orco",
	"troll",
	"dragon"
};

int MAP[16][16] = {
//Primer nivel
{ 0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
{ 0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0 },
{ 0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0 },
{ 0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0 },
{ 0,0,1,1,0,1,0,0,0,0,0,0,0,0,0,0 },
{ 0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0 },
//Segundo nivel
{ 0,0,0,0,0,0,0,1,1,1,0,1,0,0,0,0 },
{ 0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0 },
{ 0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0 },
{ 0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0 },
{ 0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0 },
{ 0,0,0,0,0,0,1,0,0,0,1,0,1,0,0,0 },
{ 0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0 },
{ 0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0 },
//Tercer nivel
{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0 }
};

//Describe los enemigos de los cuartos
void Descriptions(Player hero, vector <Enemy*> enemies)
{
	switch (hero.m_position)
	{
	case 1:
		if (enemies[0]->m_alive == 1)
		{
			cout << "Hay un " << enemyNames[enemies[0]->m_name] << " en la parte trasera, esta rematando al ultimo sobreviviente" << endl;
			break;
		}
	case 4:
		if (enemies[1]->m_alive == 1)
		{
			cout << "Hay un " << enemyNames[enemies[1]->m_name]  << " sentado en un sillon, esta jugando con un dedo humano" << endl;
			break;
		}
	case 7:
		if (enemies[2]->m_alive == 1)
		{
			cout << "Hay un " << enemyNames[enemies[2]->m_name] << " degustando comida podrida de un sarten" << endl;
			break;
		}
	case 8:
		if (enemies[3]->m_alive == 1)
		{
			cout << "Hay un " << enemyNames[enemies[3]->m_name] << " recostado en la cama principal" << endl;
			break;
		}
	case 10:
		if (enemies[4]->m_alive == 1)
		{
			cout << "Justo al centro hay un " << enemyNames[enemies[4]->m_name] << " con armadura pesada levantando los brazos y gritando, cuando te ve se lanza sobre ti" << endl;
			break;
		}
	case 11:
		if (enemies[5]->m_alive == 1)
		{
			cout << "Un " << enemyNames[enemies[5]->m_name] << " borracho lanza su tarro de carveza contra la pared y te grita" << endl;
			break;
		}
	case 12:
		if (enemies[6]->m_alive == 1)
		{
			cout << "En la oscuridad alcanzas a ver los ojos brillantes de un " << enemyNames[enemies[6]->m_name] << endl;
			break;
		}
	case 13:
		if (enemies[7]->m_alive == 1)
		{
			cout << "Puedes ver a un " << enemyNames[enemies[7]->m_name] << " buscando su mazo entre las armas" << endl;
			break;
		}
	case 15:
		if (enemies[8]->m_alive == 1)
		{
			cout << "El " << enemyNames[enemies[8]->m_name] << " ruge y el castillo tiembla, lanza un aliento de fuego sobre ti" << endl;
			break;
		}
	default:
		cout << "No hay ningun enemigo a la vista" << endl;
		break;
	}
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

//Crea todos los objetos del juego
void NewGame(vector <Room*>& map, vector <Enemy*>& enemies)
{
	//Esto crea un vector de todos mis cuartos y les asigna los valores a sus miembros
	for (int i = 0; i < 16; i++)
	{
		map.push_back(new Room());
	}
	for (int i = 0; i < map.size(); i++)
	{
		map[i]->m_position = i;
		map[i]->m_healthPot = 0;
		map[i]->m_manaPot = 0;
		map[i]->m_locked = 0;
	}

	map[0]->m_description = "Estas en la entrada del castillo, hay un puente de madera frente a ti";
	map[1]->m_description = "Estas en la explanada, hay carretas con paja y cadaveres humanos por todos lados";
	map[2]->m_description = "Estas en un pasillo angosto y oscuro, puedes ver telarañas en las paredes";
	map[3]->m_description = "Estas en el almacen, hay escobas, barriles de madera y picos para la paja";
	map[4]->m_description = "Estas en la sala, los pilares tienen detalles de oro y hay lamparas lujosas de cristal en el techo";
	map[5]->m_description = "Estas en la torre de las escaleras, en la planta baja";
	map[6]->m_description = "Estas en la torre de las escaleras, en el primer piso";
	map[7]->m_description = "Estas en la cocina, hay muchos utensilios tirados y comida podrida";
	map[8]->m_description = "Estas en el dormitorio, las camas estan destendidas y hay sangre en las sabanas";
	map[9]->m_description = "Estas en el balcon, hay plantas a tu alrededor, la vista del atardecer es hermosa";
	map[10]->m_description = "Estas en una gigantezca arena circular, hay sangre, armas y cadaveres por doquier";
	map[11]->m_description = "Estas en el bar, hay muchas botellas vacias y licor tirado por todas partes";
	map[12]->m_description = "Estas en un calabozo oscuro, puedes ver cadenas y miembros amputados de personas colgando de ellas";
	map[13]->m_description = "Estas en la armeria, por desgracia solo hay armas y armaduras rotas";
	map[14]->m_description = "Estas en la cima de la torre de las escaleras";
	map[15]->m_description = "Has llegado a la cumbre del castillo, el dragon derrumba la puerta, no hay vuelta atras";

	map[5]->m_locked = 1;
	map[6]->m_locked = 1;
	map[14]->m_locked = 1;

	map[1]->m_healthPot = 1;
	map[4]->m_healthPot = 1;
	map[7]->m_healthPot = 1;
	map[8]->m_healthPot = 1;
	map[10]->m_healthPot = 1;
	map[11]->m_healthPot = 1;
	map[12]->m_healthPot = 1;
	map[13]->m_healthPot = 1;
	map[15]->m_healthPot = 1;

	map[4]->m_manaPot = 1;
	map[7]->m_manaPot = 1;
	map[8]->m_manaPot = 1;
	map[10]->m_manaPot = 1;
	map[12]->m_manaPot = 1;

	//Esto crea un vector con los enemigos
	for (int i = 0; i < 9; i++)
	{
		enemies.push_back(new Enemy ());
	}

	//Aqui le doy valor a todos sus miembros
	enemies[0]->m_position = 1;
	enemies[0]->m_name = 0;
	enemies[0]->m_attack = 2;
	enemies[0]->m_defense = 0;
	enemies[0]->m_health = 20;

	enemies[1]->m_position = 4;
	enemies[1]->m_name = 1;
	enemies[1]->m_attack = 4;
	enemies[1]->m_defense = 0;
	enemies[1]->m_health = 40;

	enemies[2]->m_position = 7;
	enemies[2]->m_name = 1;
	enemies[2]->m_attack = 4;
	enemies[2]->m_defense = 0;
	enemies[2]->m_health = 40;

	enemies[3]->m_position = 8;
	enemies[3]->m_name = 2;
	enemies[3]->m_attack = 6;
	enemies[3]->m_defense = 1;
	enemies[3]->m_health = 60;

	enemies[4]->m_position = 10;
	enemies[4]->m_name = 3;
	enemies[4]->m_attack = 8;
	enemies[4]->m_defense = 2;
	enemies[4]->m_health = 80;

	enemies[5]->m_position = 11;
	enemies[5]->m_name = 2;
	enemies[5]->m_attack = 6;
	enemies[5]->m_defense = 1;
	enemies[5]->m_health = 60;

	enemies[6]->m_position = 12;
	enemies[6]->m_name = 1;
	enemies[6]->m_attack = 4;
	enemies[6]->m_defense = 0;
	enemies[6]->m_health = 40;

	enemies[7]->m_position = 13;
	enemies[7]->m_name = 2;
	enemies[7]->m_attack = 6;
	enemies[7]->m_defense = 1;
	enemies[7]->m_health = 60;

	enemies[8]->m_position = 15;
	enemies[8]->m_name = 4;
	enemies[8]->m_attack = 12;
	enemies[8]->m_defense = 3;
	enemies[8]->m_health = 100;

	for (int i = 0; i < enemies.size(); i++)
	{
		enemies[i]->m_active = 0;
		enemies[i]->m_alive = 1;
		enemies[i]->m_key = 0;
	}
	
	enemies[4]->m_active = 1;
	enemies[8]->m_active = 1;

	//Esto asigna las llaves a enemigos aleatorios en cada piso
	srand(time(NULL));
	int random1 = rand() % (11 - 10);
	int random2 = rand() % (11 - 6);
	enemies[random1]->m_key = 1;
	enemies[random2 + 2]->m_key = 1;
}

//Salvar partida ver 1.0
void SaveGame(Player &hero, vector <short>& data)
{
	ifstream* reader = new ifstream;
	ofstream* writer = new ofstream;
	int value;
	reader->open("Default.txt");
	while (!reader->eof())
	{
		*reader >> value;
		data.push_back(value);
	}
	hero.m_position = data[0];
	hero.m_alive = data[1];
	hero.m_health = data[2];
	hero.m_maxHeatlh = data[3];
	hero.m_magic = data[4];
	hero.m_maxMagic = data[5];
	reader->close();
	return;
}

//Llama a las otras funciones
void Caller(Player hero, vector <string> paths, vector <string> words, vector <Room*> map, vector <Enemy*> enemies, int MAP[16][16])
{
	string phrase;
	cout << map[hero.m_position]->m_description << endl;
	while (true)
	{
		Descriptions(hero, enemies);
		hero.Expansion(hero.m_position, paths, MAP, rooms);
		getline(cin, phrase);
		Split(words, phrase, ' ');
		if (words.size() > 0)
		{
			if (words[0] == "ir")
			{
				hero.Movement(hero, words, paths, MAP, rooms, map);
			}
			else if (words[0] == "subir" || words[0] == "bajar")
			{
				hero.Stairs(hero, words, rooms);
			}
			else if (words[0] == "atacar")
			{
				hero.Attack(words, enemyNames, hero, enemies, map);
			}
			else
			{
				cout << "Operacion invalida" << endl;
			}
		}
		else
		{
			cout << "No introduciste ninguna accion" << endl;
		}
		enemies[0]->Response(words, enemyNames, hero, enemies);
		words.clear();
		paths.clear();
	}
	return;
}

int main()
{
	vector <string> paths, words;
	vector <Room*> map;
	vector <Enemy*> enemies;
	vector <short> data;
	Player hero(0, 1, 100, 100, 0, 100, 5);
	NewGame(map, enemies);
	Caller(hero, paths, words, map, enemies, MAP);
	cin.ignore();
	cin.get();
	return 0;
}

//Uso correcto de los Try/Catch en multiples casos (como loops)