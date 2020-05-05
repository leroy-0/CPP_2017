#pragma once

#include "Sprite.h"

class Shoot : public Sprite
{
public:
	Shoot(const std::string & name);
	virtual ~Shoot();

private:
	int damage;
};