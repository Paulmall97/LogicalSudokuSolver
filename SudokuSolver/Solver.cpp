#include "Solver.h"

#include "Group.h"

Solver::Solver(const Grid& grid) : m_grid{ grid } {

	//generate constraints for rows, columns and boxes

	for (uint8_t i = 1; i <= 9; i++) {
		m_constraints.push_back(std::make_shared<Group>(grid.getRow(i)));
	}

	for (uint8_t i = 1; i <= 9; i++) {
		m_constraints.push_back(std::make_shared<Group>(grid.getColumn(i)));
	}

	for (uint8_t i = 1; i <= 9; i++) {
		m_constraints.push_back(std::make_shared<Group>(grid.getBox(i)));
	}

}

void Solver::run() {

	int updated = true;
	while (updated) {
		updated = false;
		for (auto constraint : m_constraints) {
			if (constraint->evaluate()) {
				updated = true;
			}
		}
	}
}