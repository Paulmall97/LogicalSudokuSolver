#include "Group.h"

#include "Constraint.h"
#include "Cell.h"

#include <set>
#include <algorithm>
#include <iterator>

Group::Group(const std::vector<std::shared_ptr<Cell>>& cells, const std::set<uint8_t>& values) : 
	Constraint(), 
	m_cells{ cells }, 
	m_availableValues{values}
{
	//empty
}

bool Group::evaluate() {

	bool updated = false;

	std::set<uint8_t> seenValues;
	std::set<std::shared_ptr<Cell>> unsolvedCells;
	for (const auto cell : m_cells) {
		auto value = cell->getValue();
		if (value) {
			seenValues.insert(value);
		}else{
			unsolvedCells.insert(cell);
		}
	}

	for (const auto cell : unsolvedCells) {
		for (const auto seen : seenValues) {
			if (cell->removeCandidate(seen)) {
				updated = true;
			}

		}
		 
		const auto canditates = cell->getCandidates();
		for (const auto value : canditates) {
			if (m_availableValues.find(value) == m_availableValues.end()) {
				if (cell->removeCandidate(value)) {
					updated = true;
				}
				
			}
		}

		if (cell->getCandidates().size() == 1) {
			cell->setValue(*(cell->getCandidates().begin()));
			updated = true;
		}
	}

	//check for if a value  is ruled out of all cells except 1

	for (const auto value : m_availableValues) {

		int count = 0;
		std::shared_ptr<Cell> last;

		for (const auto cell : unsolvedCells) {
			const auto candidates = cell->getCandidates();
			if (candidates.find(value) != candidates.end()) {
				count++;
				last = cell;
			}
		}

		if (count == 1 && last->getValue() == 0) {
			last->setValue(value);
			updated = true;
		}

	}

	return updated;

}