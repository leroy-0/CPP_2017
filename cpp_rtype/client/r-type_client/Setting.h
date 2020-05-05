#pragma once

#include "Menu.h"

class Setting : public Menu
{
public:
	Setting();
	virtual ~Setting();

	void	start();

private:
	void						save(const std::string & name);
	mod							getChoosen();
	std::vector<sf::Vector2f>	resolutions;

	float						width;
	float						height;
	bool						fullscreen;
	bool						fps;
};