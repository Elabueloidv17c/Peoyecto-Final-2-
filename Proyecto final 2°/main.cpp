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
{ 1,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0 },
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
{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 }
};

vector <short*> data1;
vector <string> data2;

//Describe los enemigos de los cuartos
void Descriptions(Player hero, vector <Enemy*> enemies)
{
	switch (hero.m_position)
	{
	case 1:
		if (enemies[0]->m_alive == 1 && enemies[0]->m_active == 0)
		{
			cout << "Hay un " << enemyNames[enemies[0]->m_name] << " en la parte trasera, esta rematando al ultimo sobreviviente" << endl;
		}
		break;
	case 4:
		if (enemies[1]->m_alive == 1 && enemies[1]->m_active == 0)
		{
			cout << "Hay un " << enemyNames[enemies[1]->m_name]  << " sentado en un sillon, esta jugando con un dedo humano" << endl;
		}
		break;
	case 7:
		if (enemies[2]->m_alive == 1 && enemies[2]->m_active == 0)
		{
			cout << "Hay un " << enemyNames[enemies[2]->m_name] << " degustando comida podrida de un sarten" << endl;
		}
		break;
	case 8:
		if (enemies[3]->m_alive == 1 && enemies[3]->m_active == 0)
		{
			cout << "Hay un " << enemyNames[enemies[3]->m_name] << " recostado en la cama principal" << endl;
		}
		break;
	case 10:
		if (enemies[4]->m_alive == 1 && enemies[4]->m_active == 0)
		{
			cout << "Justo al centro hay un " << enemyNames[enemies[4]->m_name] << " con armadura pesada levantando los brazos y gritando, cuando te ve se lanza sobre ti" << endl;
		}
		break;
	case 11:
		if (enemies[5]->m_alive == 1 && enemies[5]->m_active == 0)
		{
			cout << "Un " << enemyNames[enemies[5]->m_name] << " borracho lanza su tarro de carveza contra la pared y te grita" << endl;
		}
		break;
	case 12:
		if (enemies[6]->m_alive == 1 && enemies[6]->m_active == 0)
		{
			cout << "En la oscuridad alcanzas a ver los ojos brillantes de un " << enemyNames[enemies[6]->m_name] << endl;
		}
		break;
	case 13:
		if (enemies[7]->m_alive == 1 && enemies[7]->m_active == 0)
		{
			cout << "Puedes ver a un " << enemyNames[enemies[7]->m_name] << " buscando su mazo entre las armas" << endl;
		}
		break;
	case 15:
		if (enemies[8]->m_alive == 1 && enemies[8]->m_active == 0)
		{
			cout << "El " << enemyNames[enemies[8]->m_name] << " ruge y el castillo tiembla, lanza un aliento de fuego sobre ti" << endl;
		}
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

//Borra el elemento usado del inventario
void Eraser(string word, vector <string> &inventory)
{
	for (int i = 0; i < inventory.size(); i++)
	{
		if (inventory[i] == word)
		{
			inventory.erase(inventory.begin() + i);
			return;
		}
	}
	return;
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
		map[i]->m_key = 0;
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
	map[0]->m_healthPot = 1;
	map[9]->m_healthPot = 1;
	map[14]->m_healthPot = 1;

	//Esto crea un vector con los enemigos
	for (int i = 0; i < 9; i++)
	{
		enemies.push_back(new Enemy ());
	}

	//Aqui le doy valor a todos sus miembros
	enemies[0]->m_position = 1;
	enemies[0]->m_name = 0;
	enemies[0]->m_attack = 2;
	enemies[0]->m_health = 20;

	enemies[1]->m_position = 4;
	enemies[1]->m_name = 1;
	enemies[1]->m_attack = 4;
	enemies[1]->m_health = 40;

	enemies[2]->m_position = 7;
	enemies[2]->m_name = 1;
	enemies[2]->m_attack = 4;
	enemies[2]->m_health = 40;

	enemies[3]->m_position = 8;
	enemies[3]->m_name = 2;
	enemies[3]->m_attack = 6;
	enemies[3]->m_health = 60;

	enemies[4]->m_position = 10;
	enemies[4]->m_name = 3;
	enemies[4]->m_attack = 8;
	enemies[4]->m_health = 80;

	enemies[5]->m_position = 11;
	enemies[5]->m_name = 2;
	enemies[5]->m_attack = 6;
	enemies[5]->m_health = 60;

	enemies[6]->m_position = 12;
	enemies[6]->m_name = 1;
	enemies[6]->m_attack = 4;
	enemies[6]->m_health = 40;

	enemies[7]->m_position = 13;
	enemies[7]->m_name = 2;
	enemies[7]->m_attack = 6;
	enemies[7]->m_health = 60;

	enemies[8]->m_position = 15;
	enemies[8]->m_name = 4;
	enemies[8]->m_attack = 10;
	enemies[8]->m_health = 100;

	for (int i = 0; i < enemies.size(); i++)
	{
		enemies[i]->m_alive = 1;
		enemies[i]->m_active = 0;
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

//Salvar partida
void SaveGame(vector <string> words, Player hero, vector <Room*> map, vector <Enemy*> enemies)
{
	if (words[1] == "partida")
	{
		ofstream* writer = new ofstream;
		string name;
		cout << "Con que nombre quieres guardar tu partida?" << endl;
		cin >> name;
		writer->open(name + ".txt");
		//jugador
		*writer << hero.m_alive << endl;
		*writer << hero.m_attack << endl;
		*writer << hero.m_health << endl;
		*writer << hero.m_magic << endl;
		*writer << hero.m_magicAttack << endl;
		*writer << hero.m_maxHeatlh << endl;
		*writer << hero.m_maxMagic << endl;
		*writer << hero.m_position << endl;

		//Habitaciones
		for (int i = 0; i < map.size(); i++)
		{
			*writer << map[i]->m_position << endl;
		}

		for (int i = 0; i < map.size(); i++)
		{
			*writer << map[i]->m_healthPot << endl;
		}

		for (int i = 0; i < map.size(); i++)
		{
			*writer << map[i]->m_manaPot << endl;
		}

		for (int i = 0; i < map.size(); i++)
		{
			*writer << map[i]->m_key << endl;
		}

		for (int i = 0; i < map.size(); i++)
		{
			*writer << map[i]->m_locked << endl;
		}

		//Enemigos
		for (int i = 0; i < enemies.size(); i++)
		{
			*writer << enemies[i]->m_active << endl;
		}

		for (int i = 0; i < enemies.size(); i++)
		{
			*writer << enemies[i]->m_alive << endl;
		}

		for (int i = 0; i < enemies.size(); i++)
		{
			*writer << enemies[i]->m_attack << endl;
		}

		for (int i = 0; i < enemies.size(); i++)
		{
			*writer << enemies[i]->m_health << endl;
		}

		for (int i = 0; i < enemies.size(); i++)
		{
			*writer << enemies[i]->m_key << endl;
		}

		for (int i = 0; i < enemies.size(); i++)
		{
			*writer << enemies[i]->m_name << endl;
		}

		for (int i = 0; i < enemies.size(); i++)
		{
			*writer << enemies[i]->m_position << endl;
		}

		writer->close();
		delete(writer);

		ofstream* text = new ofstream;
		text->open(name + "2.txt");

		//Inventario
		for (int i = 0; i < hero.m_inventory.size(); i++)
		{
			*text << hero.m_inventory[i] << endl;
		}

		text->close();
		delete(text);
		cout << "Partida salvada satisfactoriamente" << endl;
	}
	else
	{
		cout << "Para salvar la partida debes introducir el comando 'Salvar partida'" << endl;
	}
	cin.ignore();
	return;
}

//Tutorial
void Help()
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
	cout << "Cargar: Esta accion sirve para cargar una partida guardada y continuar jugando desde ahi, por ejemplo:" << endl;
	cout << "    -Cargar partida" << endl << endl;
	cout << "Puedes usar mayusculas o minusculas a tu gusto, el juego reconocera las palabras de todos modos" << endl << endl;
	cout << "Nota: Si quieres volver a ver este menu, introduce el comando 'Ver ayuda'" << endl;
}

//Cargar partida
void LoadGame(Player& hero, vector <short*> &data1, vector <string> &data2, vector <Room*> &map, vector <Enemy*> &enemies)
{
	string line;
	ifstream* reader = new ifstream;
	string name;
	cout << "Cual es el nombre de tu partida guardada?" << endl;

	while (true)
	{
		cin >> name;
		reader->open(name + ".txt");
		if (reader->fail())
		{
			if (name == "n")
			{
				cout << "Se ha cargado una nueva partida" << endl << endl;
				cout << "------------------------------------------------------------------" << endl;
				Help();
				cout << map[0]->m_description << endl;
				return;
			}
			cout << "No existe ninguna partida con ese nombre, intentalo de nuevo" << endl;
			cout << "Si quieres iniciar una nueva partida presiona la tecla 'n' y luego presiona enter" << endl;
			cin.ignore();
		}
		else
		{
			break;
		}
	}

	while (!reader->eof())
	{
		short* content = new short;
		*reader >> *content;
		data1.push_back(content);
	}

	reader->close();
	delete(reader);

	ifstream* textReader = new ifstream;
	textReader->open(name + "2.txt");

	while (!textReader->eof())
	{
		getline(*textReader, line);
		data2.push_back(line);
	}

	textReader->close();
	delete(textReader);

	hero.m_alive = *data1[0];
	hero.m_attack = *data1[1];
	hero.m_health = *data1[2];
	hero.m_magic = *data1[3];
	hero.m_magicAttack = *data1[4];
	hero.m_maxHeatlh = *data1[5];
	hero.m_maxMagic = *data1[6];
	hero.m_position = *data1[7];
	
	short index = 8;

	//Habitaciones
	for (int i = 0; i < 16; i++)
	{
		map[i]->m_position = *data1[index];
		index++;
	}

	for (int i = 0; i < 16; i++)
	{
		map[i]->m_healthPot = *data1[index];
		index++;
	}

	for (int i = 0; i < 16; i++)
	{
		map[i]->m_manaPot = *data1[index];
		index++;
	}

	for (int i = 0; i < 16; i++)
	{
		map[i]->m_key = *data1[index];
		index++;
	}

	for (int i = 0; i < 16; i++)
	{
		map[i]->m_locked = *data1[index];
		index++;
	}

	//Enemigos
	for (int i = 0; i < 9; i++)
	{
		enemies[i]->m_active = *data1[index];
		index++;
	}

	for (int i = 0; i < 9; i++)
	{
		enemies[i]->m_alive = *data1[index];
		index++;
	}

	for (int i = 0; i < 9; i++)
	{
		enemies[i]->m_attack = *data1[index];
		index++;
	}

	for (int i = 0; i < 9; i++)
	{
		enemies[i]->m_health = *data1[index];
		index++;
	}

	for (int i = 0; i < 9; i++)
	{
		enemies[i]->m_key = *data1[index];
		index++;
	}

	for (int i = 0; i < 9; i++)
	{
		enemies[i]->m_name = *data1[index];
		index++;
	}

	for (int i = 0; i < 9; i++)
	{
		enemies[i]->m_position = *data1[index];
		index++;
	}
	
	//Inventario
	if (data2.size() > 0)
	{
		for (int i = 0; i < data2.size(); i++)
		{
			if (i < data2.size() - 1)
			{
				hero.m_inventory.push_back(data2[i]);
			}
		}
	}

	cout << "Partida cargada satisfactoriamente" << endl << endl;
	cout << "-----------------------------------------------------------------------" << endl;
	cout << "Bienvenido de nuevo a la aventura!" << endl;
	cout << "-----------------------------------------------------------------------" << endl;

	//Liberar memoria
	for (int i = 0; i < data1.size(); i++)
	{
		delete(data1[i]);
	}
	data1.clear();
	data2.clear();

	return;
}

//Introduccion
void Intro()
{
	cout << "Tu pueblo lleva decadas sufriendo los ataques de un castillo infestado de monstruos." << endl;
	cout << "Los guerreros del pueblo habian logrado defender su hogar hasta de los mas grandes orcos." << endl;
	cout << "Pero esta ultima vez las cosas fueron diferentes... esta vez tu pueblo fue casi aniquilado." << endl;
	cout << "Un gigantezco dragon lidero el ataque y mucha gente murio..." << endl << endl;
	cout << "La rabia se ha apoderado de ti y solo quieres terminar con esta pesadilla" << endl;
	cout << "Tomas tus mejores armas y tu libro de maldiciones." << endl;
	cout << "Es hora de emprender un viaje para terminar con esto de una vez por todas." << endl;
	cout << "Tu mision es eliminar al dragon que lidera los ataques del castillo." << endl;
	cout << "No importa lo que cueste, no saldras de ahi sin haber cumplido tu mision." << endl;
	cout << "Estas cansado de tanta matanza, ahora llevaras la pesadilla hasta ellos..." << endl << endl;
}

//Llama a las otras funciones
void Caller(Player hero, vector <string> paths, vector <string> words, vector <Room*> map, vector <Enemy*> enemies, int MAP[16][16])
{
	string phrase;
	cin.ignore();
	cin.get();
	while (true)
	{
		cout << "----------------------------------------------------------------------------------------------------------------";
		if (hero.m_alive == 0)
		{
			cout << endl << "Has pedido, la partida termino, suerte para la proxima..." << endl;
			break;
		}
		if (enemies[8]->m_alive == 0)
		{
			cout << endl << "Felicidades! has superado el juego y liberado a tu pueblo" << endl;
			cout << "Muchas gracias por jugar, espero que te haya gustado y que vuelvas a jugar pronto" << endl;
			break;
		}
		hero.HUD(hero);
		cout << "----------------------------------------------------------------------------------------------------------------";
		hero.Expansion(hero.m_position, paths, MAP, rooms);
		getline(cin, phrase);
		cout << endl;
		Split(words, phrase, ' ');
		if (words.size() == 2)
		{
			if (words[0] == "ir")
			{
				hero.Movement(hero, words, paths, MAP, rooms, map, enemies);
			}
			else if (words[0] == "subir" || words[0] == "bajar")
			{
				hero.Stairs(hero, words, rooms, map);
			}
			else if (words[0] == "atacar")
			{
				hero.Attack(words, enemyNames, hero, enemies, map);
			}
			else if (words[0] == "ver")
			{
				hero.See(hero, words);
			}
			else if (words[0] == "tomar")
			{
				hero.Take(words, hero, map, enemies);
			}
			else if (words[0] == "usar")
			{
				hero.Use(words, hero, map);
			}
			else if (words[0] == "maldecir")
			{
				hero.Spell(words, enemyNames, hero, enemies, map);
			}
			else if (words[0] == "explorar")
			{
				hero.Explore(words, map, rooms);
			}
			else if (words[0] == "salvar")
			{
				SaveGame(words, hero, map, enemies);
			}
			else if (words[0] == "cerrar")
			{
				hero.Exit(words, hero);
			}
			else
			{
				cout << "Comando invalido" << endl;
			}
		}
		else if (words.size() == 0)
		{
			cout << "No introdujiste ninguna accion" << endl;
		}
		else
		{
			cout << "Debes introducir comandos de dos palabras" << endl;
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
	Player hero(0, 1, 100, 100, 0, 80, 10, 30);

	NewGame(map, enemies);
	Intro();
	cin.get();

	cout << "Bienvenido a Knight's Revenge!" << endl << endl;
	cout << "Que quieres hacer?" << endl << "(Teclea el numero correspondiente a la opcion que desees)" << endl;
	cout << "1.- Nueva partida" << endl;
	cout << "2.- Cargar partida" << endl;
	int startup;

	while (true)
	{
		cin >> startup;
		cout << endl;
		if (startup == 1)
		{
			Help();
			cout << map[0]->m_description << endl;
			break;
		}
		if (startup == 2)
		{
			LoadGame(hero, data1, data2, map, enemies);
			break;
		}
		else
		{
			cout << "Accion invalida, intentalo de nuevo" << endl;
		}
	}

	Caller(hero, paths, words, map, enemies, MAP);

	for (int i = 0; i < map.size(); i++)
	{
		delete(map[i]);
	}
	for (int i = 0; i < enemies.size(); i++)
	{
		delete(enemies[i]);
	}
	cin.ignore();
	cin.get();
	return 0;
}

//Dudas:
//	Uso correcto de los Try/Catch en multiples casos (como loops)
//  Fuga de memoria en los punteros a los objetos de las clases

//Pendientes:
//    Uso de sobrecargas
//	  Mapa en txt