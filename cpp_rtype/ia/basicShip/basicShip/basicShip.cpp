// basicShip.cpp : définit les fonctions exportées pour l'application DLL.
//

#include <iostream>
#include "basicShip.hpp"


	basicShip::basicShip(Epibros::SwarmPattern *s) : IAi() {
		pattern = s;
	}

	Epibros::SwarmPattern *basicShip::getSwarmPattern() {
		return pattern;
	}

	 IAi *basicShip::getIA()
		{
			std::cout << "In basic ship construction" << std::endl;
			Epibros::SwarmPattern * swarm = new Epibros::SwarmPattern();
			swarm->patternContainer.push_back(new Epibros::Pattern(0, 0));
			swarm->patternContainer.push_back(new Epibros::Pattern(1, -1));
			swarm->patternContainer.push_back(new Epibros::Pattern(2, -2));
			swarm->patternContainer.push_back(new Epibros::Pattern(2, -2));
			swarm->patternContainer.push_back(new Epibros::Pattern(3, 0));
			swarm->nbShip = 10;
			basicShip *_new = new basicShip(swarm);
			return _new;
		}
