// ------------------------------------------------------------
// 2016180007 김명규
// warming1.cpp
// Ctrl + M, L to expand all
// ------------------------------------------------------------

#include <iostream>
#include <random>
#include <vector>
#include <algorithm>

// Random class declaration
class Random
{
public:
	static void init();
	static int getInt(int min, int max);
private:
	static std::mt19937 generator;
};

// Matrix3 class declaration
class Matrix3
{
public:
	Matrix3();

	void transpose();
	void set();
	void print() const;

	int getDet() const { return mDet; }

	Matrix3 operator*(const Matrix3& other) const;
	Matrix3 operator+(const Matrix3& other) const;
	Matrix3 operator-(const Matrix3& other) const;
	const int* const operator[](int index) const;
	int* operator[](int index);
private:
	void determinant();

	int mMat[3][3];
	int mDet;
};

// Matrix4 class declaration
class Matrix4
{
public:
	Matrix4();

	void print() const;
	void set(const Matrix3& mat);
	int getDet() const { return mDet; }
private:
	int mMat[4][4];
	int mDet;
};

// Caculator class declaration
class Caculator
{
public:
	Caculator();

	void run();

private:
	void printMenu() const;
	void userInput();
	void execute();

	Matrix3 mLeft;
	Matrix3 mRight;
	Matrix4 mMat4;
	bool mShouldClose;
	char mInput;
};

int main()
{
	Random::init();

	Caculator cal;
	cal.run();
	
	return 0;
}

// --------Random class definition----------
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


// --------Matrix3 class definition----------
Matrix3::Matrix3()
	: mDet(0)
{
	set();
}

void Matrix3::set()
{
	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < 3; ++j)
			mMat[i][j] = Random::getInt(0, 1);
	determinant();
}

void Matrix3::print() const
{
	for (int i = 0; i < 3; ++i)
	{
		std::cout << "| ";
		for (int j = 0; j < 3; ++j)
			std::cout << mMat[i][j] << " ";
		std::cout << "|" << std::endl;
	}
}

void Matrix3::transpose()
{
	Matrix3 temp;
	
	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < 3; ++j)
			temp.mMat[i][j] = mMat[j][i];
	
	*this = temp;
	determinant();
}

void Matrix3::determinant()
{
	int temp = (mMat[0][0] * (mMat[1][1] * mMat[2][2] - mMat[1][2] * mMat[2][1])) +
		(mMat[0][1] * -1 * (mMat[1][0] * mMat[2][2] - mMat[1][2] * mMat[2][0])) +
		(mMat[0][2] * (mMat[1][0] * mMat[2][1] - mMat[1][1] * mMat[2][0]));

	mDet = temp;
}

Matrix3 Matrix3::operator*(const Matrix3& other) const
{
	Matrix3 temp;

	temp.mMat[0][0] =
		(*this).mMat[0][0] * other.mMat[0][0] +
		(*this).mMat[0][1] * other.mMat[1][0] +
		(*this).mMat[0][2] * other.mMat[2][0];

	temp.mMat[0][1] =
		(*this).mMat[0][0] * other.mMat[0][1] +
		(*this).mMat[0][1] * other.mMat[1][1] +
		(*this).mMat[0][2] * other.mMat[2][1];

	temp.mMat[0][2] =
		(*this).mMat[0][0] * other.mMat[0][2] +
		(*this).mMat[0][1] * other.mMat[1][2] +
		(*this).mMat[0][2] * other.mMat[2][2];

	temp.mMat[1][0] =
		(*this).mMat[1][0] * other.mMat[0][0] +
		(*this).mMat[1][1] * other.mMat[1][0] +
		(*this).mMat[1][2] * other.mMat[2][0];

	temp.mMat[1][1] =
		(*this).mMat[1][0] * other.mMat[0][1] +
		(*this).mMat[1][1] * other.mMat[1][1] +
		(*this).mMat[1][2] * other.mMat[2][1];

	temp.mMat[1][2] =
		(*this).mMat[1][0] * other.mMat[0][2] +
		(*this).mMat[1][1] * other.mMat[1][2] +
		(*this).mMat[1][2] * other.mMat[2][2];

	temp.mMat[2][0] =
		(*this).mMat[2][0] * other.mMat[0][0] +
		(*this).mMat[2][1] * other.mMat[1][0] +
		(*this).mMat[2][2] * other.mMat[2][0];

	temp.mMat[2][1] =
		(*this).mMat[2][0] * other.mMat[0][1] +
		(*this).mMat[2][1] * other.mMat[1][1] +
		(*this).mMat[2][2] * other.mMat[2][1];

	temp.mMat[2][2] =
		(*this).mMat[2][0] * other.mMat[0][2] +
		(*this).mMat[2][1] * other.mMat[1][2] +
		(*this).mMat[2][2] * other.mMat[2][2];

	return temp;
}

Matrix3 Matrix3::operator+(const Matrix3& other) const
{
	Matrix3 temp;

	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < 3; ++j)
			temp.mMat[i][j] = (*this).mMat[i][j] + other.mMat[i][j];

	return temp;
}

Matrix3 Matrix3::operator-(const Matrix3& other) const
{
	Matrix3 temp;

	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < 3; ++j)
			temp.mMat[i][j] = (*this).mMat[i][j] - other.mMat[i][j];

	return temp;
}

const int* const Matrix3::operator[](int index) const
{
	if (index < 0 || index >= 3)
	{
		std::cout << "Index out of range" << std::endl;
		exit(1);
	}

	return mMat[index];
}

int* Matrix3::operator[](int index)
{
	if (index < 0 || index >= 3)
	{
		std::cout << "Index out of range" << std::endl;
		exit(1);
	}

	return mMat[index];
}


// --------Matrix4 class definition----------
Matrix4::Matrix4()
	: mDet(0)
{
}

void Matrix4::print() const
{
	for (int i = 0; i < 4; ++i)
	{
		std::cout << "| ";
		for (int j = 0; j < 4; ++j)
			std::cout << mMat[i][j] << " ";
		std::cout << "|" << std::endl;
	}
}

void Matrix4::set(const Matrix3& mat)
{
	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < 3; ++j)
			mMat[i][j] = mat[i][j];

	for (int i = 0; i < 3; ++i)
	{
		mMat[i][3] = 0;
		mMat[3][i] = 0;
	}
	mMat[3][3] = 1;

	mDet = 1 * mat.getDet();
}


// --------Caculator class definition----------
Caculator::Caculator()
	: mShouldClose(false),
	mInput(0)
{
}

void Caculator::run()
{
	while (!mShouldClose)
	{
		userInput();
		execute();
	}
}

void Caculator::printMenu() const
{
	std::cout << "--------3x3 행렬 계산기--------" << std::endl;
	std::cout << "Press 'M' to multiply" << std::endl;
	std::cout << "Press 'A' to add" << std::endl;
	std::cout << "Press 'D' to subtract" << std::endl;
	std::cout << "Press 'R' to get determinant" << std::endl;
	std::cout << "Press 'T' to transpose" << std::endl;
	std::cout << "Press 'H' to convert to 4x4 matrix" << std::endl;
	std::cout << "Press 'S' to reset" << std::endl;
	std::cout << "Press 'Q' to quit" << std::endl;
	std::cout << "------------------------------" << std::endl;
	std::cout << "Your choice>> ";
}

void Caculator::userInput()
{
	int check = false;
	std::vector<char> inputPool{ 'm', 'M', 'a', 'A', 'd', 'D', 'r', 'R', 't', 'T', 'h', 'H', 's', 'S', 'q', 'Q' };

	while (!check)
	{
		printMenu();
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

void Caculator::execute()
{
	Matrix3 mat3;
	switch (mInput)
	{
	case 'm': case 'M':
		std::cout << "\n두 행렬 간 곱셈을 수행합니다." << std::endl;
		mLeft.print();
		std::cout << "    *     " << std::endl;
		mRight.print();
		std::cout << "    =     " << std::endl;
		mat3 = mLeft * mRight;
		mat3.print();
		break;
	case 'a': case 'A':
		std::cout << "\n두 행렬 간 덧셈을 수행합니다." << std::endl;
		mLeft.print();
		std::cout << "    +     " << std::endl;
		mRight.print();
		std::cout << "    =     " << std::endl;
		mat3 = mLeft + mRight;
		mat3.print();
		break;
	case 'd': case 'D':
		std::cout << "\n두 행렬 간 뺄셈을 수행합니다." << std::endl;
		mLeft.print();
		std::cout << "    -     " << std::endl;
		mRight.print();
		std::cout << "    =     " << std::endl;
		mat3 = mLeft - mRight;
		mat3.print();
		break;
	case 'r': case 'R':
		std::cout << "\n두 행렬의 행렬식을 출력합니다." << std::endl;
		mLeft.print();
		std::cout << "    = " << mLeft.getDet() << std::endl;
		mRight.print();
		std::cout << "    = " << mRight.getDet() <<std::endl;
		break;
	case 't': case 'T':
		std::cout << "\n두 행렬을 전치하고 행렬식을 출력합니다." << std::endl;
		mLeft.print();
		std::cout << "----- Transpose to -----" << std::endl;
		mLeft.transpose();
		mLeft.print();
		std::cout << "    = " << mLeft.getDet() << std::endl << std::endl;

		mRight.print();
		std::cout << "----- Transpose to -----" << std::endl;
		mRight.transpose();
		mRight.print();
		std::cout << "    = " << mRight.getDet() << std::endl;
		break;
	case 'h': case 'H':
		std::cout << "\n두 행렬을 4x4 행렬로 변환하고 행렬식을 출력합니다." << std::endl;
		mLeft.print();
		std::cout << "----- Transform to -----" << std::endl;
		mMat4.set(mLeft);
		mMat4.print();
		std::cout << "    = " << mMat4.getDet() << std::endl << std::endl;

		mRight.print();
		std::cout << "----- Transform to -----" << std::endl;
		mMat4.set(mRight);
		mMat4.print();
		std::cout << "    = " << mMat4.getDet() << std::endl;
		break;
	case 's': case 'S':
		std::cout << "\n두 행렬의 값을 재설정합니다." << std::endl;
		mLeft.set();
		mRight.set();
		break;
	case 'q': case 'Q':
		mShouldClose = true;
		break;
	}
	std::cout << std::endl;
}