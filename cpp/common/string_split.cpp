
#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <iterator>


void splitByChar(const std::string& str, std::vector<std::string>& container, char delim = ' ')
{
	std::istringstream stream(str);
	std::string token;
	while (std::getline(stream, token, delim))
	{
		// TODO: store the token
		container.push_back(token);
	}
}

void splitByString(const std::string& str, std::vector<std::string>& container, const std::string& delims = " ")
{
	std::size_t length = delims.size();
	if (delims.empty() == true)
		return; // invalid sub string

	std::size_t current, previous = 0;
	current = str.find(delims);
	while (current != std::string::npos)
	{
		std::string substr = str.substr(previous, current - previous);
		// TODO: trim the null string and store the token
		if (previous < current)
			container.push_back(substr);
		previous = current + length;
		current = str.find(delims, previous);
	}

	// TODO: trim the null string and store the last token
	if (previous < current)
		container.push_back(str.substr(previous, current - previous));
}


//void main()
//{
//	char str[] = "the quick brown fox jumps over the lazy dog";
//
//	std::vector<std::string> words1;
//	splitByChar(str, words1, ' ');
//	std::copy(words1.begin(), words1.end(),
//		std::ostream_iterator<std::string>(std::cout, "\n"));
//
//	std::vector<std::string> words2;
//	splitByString(str, words2, "the");
//	std::copy(words2.begin(), words2.end(),
//		std::ostream_iterator<std::string>(std::cout, "\n"));
//
//	system("pause");
//}