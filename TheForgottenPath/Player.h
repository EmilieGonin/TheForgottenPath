#pragma once

#include "Entity.h"

using std::pair;

class Player : public Entity
{
public:
	Player();

	pair<int, int> GetPos();

private:

	pair<int, int> m_pos;

};