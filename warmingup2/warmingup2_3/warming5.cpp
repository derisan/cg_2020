// ---------------------------------
// 2016180007 김명규
// 5. 경로 만들기
// ---------------------------------

#include <iostream>
#include <random>
#include <vector>
#include <cstdlib>

class Random
{
public:
	static void init();
	static int getInt(int min, int max);
private:
	static std::mt19937 generator;
};

void Random::init()
{
	std::random_device rd;
	generator.seed(rd());
}

int Random::getInt(int min, int max)
{
	std::uniform_int_distribution<int> uid(min, max);
	return uid(generator);
}

std::mt19937 Random::generator;


class Maze
{
	enum
	{
		Unvisited,
		Wall,
		Path,
		Blocked
	};
public:
	Maze();
	int search(int x, int y);
	void print() const;
	void reset();

	static const int Size = 50;
private:
	int maze[Size][Size];
};

Maze::Maze()
	: maze{ 0 }
{
}

void Maze::print() const
{
	for (int i = 0; i < Size; ++i)
	{
		for (int j = 0; j < Size; ++j)
		{
			if (maze[i][j] == Path)
				std::cout << "0 ";
			else
				std::cout << "1 ";
		}
		std::cout << std::endl;
	}
}

void Maze::reset()
{
	for (int i = 0; i < Size; ++i)
		for (int j = 0; j < Size; ++j)
			maze[i][j] = 0;
}

int Maze::search(int x, int y)
{
	if (x < 0 || y < 0 || x >= Size || y >= Size)
		return 0;
	else if (maze[x][y] != Unvisited)
		return 0;
	else if (x == Size - 1 && y == Size - 1)
	{
		maze[x][y] = Path;
		return 1;
	}
	else
	{
		maze[x][y] = Path;
		int dir = Random::getInt(0, 1);
		switch (dir)
		{
			case 0:
				if (search(x + 1, y) || search(x, y - 1) || search(x - 1, y) || search(x, y + 1))
					return 1;
				break;
			case 1:
				if (search(x, y + 1) || search(x - 1, y) || search(x, y - 1) ||  search(x + 1, y))
					return 1;
				break;
		}
	}
	maze[x][y] = Blocked;
	return 0;
}

class TestProgram
{
public:
	TestProgram();
	void run();
	void print() const;

private:
	void userInput();
	void execute();

	bool mShouldClose;
	char mInput;
	Maze mMaze;
};

TestProgram::TestProgram()
	: mShouldClose(false),
	mInput(0)
{
}

void TestProgram::run()
{
	while (!mShouldClose)
	{
		userInput();
		execute();
	}
}

void TestProgram::userInput()
{
	int check = false;
	std::vector<char> inputPool{ 'r', 'R', 'q', 'Q' };

	while (!check)
	{
		std::cout << "Command(press 'r' to search) >>> ";
		std::cin >> mInput;

		if (std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore(256, '\n');
			std::cout << "Unknown input, please retry." << std::endl;
			continue;
		}

		auto iter = std::find(inputPool.begin(), inputPool.end(), mInput);
		if (iter != inputPool.end())
			check = true;
		else
			std::cout << "No option with " << mInput << std::endl;
		std::cin.ignore(256, '\n');
	}
}

void TestProgram::execute()
{
	switch (mInput)
	{
		case 'r': case 'R':
			system("cls");
			mMaze.reset();
			mMaze.search(0, 0);
			mMaze.print();
			break;
		case 'q': case 'Q':
			mShouldClose = true;
			break;
	}
}

int main()
{
	Random::init();

	TestProgram tp;
	tp.run();
	return 0;
}
