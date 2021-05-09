#include "Cell.h"

#include "BoundsCheck.h"

#include <assert.h>

Cell::Cell(const uint8_t value) : 
	m_value{ value }
{
	if (!value) {
		setCandidates({ 1,2,3,4,5,6,7,8,9 });
	}
	else {
		assert(outOfBoundsValue(value));
		setCandidates({ value });
	}
}

Cell::Cell(const std::set<uint8_t> candidates) :
	m_value { 0 },
	m_candidates{ candidates }
{

}

uint8_t Cell::getValue() const{
	return m_value;
}

void Cell::setValue(const uint8_t value) {
	assert(outOfBoundsValue(value));
	m_value = value;
	setCandidates({ value });
}

const std::set<uint8_t>& Cell::getCandidates() const{
	return  m_candidates;
}

bool Cell::addCandidate(const uint8_t candidate) {
	assert(outOfBoundsValue(candidate));
	if (std::find(m_candidates.begin(), m_candidates.end(), candidate) == m_candidates.end()) {
		m_candidates.insert(candidate);
		return true;
	}
	return false;
}

bool Cell::removeCandidate(const uint8_t candidate) {
	assert(outOfBoundsValue(candidate));
	auto it = std::find(m_candidates.begin(), m_candidates.end(), candidate);
	if (it != m_candidates.end()) {
		m_candidates.erase(it);
		return true;
	}
	return false;
}

void Cell::setCandidates(const std::set<uint8_t>& candidates) {
	m_candidates = std::set<uint8_t>(candidates);
}