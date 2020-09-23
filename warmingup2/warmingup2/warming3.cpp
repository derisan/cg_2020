// ---------------------------------
// 2016180007 김명규
// 3. 도형 간의 충돌 체크
// ---------------------------------

#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

class Random
{
public:
	static void init();
	static int getInt(int min, int max);
private:
	static std::mt19937 generator;
};

struct Point
{
	int x;
	int y;

	void print() const;
};

class Rect
{
public:
	Rect();
	void move(char input);
	void print() const;
	// Return true if collides with other Rect
	bool intersect(const Rect& other) const;

private:
	Point lt;
	Point rb;
	int mWidth;
	int mHeight;
	int mMoveSpeed;
};

class CollisionCheckProgram
{
public:
	CollisionCheckProgram();
	void run();

private:
	void printRect() const;
	void userInput();
	void execute();

	Rect mFirst;
	Rect mSecond;
	bool mShouldClose;
	char mInput;
};

void Point::print() const
{
	std::cout << "(" << x << ", " << y << ") ";
}

Rect::Rect()
	: mMoveSpeed(40)
{
	lt.x = Random::getInt(0, 499);
	lt.y = Random::getInt(0, 499);
	mWidth = std::min(40, 500 - lt.x);
	mHeight = std::min(40, 500 - lt.y);
	rb.x = lt.x + mWidth;
	rb.y = lt.y + mHeight;
}

void Rect::move(char input)
{
	switch (input)
	{
		case 'w': case 'W':
			lt.y -= mMoveSpeed;
			rb.y -= mMoveSpeed;
			break;
		case 's': case 'S':			
			lt.y += mMoveSpeed;
			rb.y += mMoveSpeed;
			break;
		case 'a': case 'A':
			lt.x -= mMoveSpeed;
			rb.x -= mMoveSpeed;
			break;
		case 'd': case 'D':
			lt.x += mMoveSpeed;
			rb.x += mMoveSpeed;
			break;
	}

	if (lt.x < 0)
	{
		std::cout << "Rect bound error" << std::endl;
		lt.x += mMoveSpeed;
		rb.x += mMoveSpeed;
	}

	if (lt.y < 0)
	{
		std::cout << "Rect bound error" << std::endl;
		lt.y += mMoveSpeed;
		rb.y += mMoveSpeed;
	}

	if (rb.x > 500)
	{
		std::cout << "Rect bound error" << std::endl;
		rb.x -= mMoveSpeed;
		lt.x -= mMoveSpeed;
	}

	if (rb.y > 500)
	{
		std::cout << "Rect bound error" << std::endl;
		rb.y -= mMoveSpeed;
		lt.y -= mMoveSpeed;
	}
}

void Rect::print() const
{
	lt.print();
	rb.print();
	std::cout << std::endl;
}

bool Rect::intersect(const Rect& other) const
{
	bool res = lt.x > other.rb.x ||
		rb.x < other.lt.x ||
		lt.y > other.rb.y ||
		rb.y < other.lt.y;

	return !res;
}

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

CollisionCheckProgram::CollisionCheckProgram()
	: mShouldClose(false),
	mInput(0)
{
}

void CollisionCheckProgram::run()
{
	std::cout << "이동 명령어(q to quit): a(left), d(right), s(down), w(up)" << std::endl;
	std::cout << "Input Shape Coordinates value:" << std::endl;
	printRect();
	while (!mShouldClose)
	{
		userInput();
		execute();
	}
}


void CollisionCheckProgram::printRect() const
{
	std::cout << "	Shape 1:"; mFirst.print();
	std::cout << "	Shape 2:"; mSecond.print();
	std::cout << std::endl;
}

void CollisionCheckProgram::userInput()
{
	int check = false;
	std::vector<char> inputPool{ 'a', 'A', 'd', 'D', 's', 'S', 'w', 'W', 'q', 'Q' };

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

void CollisionCheckProgram::execute()
{
	switch (mInput)
	{
		case 'w': case 'W':
			mSecond.move(mInput);
			break;
		case 's': case 'S':
			mSecond.move(mInput);
			break;
		case 'a': case 'A':
			mSecond.move(mInput);
			break;
		case 'd': case 'D':
			mSecond.move(mInput);
			break;
		case 'q': case 'Q':
			mShouldClose = true;
			break;
	}
	printRect();

	if (mFirst.intersect(mSecond))
	{
		std::cout << "Rect1 & Rect2 collide!!" << std::endl;
		mShouldClose = true;
	}
}

int main()
{
	Random::init();

	CollisionCheckProgram ccp;
	ccp.run();

	return 0;
}