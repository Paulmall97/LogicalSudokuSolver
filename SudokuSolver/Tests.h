#pragma once

#include "Test.h"

#include <vector>
#include <string>
#include <functional>

class Tests
{

public:

	Tests();
	bool runTests();

private:

	std::vector<Test> m_tests;

};

