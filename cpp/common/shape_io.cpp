
#include <string>
#include <fstream>
#include <sstream>
#include <utility>
#include <vector>
#include <iomanip>


bool loadShapeWithoutCheck(const char* path, std::vector<std::pair<float,float>>& vec)
{
	std::ifstream file(path);
	std::string line;

	if (file.is_open() == false)
		return false;

	// TODO: loop condition
	while (file.eof() == false && std::getline(file, line))
	{
		// string to float
		std::string::size_type sz;
		float x = std::stof(line, &sz);
		float y = std::stof(line.substr(sz));
		// TODO: store the value
		std::pair<float, float> pair(x, y);
		vec.push_back(pair);
	}

	return true;
}

bool loadShapeWithCheck(const char* path, std::vector<std::pair<float, float>>& vec, char delims = ' ')
{
	std::ifstream file(path);

	if (file.is_open() == false)
		return false;

	// TODO: loop condition
	std::string line;
	while (file.eof() == false && std::getline(file, line))
	{
		// split and check delims
		std::size_t pos = line.find_first_of(delims);
		if (pos == std::string::npos)
			return false;
		// check the two if they are numbers
		float x, y;
		std::istringstream first(line.substr(0, pos));
		std::istringstream second(line.substr(pos, std::string::npos));
		if (!(first >> x) || !(second >> y))
			return false;
		// TODO: store the value
		std::pair<float, float> pair(x, y);
		vec.push_back(pair);
	}

	return true;
}

bool dumpShape(const char* path, const std::vector<std::pair<float, float>>& vec, char delims = ' ')
{
	std::ofstream file(path);

	if (file.is_open() == false)
		return false;

	for (std::size_t n = 0; n < vec.size(); n++)
	{
		// TODO: get the value
		float x = vec[n].first;
		float y = vec[n].second;
		// convert to string
		std::ostringstream line;
		// TODO: set the presicion of float
		line << std::fixed << std::setprecision(6);
		// TODO: output format
		line << x << delims << y << '\n';
		file << line.str();
	}

	file.close();
	return true;
}


//void main()
//{
//	// load test
//	std::vector<std::pair<float, float>> vec;
//	loadShapeWithCheck("E:\\Exercise\\c++\\wheel\\wheel\\shape_in.txt", vec);
//
//	// output test
//	dumpShape("E:\\Exercise\\c++\\wheel\\wheel\\shape_out.txt", vec);
//}


