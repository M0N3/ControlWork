#include "Square.h"
const int NotUsed = system("color F0");
void main()
{

	char y = 'y'; int i; Square x;
	while (y == 'y')
	{
		cout << " Enter 1 to play or 2 for autogame: ";
		while (!(cin >> i) || i < 1 || i>2)
		{
			cin.clear();
			while (cin.get() != '\n')
				continue;
			cout << "Error input! Reinput value:\n";
		}
		switch (i)
		{
		case 1:
			x.Game();
			break;
		case 2:
			x.AutoGame();
			break;
		}
		cout << "\n Again? y/other" << endl;
		cin >> y;
	}
}
