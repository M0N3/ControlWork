#ifndef SQUARE_H
#define SQUARE_H
#include <iostream>
#include <time.h>
using namespace std;
const int s = 4;//размер массива 
typedef char* p;
typedef char** pp;
class Square
{
private:
	pp CharArray;
	void Output();
	void Swap(bool& f);
	void Check(bool& Win);
	void Random();
	void Round(int x, int y);
	void SortStr1(bool &end, bool pos, bool high, bool e, int m, int n, int &i, int &j, int &border, int &hborder, int &count, int a);
	void SortStr2(bool &end, int m, int &n, int &i, int &j, int &count, int &a);
	void SortLastStr(bool &end, int &count, int &a);
public:
	Square();
	~Square();
	void AutoGame();
	void Game();

};
#endif