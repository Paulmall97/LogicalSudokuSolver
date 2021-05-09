#pragma once

#include "Grid.h"

#include "Constraint.h"

class Solver
{

public:
	Solver(const Grid& grid);

	void run();

private:

	const Grid& m_grid;
	std::vector<std::shared_ptr<Constraint>> m_constraints;

};

