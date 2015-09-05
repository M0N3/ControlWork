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
			//cin >> mas;//����������� ��� ����� �������� ������� + ����������� ����� Random
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
	for (int i = 0; i < s; i++)//��� �������
	{
		cout << endl;
		if (i == 0)//��� ����� ���������
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
	if (border == (s - 2) && (i == m&&n == (j - 1)))//���� ������������� �������  � �� ������ �������
	{
		pos = true; end = true; ++hborder; high = true;
	}
	if ((hborder == (s - 2)) && (i < (s - 1)) && (a + 1 == CharArray[i + 1][j]) && end && (count >= ((s - 2)*s)))//I J ���� J ��� I
	{
		Round(i, j); Round(i, j); Round(i, j); Round(i, j + 1);  Round(i, j); Round(i, j + 1);
	}
	if (end)
	{
		if (border == (s - 2) && !pos&&CharArray[i][j + 1] != a + 1)//���� � �� �� ������ ������� � ���� �� ��� ����� - �������� � �����
		{
			Round(i, j);   ++hborder; high = true; pos = true; j++;//��������� ������������ ������� �
		}
		else
			if (border == (s - 2) && !high)//�������� ������� �������
				++hborder;

		if (CharArray[i][j - 1] == (a + 1) && pos) //��������� �� ��������� �� A B D C 
		{
			Round(i, j - 1);   Round(i, j - 1);   Round(i, j - 1);   Round(i + 1, j - 1);   Round(i, j - 1);   Round(i + 1, j - 1);  //������ ��� � ������ D
		}
	}
	while (j < border && !end)//���� �� �������� ������� �� �������
	{
		if (i == (s - 1))
		{
			Round(i - 1, j); Round(i - 1, j);
			if (j == 0 && border == s - 2)//����  G �� �����������  s-1 0 ������� ������ 
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
		if (border == (s - 1))//������ ������� ������� � ������ ����� D
		{
			if (i == hborder&&j == (s - 1))//���� ����� �� �����, ������������� ����������
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
		i--; j--;//������� ���������� �������
	if (!end)
		if (j < border)//����������� �� �������
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
	if (count == (s - 2)*s + 2 && end)//������ I J �� ���� (���) 
	{
		Round(i, j); Round(i, j); Round(i, j);
	}
}
void Square::SortStr2(bool &end, int m, int &n, int &i, int &j, int &count, int &a)
{
	while (count > ((s - 2)*s + (s - 2)) && count < ((s - 1)*s + 1))//���� ��������� 2 ��������� �������� ������������� ������ 
	{
		if (count == ((s - 2)*s + s - 1))//������ �������� ��������� ���������  �� ������� ��������� L ����� K
			++n;
		if (count == ((s - 2)*s + s))//������ �������� ��������� ���������  �� ������� ��������� L ����� K
		{
			--n; --n;
		}
		end = (m == i&&n == j);//�������� �� ���������� �� ����� �� ����� �����
		if (end)
		{
			break;
		}
		if (count == ((s - 2)*s + s) && i == s - 1 && j == s - 1)//���� � ��� L ���������� 
		{
			--i; --j; Round(i, j);
			--j; Round(i, j);   Round(i, j);
			++j; Round(i, j);   Round(i, j);   Round(i, j);
			--j; Round(i, j);
			end = true;
			break;
		}
		if (i == s - 1)//��������� � ����� ������ ������ ��� �������������
		{
			if (j >= s - 2)//���������  �� ��������� ��� ���
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
	if (count == ((s - 2)*s + s - 1))//������������ � � 
	{
		--a; --a;
	}
	if (count == ((s - 2)*s + s))//������������ K L - ������� �������� �� ���
	{
		++a; Round(s - 2, s - 2);
	}
}
void Square::SortLastStr(bool &end, int &count, int &a)
{
	while (count >((s - 2)*s + s))//���� �������� ��������� ������
	{
		int check = 0; int x = -1, y = 0;//����������
		if (CharArray[s / 2 + 1][s / 2 - 1] == a)//���������, �� ����� �� ����� �������� � ��������� ������
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
		if (check == s)//���� ��� �������� �� ����� 
		{
			end = true; Round(s - 2, 0);  Round(s - 2, s / 2); Round(s - 2, s / 2); Round(s - 2, s / 2); a = a + s; break;
		}
		if (check < 2)//���� ������ 2 �� ����� �� ������������ 
		{
			Round(s - 2, s / 2 - 1);
		}
		else
		{
			Round(s - 2, 0);   Round(s - 2, s / 2);   Round(s - 2, s / 2);   Round(s - 2, s / 2);  //���� ���� �� 2 �� ����� - ���������� �� � ������
			if (CharArray[s - 1][0] != a)
				x = 0;
			if (CharArray[s - 1][1] != a + 1)//�������� ����� 2 ����� ����� ������� �������
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
			int w = CharArray[s - 1][x];//������ ��� 2 �����
			CharArray[s - 1][x] = CharArray[s - 1][y];
			CharArray[s - 1][y] = w;
			a = a + s;//��� � �������� ���� ������ �� ���
			cout << "           SWAP\n";
			Output();
			end = true;//����� �����
			break;
		}
	}
}
void Square::AutoGame()
{
	Random();//��������� �������� ��� ������
	Output();
	bool pos = false; bool end = false; int m = 0, n = -1; int border = -1; int hborder = 0;  int count = 0; bool e = false; bool high = false;
	for (int a = 'A'; a < 'P'; a++)//a - current character
	{
		++n;//��� ��������� � ��������� ��������� ������ ��� ������ ������� ������ ������ ���������� ������� �����
		if (border < (s - 1))//����� ������� ����� ��� ������������ �� ��� �����
			++border;
		else
		{
			border = 0;//�������� ������� ����� ���������� ����� ������
			++m;//��������� ������ 
			n = 0;//� ������ ������ 
		}
		count++;//���������� ��������������� ���� 
		end = false; high = false; e = false;//�������� �����c��� ����������
		if (count == ((s - 2)*s + s - 1))//���� ����� �� � ��������� ������� L
			++a;
		int i = 0;
		while (i < s && !end)
		{
			int j = 0;
			while (j < s&&!end)
			{
				while (CharArray[i][j] == a && !end)//���� ���� ����� �������� ������� 
				{
					if (count < s*(s - 2) + (s - 1))//��������� s-2 ������ + 2 �������� s-1 ������
					{
						SortStr1(end, pos, high, e, m, n, i, j, border, hborder, count, a);
					}
					else
						if (count < s*(s - 1) + 1)//��������� ��������� 2 �������� s-1 ������ 
							SortStr2(end, m, n, i, j, count, a);
						else//��������� ��������� ������
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
		cin.get(k);//����� ����� �������, ��� � ������� ���������� ������ �����
		if (cin.get() != '\n')
			while (cin.get() != '\n');
		switch (k)
		{
		case('q') :
			Round(0, 0);//����� ����� ���������� ����������, ������� ����� ����
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