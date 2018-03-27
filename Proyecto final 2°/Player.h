#include "Headers.h"

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

	Player(int position, bool alive, int health, int maxHealth, int magic, int maxMagic);
	~Player();
};

