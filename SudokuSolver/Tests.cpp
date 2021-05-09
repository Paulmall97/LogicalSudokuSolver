#include "Tests.h"

#include "Cell.h"
#include "Group.h"

#include <iostream>
#include "SudokuBuilder.h"
#include "Solver.h"

namespace {

	bool validateSudoku(const Grid& grid) {

		auto groups = std::vector<std::vector<std::shared_ptr<Cell>>>();

		for (uint8_t i = 1; i <= 9; i++) {
			groups.push_back(grid.getRow(i));
		}

		for (uint8_t i = 1; i <= 9; i++) {
			groups.push_back(grid.getColumn(i));
		}

		for (uint8_t i = 1; i <= 9; i++) {
			groups.push_back(grid.getBox(i));
		}

		for (const auto group : groups) {
			auto set = std::set<uint8_t>();
			for (const auto cell : group) {
				set.insert(cell->getValue());
			}

			if (set.find((uint8_t)0) != set.end() || set.size() != 9) {
				//if a value was unsolved or we had a duplicate value
				//then solver has failed
				return false;
			}

		}

		return true;
	}


	bool testFullSudoku(const std::string& sudoku, const bool print) {

		SudokuBuilder builder;
		auto grid = builder.buildSudoku(sudoku);
		
		if (print) {
			grid.printGrid();
			std::cout << "------------------------" << std::endl;
		}

		Solver solver(grid);
		solver.run();

		if (print) {
			grid.printGrid();
			std::cout << "------------------------" << std::endl;
		}

		auto gridSolution = grid.toString();
		return validateSudoku(grid);

	}


}

Tests::Tests() {

	m_tests.push_back(Test(
		"9 Group Single Digit Missing", [] {

		
		auto unsolved = std::make_shared<Cell>((uint8_t)0);

		const auto cells = std::vector<std::shared_ptr<Cell>>({
			std::make_shared<Cell>((uint8_t)1),
			std::make_shared<Cell>((uint8_t)2) ,
			std::make_shared<Cell>((uint8_t)3) ,
			std::make_shared<Cell>((uint8_t)4) ,
			std::make_shared<Cell>((uint8_t)5) ,
			std::make_shared<Cell>((uint8_t)6) ,
			std::make_shared<Cell>((uint8_t)7) ,
			std::make_shared<Cell>((uint8_t)8) ,
			unsolved });
		Group group(cells);
		group.evaluate();

		return unsolved->getValue() == 9;
			

		}));
	
	m_tests.push_back(Test(
		"4 Group Single Digit Missing", [] {

		auto unsolved = std::make_shared<Cell>((uint8_t)0);

		const auto cells = std::vector<std::shared_ptr<Cell>>({
			std::make_shared<Cell>((uint8_t)1),
			std::make_shared<Cell>((uint8_t)2) ,
			unsolved ,
			std::make_shared<Cell>((uint8_t)4) });

		Group group(cells, { 1,2,3,4 });
		group.evaluate();

		if (unsolved->getValue() == 3) {
			return std::pair<bool, std::string>(true, "");
		}
		return std::pair<bool, std::string>(false, "Value was " + unsolved->getValue());

		}
	));

	m_tests.push_back(Test(
		"Reduce to 2 Candidates", [] {

			auto unsolved1 = std::make_shared<Cell>((uint8_t)0);
			auto unsolved2 = std::make_shared<Cell>((uint8_t)0);

			const auto cells = std::vector<std::shared_ptr<Cell>>({
				std::make_shared<Cell>((uint8_t)1),
				std::make_shared<Cell>((uint8_t)2) ,
				unsolved1 ,
				unsolved2 });

			Group group(cells, { 1,2,3,4 });
			group.evaluate();

			if (unsolved1->getCandidates() != std::set<uint8_t>({ 3, 4 })
				|| unsolved2->getCandidates() != std::set<uint8_t>({ 3, 4 })) {
				return std::pair<bool, std::string>(false, "Both cells werent 3,4");
			}
			
			unsolved1->setValue(3);

			group.evaluate();

			if (unsolved2->getValue() != 4) {
				return std::pair<bool, std::string>(false , "Cell did not react to other cell in group being set");
			}
			return std::pair<bool, std::string>(true, "");

		}
	));

	m_tests.push_back(Test(
		"Only 1 possability in group", [] {

			const auto unsolved = std::make_shared<Cell>();

			const auto cells = std::vector<std::shared_ptr<Cell>>({
				std::make_shared<Cell>((uint8_t)5),
				unsolved,
				std::make_shared<Cell>((uint8_t)6),
				std::make_shared<Cell>(),
				std::make_shared<Cell>(),
				std::make_shared<Cell>(),
				std::make_shared<Cell>(),
				std::make_shared<Cell>(),
				std::make_shared<Cell>()
				});

			for (int i = 3; i < 9; i++) {
				cells[i]->removeCandidate(1);
			}

			Group group(cells);

			group.evaluate();

			return unsolved->getValue() == 1;

		}
	));

	m_tests.push_back(Test(
		"Very Easy Set", [] {
			const auto sudokus = {
				".4.2859..692..7..88...6.47295.74...3..6..8294.2839..1...46..38558.1.46..2.98.3.4.",
				"..96.21.557.34..6..2...54379.3.57...4.7..6259.8.49.67....72.3967341.9....92.8..41"
			};

			for (const auto sudoku : sudokus) {
				if (!testFullSudoku(sudoku, false)) {
					return false;
				}
			}

			return true;

		}
	));

	m_tests.push_back(Test(
		"Hard Set", [] {
			const auto sudokus = {
				"4.....8.5.3..........7......2.....6.....8.4......1.......6.3.7.5..2.....1.4......",
				"...81.....2........1.9..7...7..25.934.2............5...975.....563.....4......68."
			};

			bool failed = false;
			for (const auto sudoku : sudokus) {
				if (!testFullSudoku(sudoku, true)) {
					failed = true;
				}
			}

			return !failed;

		}
	));

	m_tests.push_back(Test(
		"CTC Set 1", [] {
			const auto sudokus = {
				"7.4..6..9.8..1......3.2.45.........2.56...78.1.........25.3.1......4..6.9..5..3.7",
				"6.5.....7...5..1...4...1..6..4.1..6....462....8..3.2..8..3...2...3..7...5.....7.4"
			};

			bool failed = false;
			for (const auto sudoku : sudokus) {
				if (!testFullSudoku(sudoku, false)) {
					failed = true;
				}
			}

			return !failed;

		}
	));
	
}

bool Tests::runTests() {

	int countSuccess = 0;
	for (auto test : m_tests) {
		const bool success = test.getResult();
		const std::string outputString = (success) ? "Passed" : "Failed";
		std::cout << test.getName() << ": " << outputString << ": " << test.getMessage() << std::endl;
		if (success) {
			countSuccess++;
		}
	}

	std::cout << "Passed " << countSuccess << "/" << m_tests.size() << std::endl;

	return countSuccess == m_tests.size();
}