#pragma once

#include <string>
#include <functional>

class Test
{

public:

	Test(const std::string& name, std::function<bool()> test);
	Test(const std::string& name, std::function<std::pair<bool, std::string>()> test);

	const bool getResult() { return m_result; };
	const std::string& getName(){ return m_testName; };
	const std::string& getMessage() { return m_message; };

private:

	bool m_result;
	std::string m_message;

	const std::string m_testName;

};

