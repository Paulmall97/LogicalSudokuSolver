#include "Test.h"

Test::Test(const std::string& name, std::function<bool()> test) : 
	m_testName{ name } 
{

	m_result = test();

}

Test::Test(const std::string& name, std::function<std::pair<bool, std::string>()> test):
	m_testName{ name }
{
	auto result = test();
	m_result = result.first;
	m_message = result.second;
}