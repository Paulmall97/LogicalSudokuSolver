#include "SudokuBuilder.h"
#include "Grid.h"
#include "Cell.h"
#include "BoundsCheck.h"

#include "assert.h"

Grid SudokuBuilder::buildSudoku(const std::string& sudoku) {

	if (sudoku.size() != 9 * 9) {
		assert(false);
	}

	Grid grid;
	uint8_t row = 0;
	uint8_t column = 0;
	for (const char value : sudoku) {
		if (value != '.') {
			//ascii digits begin at '0', so minus that to get number
			uint8_t number = value - '0';
			assert(outOfBoundsValue(number));
;			grid.getCell(row, column)->setValue(number);
		}
		column++;
		if (column >= 9) {
			row++;
			column = 0;
		}
	}

	return grid;
}