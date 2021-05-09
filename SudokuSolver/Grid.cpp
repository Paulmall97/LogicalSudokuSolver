#include "Grid.h"

#include "Cell.h"

#include <assert.h>
#include <iostream>
#include <sstream>

Grid::Grid() {

	for (int i = 0; i < 9; i++) {
		auto column = std::vector<std::shared_ptr<Cell>>();
		for (int j = 0; j < 9; j++) {
			column.push_back(std::make_shared<Cell>());
		}
		m_cells.push_back(column);
	}

}

std::vector<std::shared_ptr<Cell>> Grid::getRow(const uint8_t num) const {

	assert(num != 0 && num < 10);
	return m_cells[num - 1];

}

std::vector<std::shared_ptr<Cell>> Grid::getColumn(const uint8_t num) const {

	assert(num != 0 && num < 10);

	auto values = std::vector<std::shared_ptr<Cell>>();

	for (const auto row : m_cells) {
		values.push_back(row[num - 1]);
	}

	return values;
}


std::vector<std::shared_ptr<Cell>> Grid::getBoxCells(uint8_t x, uint8_t y) const {
	auto box = std::vector<std::shared_ptr<Cell>>();
	for (uint8_t i = 0; i < 3; i++) {
		for (uint8_t j = 0; j < 3; j++) {
			box.push_back(getCell(x + i, y + j));
		}
	}
	return box;
}


std::vector<std::shared_ptr<Cell>> Grid::getBox(const uint8_t num) const {

	assert(num != 0 && num < 10);

	auto values = std::vector<std::shared_ptr<Cell>>();

	const auto coords = std::vector<std::pair<uint8_t, uint8_t>>({
		{(uint8_t)0, (uint8_t)0}, //1
		{(uint8_t)0, (uint8_t)3}, //2
		{(uint8_t)0, (uint8_t)6}, //3
		{(uint8_t)3, (uint8_t)0}, //4
		{(uint8_t)3, (uint8_t)3}, //5
		{(uint8_t)3, (uint8_t)6}, //6
		{(uint8_t)6, (uint8_t)0}, //7
		{(uint8_t)6, (uint8_t)3}, //8
		{(uint8_t)6, (uint8_t)6}  //9
	});

	return getBoxCells(coords[num - 1].first, coords[num - 1].second);

}


std::shared_ptr<Cell> Grid::getCell(const uint8_t row, const uint8_t column) const{
	assert(row < 9 && column < 9);
	return m_cells.at(row).at(column);
}

void Grid::printGrid() const{

	for (const auto column : m_cells) {
		for (const auto cell : column) {
			const int value = (int)cell->getValue();
			//const std::string outputString = (value) ? value  + "" : "-";

			if (!value) {
				std::cout << "." << " ";
			}
			else {
				std::cout << value << " ";
			}
			
		}
		std::cout << std::endl;
	}

}

const std::string Grid::toString() const {

	std::stringstream solution;
	for (const auto row : m_cells) {
		for (const auto cell : row) {
			auto value = (int)cell->getValue();
			if (value == 0) {
				solution << ".";
			}
			else {
				solution << (int)value;
			}
			
		}
	}
	return solution.str();
}