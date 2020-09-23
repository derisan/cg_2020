// ---------------------------------
// 2016180007 김명규
// 4. 저장 리스트 만들기
// ---------------------------------

#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <algorithm>

struct Point
{
	int x;
	int y;
	int z;
	double dist;

	Point(int x, int y, int z);
	void print() const;
	double distance();
};

Point::Point(int x = 0, int y = 0, int z = 0)
	: x(x),
	y(y),
	z(z)
{
	dist = distance();
}

void Point::print() const
{
	std::cout << "(" << x << ", " << y << ", " << z << ")" << std::endl;
}

double Point::distance()
{
	dist = sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
	return dist;
}

class MyList
{
public:
	MyList();
	~MyList();

	void append(int x, int y, int z);
	void pop();
	void enqueue(int x, int y, int z);
	void dequeue();
	int size() const { return mPoints.size(); }
	void clear();
	void farthest() const;
	void nearest() const;
	void sort();
	void print() const;

private:
	std::vector<Point*> mPoints;
	int mLimit;
};

MyList::MyList()
	: mLimit(10)
{

}

void MyList::sort()
{
	std::sort(mPoints.begin(), mPoints.end(),
		[](const Point* const a, const Point* const b) -> bool
	{
		return a->dist < b->dist;
	});
}

void MyList::print() const
{
	if (!mPoints.empty())
	{
		int last = mPoints.size() - 1;

		auto iter = mPoints.rbegin();
		for (; iter != mPoints.rend(); ++iter)
		{
			std::cout << last-- << " | ";
			(*iter)->print();
		}
	}
	else
		std::cout << "List is empty." << std::endl;
}

void MyList::append(int x, int y, int z)
{
	if (size() < mLimit)
	{
		Point* p = new Point(x, y, z);
		mPoints.emplace_back(p);
	}
	else
		std::cout << "List is full." << std::endl;
}

void MyList::pop()
{
	if (!mPoints.empty())
	{
		delete mPoints.back();
		mPoints.pop_back();
	}
}

void MyList::enqueue(int x, int y, int z)
{
	if (size() < mLimit)
	{
		Point* p = new Point(x, y, z);
		mPoints.insert(mPoints.begin(), p);
	}
	else
		std::cout << "List is full." << std::endl;
}

void MyList::dequeue()
{
	if (!mPoints.empty())
	{
		delete mPoints.front();
		mPoints.erase(mPoints.begin());
	}
}

void MyList::farthest() const
{
	if (!mPoints.empty())
	{
		Point* temp = mPoints[0];
		double distance = 0;
		for (auto point : mPoints)
		{
			if (distance < point->distance())
			{
				distance = point->distance();
				temp = point;
			}
		}
		temp->print();
	}
	else
		std::cout << "List is empty." << std::endl;
}

void MyList::nearest() const
{
	if (!mPoints.empty())
	{
		Point* temp = mPoints[0];
		double distance = mPoints[0]->distance();
		for (auto point : mPoints)
		{
			if (distance > point->distance())
			{
				distance = point->distance();
				temp = point;
			}
		}
		temp->print();
	}
	else
		std::cout << "List is empty." << std::endl;
}

MyList::~MyList()
{
	clear();
}

void MyList::clear()
{
	for (auto point : mPoints)
		delete point;
	mPoints.clear();
}

class TestProgram
{
public:
	TestProgram();
	~TestProgram();
	void run();

private:
	void print() const;
	void userInput();
	void execute();

	MyList* list;
	bool mShouldClose;
	std::string mInput;
};

TestProgram::TestProgram()
	: list(nullptr),
	mShouldClose(false)
{
	list = new MyList();
}

TestProgram::~TestProgram()
{
	delete list;
}

void TestProgram::run()
{
	while (!mShouldClose)
	{
		userInput();
		execute();
	}
}

void TestProgram::print() const
{
	list->print();
}

void TestProgram::userInput()
{
	std::string str;
	std::getline(std::cin, str);

	auto iter = std::remove(str.begin(), str.end(), ' ');
	str.erase(iter, str.end());

	mInput = str;
}

void TestProgram::execute()
{
	switch (mInput[0])
	{
		case '+':
			list->append(static_cast<int>(mInput[1] - '0'), static_cast<int>(mInput[2] - '0'), static_cast<int>(mInput[3] - '0'));
			list->print();
			break;
		case '-':
			list->pop();
			list->print();
			break;
		case 'e': case 'E':
			list->enqueue(static_cast<int>(mInput[1] - '0'), static_cast<int>(mInput[2] -'0'), static_cast<int>(mInput[3] - '0'));
			list->print();
			break;
		case 'd': case 'D':
			list->dequeue();
			list->print();
			break;
		case 'l': case 'L':
			std::cout << "리스트 길이>>> " << list->size() << std::endl;
			break;
		case 'c': case 'C':
			list->clear();
			list->print();
			break;
		case 'm': case 'M':
			list->farthest();
			break;
		case 'n': case 'N':
			list->nearest();
			break;
		case 's': case 'S':
			list->sort();
			list->print();
			break;
		case 'q': case 'Q':
			mShouldClose = true;
			break;
		default:
			std::cout << "Invalid option." << std::endl;
	}
	std::cout << std::endl;
}

int main()
{
	TestProgram tp;
	tp.run();

	return 0;
}