#include "Headers.h"
#include "Player.h"
#include "Room.h"
#include "Enemy.h"

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

string rooms[16] = {
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

string enemyNames[5] = {
	"gremlin",
	"goblin",
	"orco",
	"troll",
	"dragon"
};

//Busca las posibles expansiones y se las notifica al usuario
void Expansion(int position, vector <string>& paths)
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
void Movement(Player &hero, vector <string> words, vector <string> paths)
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
	}
	else
	{
		cout << "No es posible ir a " << words[1] << endl;
	}
	return;
};

//Subir y bajar escaleras
void Stairs(Player &hero, vector <string> words)
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

//Llena el vector que almacena los cuartos y enemigos
void NewGame(vector <Room*>& map, vector <Enemy*>& enemies)
{
	//Esto crea un vector de todos mis cuartos y les asigna los valores a sus miembros
	Room* unit = new Room;
	for (int i = 0; i < 16; i++)
	{
		map.push_back(unit);
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

//Llama a las otras funciones
void Caller(Player hero, vector <string> paths, vector <string> words, vector <Room*> map, vector <Enemy*> enemies)
{
	string phrase;
	while (true)
	{
		Expansion(hero.m_position, paths);

		//pequeña prueba para comprobar que los datos almacenados en el mapa son correctos
		for (int i = 0; i < enemies.size(); i++)
		{
			if (enemies[i]->m_key == 1)
			{
				cout << "La llave se encuentra en " << rooms[enemies[i]->m_position] << "..." << " la tiene un "  << 
				enemyNames[enemies[i]->m_name] << endl << endl;
			}
		}

		getline(cin, phrase);
		Split(words, phrase, ' ');
		if (words.size() > 0)
		{
			if (words[0] == "ir")
			{
				Movement(hero, words, paths);
			}
			else if (words[0] == "subir" || words[0] == "bajar")
			{
				Stairs(hero, words);
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
		words.clear();
		paths.clear();
	}
	return;
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

int main()
{
	vector <string> paths, words;
	vector <Room*> map;
	vector <Enemy*> enemies;
	vector <short> data;
	Player hero(0, 1, 100, 100, 0, 100);
	NewGame(map, enemies);
	Caller(hero, paths, words, map, enemies);

	cin.ignore();
	cin.get();
	return 0;
}

//Uso correcto de los Try/Catch en multiples casos (como loops)