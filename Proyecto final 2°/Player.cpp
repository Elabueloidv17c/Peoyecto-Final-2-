#include "Player.h"

Player::Player(int position, bool alive, int health, int maxHealth, int magic, int maxMagic)
{
	m_position = position;
	m_alive = alive;
	m_health = health;
	m_maxHeatlh = maxHealth;
	m_magic = magic;
	m_maxMagic = maxMagic;
};

Player::~Player() {};
