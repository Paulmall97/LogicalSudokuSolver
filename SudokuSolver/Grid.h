#pragma once

#include <cstdint>
#include <vector>
#include <memory>
#include <string>

class Cell;

class Grid
{

public:

	Grid();

	std::shared_ptr<Cell> getCell(const uint8_t row, const uint8_t column) const;
	
	//these functions follow "sudoku" conventions for number. 1-9, left to right, top to bottom
	std::vector<std::shared_ptr<Cell>> getRow(const uint8_t num) const;
	std::vector<std::shared_ptr<Cell>> getColumn(const uint8_t num) const;
	std::vector<std::shared_ptr<Cell>> getBox(const uint8_t num) const;

	void printGrid() const;
	const std::string toString() const;

private:

	std::vector<std::vector<std::shared_ptr<Cell>>> m_cells;

	std::vector<std::shared_ptr<Cell>> getBoxCells(uint8_t x, uint8_t y) const;

};

