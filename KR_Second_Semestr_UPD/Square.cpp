#include "Square.h"
Square::Square()
{
	CharArray = new p[s];
	for (int i = 0; i < s; i++)
	{
		CharArray[i] = new char[s];
	}
	char mas = 'A';
	for (int i = 0; i < s; i++)
	{

		for (int j = 0; j < s; j++)
		{
			//cin >> mas;//откоментить для ввода алфавита вручную + закоментить тогда Random
			//cin.get();
			CharArray[i][j] = mas;
			++mas;
		}
	}
}
Square::~Square()
{
	for (int i = 0; i < s; i++)
	{
		delete[] CharArray[i];
		CharArray[i] = nullptr;
	}
	delete[]CharArray;
	CharArray = nullptr;
}
void Square::Random()
{
	int z;
	srand(time(NULL));
	cout << " Enter the complexity of the game (1-100): ";
	while (!(cin >> z)||z<0||z>100)
	{
		cin.clear();
		while (cin.get() != '\n')
			continue;
		cout << "Error input! Reinput value:\n";
	}
	for (int k = 0; k < z; k++)//random
	{
		int i = (rand() % s);
		int j = (rand() % s);
		int m = (rand() % s);
		int n = (rand() % s);
		int c = CharArray[i][j];
		CharArray[i][j] = CharArray[m][n];
		CharArray[m][n] = c;
	}
	cin.get();
}
void Square::Output()
{
	int mas = 'A';
	for (int i = 0; i < s; i++)//для массива
	{
		cout << endl;
		if (i == 0)//для сетки координат
		{
			cout << "  ";
			cout << " ";
			for (int k = 0; k < s; k++)
			{
				cout << k << "  ";
			}
			cout << "        ";
			for (int k = 0; k < s; k++)
			{
				cout << k << "  ";
			}
			cout << endl;
		}
		cout << " ";
		cout << i << " ";
		for (int j = 0; j < s; j++)
		{

			cout <<CharArray[i][j] << "  ";
		}
		cout << "      ";
		cout << i << " ";
		for (int j = 0; j < s; j++)
		{
			cout << (char)mas << "  ";
			++mas;
		}
	}
	cout << endl;
	cout << endl;
	cout << "           Press: " << endl;
	cout << "           Q W E" << endl;
	cout << "           A S D" << endl;
	cout << "           Z X C" << endl;
	cout << "    To rotate the squares." << endl;
}
void Square::Swap(bool& f)
{
	while (f)
	{
		char a, b;
		cout << "Enter first upper letter: ";
		cin.get(a);
		if (cin.get() != '\n')
			while (cin.get() != '\n'){};
		if (a < 'A' || a>'P')
		{
			cout << "Wrong input!" << endl;
			break;
		}
		cout << "Enter second upper letter: ";
		cin.get(b);
		if (cin.get() != '\n')
			while (cin.get() != '\n');
		if (a < 'A' || a>'P')
		{
			cout << "Wrong input!" << endl;
			break;
		}
		int m, n, c;
		for (int i = 0; i < s; i++)
		{

			for (int j = 0; j < s; j++)
			{
				if (CharArray[i][j] == a)
				{
					m = i;
					n = j;
					break;
				}
			}
			for (int j = 0; j < s; j++)
			{
				if (CharArray[i][j] == b)
				{
					c = CharArray[m][n];
					CharArray[m][n] = CharArray[i][j];
					CharArray[i][j] = c;
				}
			}
		}
		f = false;
	}
}
void Square::Check(bool& Win)
{
	int mas = 'A';
	for (int i = 0; i < s; i++)
	{

		for (int j = 0; j < s; j++)
		{
			if (CharArray[i][j] != mas)
			{
				Win = false;
				break;
			}
			++mas;
		}
	}
	if (Win)
		cout << endl << " VICTORY!" << endl;
}
void Square::Round(int x, int y)
{
	char c = CharArray[x][y];
	CharArray[x][y] = CharArray[x + 1][y];
	CharArray[x + 1][y] = CharArray[x + 1][y + 1];
	CharArray[x + 1][y + 1] = CharArray[x][y + 1];
	CharArray[x][y + 1] = c;
	Output();
}
void Square::SortStr1(bool& end, bool pos, bool high, bool e, int m, int n, int& i, int& j, int& border, int& hborder, int& count, int a)
{
	end = (m == i&&n == j); pos = false;
	if (border == (s - 2) && (i == m&&n == (j - 1)))//если предпоследний элемент  С на нужной позиции
	{
		pos = true; end = true; ++hborder; high = true;
	}
	if ((hborder == (s - 2)) && (i < (s - 1)) && (a + 1 == CharArray[i + 1][j]) && end && (count >= ((s - 2)*s)))//I J если J под I
	{
		Round(i, j); Round(i, j); Round(i, j); Round(i, j + 1);  Round(i, j); Round(i, j + 1);
	}
	if (end)
	{
		if (border == (s - 2) && !pos&&CharArray[i][j + 1] != a + 1)//если С не на нужной позиции и след за ним буква - следущая в цикле
		{
			Round(i, j);   ++hborder; high = true; pos = true; j++;//сортируем предпослений элемент С
		}
		else
			if (border == (s - 2) && !high)//повышаем верхнюю границу
				++hborder;

		if (CharArray[i][j - 1] == (a + 1) && pos) //проверяем не являеться ли A B D C 
		{
			Round(i, j - 1);   Round(i, j - 1);   Round(i, j - 1);   Round(i + 1, j - 1);   Round(i, j - 1);   Round(i + 1, j - 1);  //крутим что б убрать D
		}
	}
	while (j < border && !end)//пока не выпехнем элемент за границу
	{
		if (i == (s - 1))
		{
			Round(i - 1, j); Round(i - 1, j);
			if (j == 0 && border == s - 2)//если  G на координатах  s-1 0 частный случай 
			{
				Round(i - 1, j + 1); e = true;
			}
			--i; ++j;
		}
		else
		{
			Round(i, j); ++j; if (e){ ++j; }
		}
	}
	if (!end)
		if (border == (s - 1))//ставим крайний элемент в нужное место D
		{
			if (i == hborder&&j == (s - 1))//если сразу на месте, проварачиваем подквадрат
			{
				--i; --j;	Round(i, j); Round(i, j); Round(i, j);	 	end = true;
			}
			else
			{
				while (i != hborder || j != (s - 1))
				{
					--i; --j;	Round(i, j); Round(i, j); Round(i, j);	  ++j;
				}
				--i; --j; Round(i, j); Round(i, j); Round(i, j);    end = true;
			}
		}
	if (!end)
		i--; j--;//находим координаты вершины
	if (!end)
		if (j < border)//выталкиваем за границу
		{
			j = border; Round(i, j);
		}
		else
			if (i < hborder)
			{
				i = hborder; Round(i, j); Round(i, j); Round(i, j);
			}
			else
			{
				Round(i, j); Round(i, j);
			}
	if (count == (s - 2)*s + 2 && end)//крутим I J на край (бок) 
	{
		Round(i, j); Round(i, j); Round(i, j);
	}
}
void Square::SortStr2(bool &end, int m, int &n, int &i, int &j, int &count, int &a)
{
	while (count > ((s - 2)*s + (s - 2)) && count < ((s - 1)*s + 1))//если сортируем 2 последних элемента предпоследней строки 
	{
		if (count == ((s - 2)*s + s - 1))//меняем значения дефолтных координат  тк сначала сортируем L потом K
			++n;
		if (count == ((s - 2)*s + s))//меняем значения дефолтных координат  тк сначала сортируем L потом K
		{
			--n; --n;
		}
		end = (m == i&&n == j);//проверка на координаты на своем ли месте буква
		if (end)
		{
			break;
		}
		if (count == ((s - 2)*s + s) && i == s - 1 && j == s - 1)//если К под L исключение 
		{
			--i; --j; Round(i, j);
			--j; Round(i, j);   Round(i, j);
			++j; Round(i, j);   Round(i, j);   Round(i, j);
			--j; Round(i, j);
			end = true;
			break;
		}
		if (i == s - 1)//Проверяем в какой строке нижней или предпоследней
		{
			if (j >= s - 2)//проверяем  за серединой или нет
			{
				--i; --j; Round(i, j);   Round(i, j);   Round(i, j);   ++j;
				end = (m == i&&n == j);
				if (end)
					break;
				else
					Round(i, j); j++;
			}
			else
			{
				--i; Round(i, j);   Round(i, j); ++j;
				end = (m == i&&n == j);
				if (end)
					break;
				else
					Round(i, j); j++;
			}
		}
		else
		{
			Round(i, j); ++j;
			end = (m == i&&n == j);
			if (end)
				break;
			else
				Round(i, j); ++j;
		}
		end = (m == i&&n == j);
		if (end)
		{
			break;
		}
	}
	if (count == ((s - 2)*s + s - 1))//возвращаемся к К 
	{
		--a; --a;
	}
	if (count == ((s - 2)*s + s))//поварачиваем K L - крайние элементы на бок
	{
		++a; Round(s - 2, s - 2);
	}
}
void Square::SortLastStr(bool &end, int &count, int &a)
{
	while (count >((s - 2)*s + s))//если осталась последняя строка
	{
		int check = 0; int x = -1, y = 0;//координаты
		if (CharArray[s / 2 + 1][s / 2 - 1] == a)//проверяем, на своем ли месте элементы в последней строке
		{
			++check;
		}
		if (CharArray[s / 2][s / 2 - 1] == a + 1)
		{
			++check;
		}
		if (CharArray[s / 2][s / 2] == a + 2)
		{
			++check;
		}
		if (CharArray[s / 2 + 1][s / 2] == a + 3)
		{
			++check;
		}
		if (check == s)//если все элементы на месте 
		{
			end = true; Round(s - 2, 0);  Round(s - 2, s / 2); Round(s - 2, s / 2); Round(s - 2, s / 2); a = a + s; break;
		}
		if (check < 2)//если меньше 2 на месте то прокручиваем 
		{
			Round(s - 2, s / 2 - 1);
		}
		else
		{
			Round(s - 2, 0);   Round(s - 2, s / 2);   Round(s - 2, s / 2);   Round(s - 2, s / 2);  //если хотя бы 2 на месте - возвращаем их в строку
			if (CharArray[s - 1][0] != a)
				x = 0;
			if (CharArray[s - 1][1] != a + 1)//проверям какие 2 буквы нужно сменить местами
				if (x != -1)
					y = 1;
				else
					x = 1;
			if (CharArray[s - 1][2] != a + 2)
				if (x != -1)
					y = 2;
				else
					x = 2;
			if (CharArray[s - 1][3] != a + 3)
				if (x != -1)
					y = 3;
			int w = CharArray[s - 1][x];//меняем эти 2 буквы
			CharArray[s - 1][x] = CharArray[s - 1][y];
			CharArray[s - 1][y] = w;
			a = a + s;//что б основной цикл дальше не шел
			cout << "           SWAP\n";
			Output();
			end = true;//конец цикла
			break;
		}
	}
}
void Square::AutoGame()
{
	Random();//сортируем рандомно наш массив
	Output();
	bool pos = false; bool end = false; int m = 0, n = -1; int border = -1; int hborder = 0;  int count = 0; bool e = false; bool high = false;
	for (int a = 'A'; a < 'P'; a++)//a - current character
	{
		++n;//для сравнения с дэфолтным алфавитом вместо еще одного массива просто задаем координаты текущей буквы
		if (border < (s - 1))//левая граница нужна для выталкивания за нее буквы
			++border;
		else
		{
			border = 0;//обнуляем границу когда начинается новая строка
			++m;//следующая строка 
			n = 0;//с начала строки 
		}
		count++;//количество отсортированных букв 
		end = false; high = false; e = false;//обнуляем булевcкие переменные
		if (count == ((s - 2)*s + s - 1))//если дошли до К сортируем сначала L
			++a;
		int i = 0;
		while (i < s && !end)
		{
			int j = 0;
			while (j < s&&!end)
			{
				while (CharArray[i][j] == a && !end)//если наша буква является текущей 
				{
					if (count < s*(s - 2) + (s - 1))//сортируем s-2 строки + 2 элемента s-1 строки
					{
						SortStr1(end, pos, high, e, m, n, i, j, border, hborder, count, a);
					}
					else
						if (count < s*(s - 1) + 1)//сортируем последние 2 элемента s-1 строки 
							SortStr2(end, m, n, i, j, count, a);
						else//сортируем последнюю строку
							SortLastStr(end, count, a);
				}
				++j;
			}
			++i;
		}
	}
	Check(end);
}
void Square::Game()
{
	bool Win = false, f = true; char k;
	Random();
	Output();//for output matrix
	while (!Win)
	{
		if (f)
			cout << " Or press F to swap two any letters." << endl;
		cin.get(k);//Здесь можно сделать, что б вводить координаты вместо буквы
		if (cin.get() != '\n')
			while (cin.get() != '\n');
		switch (k)
		{
		case('q') :
			Round(0, 0);//здесь можно передавать координаты, которые ввели выше
			break;
		case('w') :
			Round(0, 1);
			break;
		case('e') :
			Round(0, 2);
			break;
		case('a') :
			Round(1, 0);
			break;
		case('s') :
			Round(1, 1);
			break;
		case('d') :
			Round(1, 2);
			break;
		case('z') :
			Round(2, 0);
			break;
		case('x') :
			Round(2, 1);
			break;
		case('c') :
			Round(2, 2);
			break;
		case('f') :
			if (f)
				Swap(f);//for swap 2 letters
			else
				cout << "Alredy used!" << endl;
			break;
		default:
			cout << "Reinput" << endl;
		}
		Win = true;
		Check(Win);//check the Victory
	}
}