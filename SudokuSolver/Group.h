#pragma once

#include "Constraint.h"

#include <vector>
#include <memory>
#include <set>

class Cell;

//Constraint that enforces every cell to have a unique value
class Group: public Constraint
{

public:
	Group(const std::vector<std::shared_ptr<Cell>>& cells, const std::set<uint8_t>& values = { 1,2,3,4,5,6,7,8,9 });

	virtual bool evaluate() override;

private:

	const std::vector<std::shared_ptr<Cell>> m_cells;
	const std::set<uint8_t> m_availableValues;

};

