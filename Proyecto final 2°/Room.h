#pragma once
#include "Headers.h"

class Room
{
public:
	string m_description;
	int m_position;
	bool m_locked;
	bool m_manaPot;
	bool m_healthPot;

	Room();
	~Room();
};
