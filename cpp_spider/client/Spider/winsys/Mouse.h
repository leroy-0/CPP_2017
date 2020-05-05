#pragma once

#include "IRecorder.h"

#include <vector>

class Mouse : public IRecorder
{
public:
	Mouse();
	virtual ~Mouse();

public:
	const std::string 		getCursorPos() const;
	const std::string 		getClicks() const;
	const std::string 		manageMoves();
	const std::string 		readMouse();

	void					read();
	void					write(const std::string & filename);

private:
	const std::vector<std::string>	clickNames { "L(1)", "R(1)", "Cancel", "M(1)", "X(1)", "X(2)" };
	std::string						record;
	time_t							start;
	int								lastPos[2];
};