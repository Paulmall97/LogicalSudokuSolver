#pragma once

#include <vector>

class Constraint {


public:

	Constraint() {};
	virtual ~Constraint() {};

	//returns if any updates were made to any cell or constraint within this constraint
	virtual bool evaluate() = 0;

};