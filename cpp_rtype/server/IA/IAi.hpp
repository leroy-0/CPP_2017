//
// Created by Sébastien on 20/01/2018.
//

#ifndef R_TYPE_IAI_HPP
#define R_TYPE_IAI_HPP

#include <Rules.hpp>

class IAi {
public:
	IAi() {};
    virtual Epibros::SwarmPattern *getSwarmPattern() {
		return nullptr;
	};

	virtual void        setWaitTime(int) = 0;
};

#endif //R_TYPE_IAI_HPP

