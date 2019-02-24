
#include <iostream>
#include <string>
#include <algorithm>
#include <cstring>
#include <locale>


bool isEqual(const std::string& str1, const std::string& str2)
{
	if (str1.size() != str2.size())
		return false;

	for (std::size_t n = 0; n < str1.size(); n++)
	{
		if (str1[n] != str2[n])
			return false;
	}

	return true;
}

void lower(std::string& str)
{
	std::locale loc;
	// TODO: lower
	for (std::size_t n = 0; n < str.size(); n++)
		str[n] = std::tolower(str[n], loc);
}

void upper(std::string& str)
{
	std::locale loc;
	// TODO: upper
	for (std::size_t n = 0; n < str.size(); n++)
		str[n] = std::toupper(str[n], loc);
}

void ltrim(std::string& str, const std::string& chars = "\t\n\v\f\r ")
{
	//str.erase(0, str.find_first_not_of(chars));
	std::size_t pos = str.find_first_not_of(chars);
	str = str.substr(pos, std::string::npos);
}

void rtrim(std::string& str, const std::string& chars = "\t\n\v\f\r ")
{
	//str.erase(0, str.find_first_not_of(chars));
	std::size_t pos = str.find_last_not_of(chars);
	str = str.substr(0, pos+1);
}



//void main()
//{
//	//
//	std::string str1("i have a cat"), str2("I have a cat");
//	std::cout << isEqual(str1, str2) << std::endl;
//
//	//
//	lower(str1);
//	std::cout << str1 << std::endl;
//	upper(str2);
//	std::cout << str2 << std::endl;
//
//	// 
//	lower(str1);
//	lower(str2);
//	std::cout << isEqual(str1, str2) << std::endl;
//
//	//
//	std::string str("the title");
//	ltrim(str);
//	rtrim(str);
//	std::cout << str << std::endl;
//
//	system("pause");
//}