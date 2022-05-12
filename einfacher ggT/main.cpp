#include <iostream>


//calculate via euklid algorithm which number is the greatest shared divider
int euklid(int _a, int _b)
{
	int h = 0;
	if (_a < _b) std::swap(_a, _b);

	while (_b != 0)
	{
		h = _a % _b;
		_a = _b;
		_b = h;
	}
	return _a;
}

int main()
{
	while (1)
	{
		system("cls");
		int a = 0;
		int b = 0;
		std::cout << "Gemeinsamer Teiler von (1.Zahl eingeben) ";
		std::cin >> a;
		std::cout << " und (2.Zahl eingeben) ";
		std::cin >> b;
		int ggT = euklid(a, b);
		std::cout << std::endl;
		std::cout << "Gemeinsamer Teiler von " << a << " und " << b << " => " << ggT << std::endl;
		system("pause");
	}
	return 0;
}