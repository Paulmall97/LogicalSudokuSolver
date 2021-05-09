#pragma once
#include <cstdint>
#include <set>

//class to represent a single sudoku cell
//a value of 0 represents a cell with no value, since sudoku can only contain the digits 1-9
class Cell
{

public:

	Cell(const uint8_t value = 0);
	Cell(const std::set<uint8_t> candidates);

	uint8_t getValue() const;
	void setValue(const uint8_t value);
	
	const std::set<uint8_t>& getCandidates() const;

	//returns true if a change occured to the candiate list, false otherwise
	bool addCandidate(const uint8_t value);
	//returns true if a change occured to the candiate list, false otherwise
	bool removeCandidate(const uint8_t value);


private:

	void setCandidates(const std::set<uint8_t>& candidates);

	uint8_t m_value;
	std::set<uint8_t> m_candidates;

};

