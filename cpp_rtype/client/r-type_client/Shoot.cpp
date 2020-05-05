#include "Shoot.h"

Shoot::Shoot(const std::string & name)
	: Sprite(name)
{
	this->damage = 1;
}

Shoot::~Shoot()
{

}