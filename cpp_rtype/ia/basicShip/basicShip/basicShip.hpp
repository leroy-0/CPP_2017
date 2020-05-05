#pragma once

#ifdef BASICSHIPDLL_EXPORTS
#define BASICSHIPDLL_API __declspec(dllexport) 
#else
#define BASICSHIPDLL_API __declspec(dllimport) 
#endif

#include "IAi.hpp"

	// This class is exported from the MathFuncsDll.dll
	class basicShip : public IAi
	{
	public:
		basicShip(Epibros::SwarmPattern *);
		virtual ~basicShip() {};

		Epibros::SwarmPattern *getSwarmPattern();

		Epibros::SwarmPattern   *pattern;
		static BASICSHIPDLL_API  IAi *getIA();

	};