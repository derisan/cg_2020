// ------------------------------------------------------------
// 2016180007 ±è¸í±Ô
// warming2.cpp
// Ctrl + M, L to expand all
// ------------------------------------------------------------

#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include <cctype>

void readFile(const std::string& fileName);
void split(std::string str, char delimiter, int& countWord, int& countNum);

int main()
{
	std::string fileName;
	std::cout << "Input data file name: ";
	std::getline(std::cin, fileName);
	readFile(fileName);
	return 0;
}

// Read text from file
void readFile(const std::string& fileName)
{
	int countWord = 0;
	int countNum = 0;

	std::fstream file(fileName);
	if (file.is_open())
	{
		std::string line;
		std::vector<std::string> contents;

		// split with '\n'
		while (std::getline(file, line, '\n'))
			contents.emplace_back(line);

		for (auto& con : contents)
			split(con, ' ', countWord, countNum);
	}
	else
	{
		std::cout << "Failed to load file " << fileName << std::endl;
		return;
	}

	std::cout << "Word count>> " << countWord << std::endl;
	std::cout << "Number count>> " << countNum << std::endl;
}

// split with delimiter and store number of words in each integer
void split(std::string str, char delimiter, int& countWord, int& countNum)
{
	std::vector<std::string> v;
	std::stringstream sstream(str);
	std::string temp;

	int countTotal = countWord + countNum;

	while (std::getline(sstream, temp, delimiter))
		v.emplace_back(temp);

	for (const auto& str : v)
	{
		for(const auto ch : str)
			if (std::isdigit(ch))
			{
				++countNum;
				break;
			}
		++countTotal;
	}
	countWord = countTotal - countNum;
}