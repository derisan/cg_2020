// ---------------------------------
// 2016180007 김명규
// 6. 움직이는 도형 그리기
// ---------------------------------

#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>

struct Point
{
	int x;
	int y;
};


class Board
{
	enum
	{
		ROW = 30,
		COL = 30
	};
public:
	Board();
	void move(char input);
	void scale(char input);
	void scaleX(char input);
	void scaleY(char input);
	void set();
	void print() const;
	void update();

private:
	void boundcheck();

	char mBoard[ROW][COL];
	Point lt;
	int mWidth;
	int mHeight;
};

Board::Board()
	: lt{ 0, 0 },
	mWidth(0),
	mHeight(0)
{
	for (int i = 0; i < ROW; ++i)
		for (int j = 0; j < COL; ++j)
			mBoard[i][j] = '.';
}

void Board::print() const
{
	for (int i = 0; i < ROW; ++i)
	{
		for (int j = 0; j < COL; ++j)
			std::cout << mBoard[i][j] << " ";
		std::cout << std::endl;
	}
}

void Board::update()
{
	for (int i = 0; i < ROW; ++i)
		for (int j = 0; j < COL; ++j)
		{
			if (lt.y <= j && j <= lt.y + mWidth
				&& lt.x <= i && i <= lt.x + mHeight)
				mBoard[i][j] = '0';
			else
				mBoard[i][j] = '.';
		}
}

void Board::set()
{
	int coords[4];
	std::cout << "Input coord value>>> ";
	for (int i = 0; i < 4; ++i)
		std::cin >> coords[i];

	lt.x = coords[0] - 1;
	lt.y = coords[1] - 1;
	mWidth = coords[3] - coords[1];
	mHeight = coords[2] - coords[0];
}

void Board::move(char input)
{
	switch (input)
	{
		case 'x':
			lt.y += 1;
			break;
		case 'X':
			lt.y -= 1;
			break;
		case 'y':
			lt.x += 1;
			break;
		case 'Y':
			lt.x -= 1;
			break;
	}
	boundcheck();
}

void Board::scale(char input)
{
	switch (input)
	{
		case 's':
			scaleX('j');
			scaleY('l');
			break;

		case 'S':
			scaleX('i');
			scaleY('k');
			break;
	}
}

void Board::scaleX(char input)
{
	switch (input)
	{
		case 'i':
			if (lt.y + mWidth < COL)
				++mWidth;
			else if (lt.y > 1)
			{
				--lt.y;
				++mWidth;
			}
			break;

		case 'j':
			if (mWidth >= 1)
				--mWidth;
			break;
	}
}

void Board::scaleY(char input)
{
	switch (input)
	{
		case 'k':
			if (lt.x + mHeight < ROW)
				++mHeight;
			else if (lt.x > 1)
			{
				--lt.x;
				++mHeight;
			}
			break;

		case 'l':
			if (mHeight >= 1)
				--mHeight;
			break;
	}
}


void Board::boundcheck()
{
	if (lt.x < 0)
		lt.x += 1;
	else if (lt.x + mHeight >= 30)
		lt.x -= 1;

	if (lt.y < 0)
		lt.y += 1;
	else if (lt.y + mWidth >= 30)
		lt.y -= 1;
}

class TestProgram
{
public:
	TestProgram();

	void run();
private:
	void userInput();
	void execute();

	Board mBoard;
	bool mShoudlClose;
	char mInput;
};

TestProgram::TestProgram()
	: mShoudlClose(false),
	mInput(NULL)
{
	mBoard.set();
}

void TestProgram::run()
{
	while (!mShoudlClose)
	{
		userInput();
		execute();
	}
}

void TestProgram::userInput()
{
	int check = false;
	std::vector<char> inputPool{ 'x', 'X', 'y', 'Y', 's', 'S', 'i', 'I', 'j', 'J',
		'k', 'K', 'l', 'L', 'r', 'R', 'q', 'Q' };

	while (!check)
	{
		std::cout << "Command >>> ";
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
		case 'x': case 'X':
		case 'y': case 'Y':
			mBoard.move(mInput);
			break;
		case 's': case 'S':
			mBoard.scale(mInput);
			break;
		case 'i': case 'I':
		case 'j': case 'J':
			mBoard.scaleX(mInput);
			break;
		case 'k': case 'K':
		case 'l': case 'L':
			mBoard.scaleY(mInput);
			break;
		case 'r': case 'R':
			mBoard.set();
			break;
		case 'q': case 'Q':
			mShoudlClose = true;
			break;
	}
	mBoard.update();
	system("cls");
	mBoard.print();
}

int main()
{
	TestProgram tp;

	tp.run();

	return 0;
}