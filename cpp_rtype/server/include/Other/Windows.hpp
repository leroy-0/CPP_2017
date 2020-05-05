//
// Created by Sébastien on 20/01/2018.
//

#ifndef R_TYPE_WINDOWS_HPP
#define R_TYPE_WINDOWS_HPP

#include <string>
#include "Other/ILoader.hpp"
#include "../../IA/IAi.hpp"

class Windows : public ILoader {
public:
	Windows() = default;
	virtual ~Windows() = default;

	IAi *loadSharedLibrary(const std::string &);
};


#endif //R_TYPE_WINDOWS_HPP
