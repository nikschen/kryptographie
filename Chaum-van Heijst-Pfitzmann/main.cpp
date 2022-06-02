#include <bitset>
#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;

string decToBin(int _dec)
{
	string binary = std::bitset<16>(_dec).to_string();
	binary.erase(0, binary.find_first_not_of('0'));
	return binary;
}

//Q if binary 0, QM if binary 1 => Q ==Square M==Multiply
long squareAndMultiply(int _base, int _exponent, int _mod)
{
	string binaryExp = decToBin(_exponent);
	string commandChain = "";
	long result = 1;
	for (char c : binaryExp)
	{
		if (c == '1') commandChain += "QM";
		else commandChain += 'Q';
	}
	for (char command : commandChain)
	{
		if (command == 'Q') result *= result;
		else result *= _base;
		result %= _mod;
	}
	return result;
}

long hash(int _x1, int _x2, int _alpha, int _beta, int _p)
{
	return (squareAndMultiply(_alpha, _x1, _p)* squareAndMultiply(_beta, _x2, _p))%_p;
}

int main()
{
	int p = 12347;
	int alpha = 2;
	int beta = 8461;
	int q = (p - 1) / 2;
	cout << hash(5692, 144, alpha, beta, p) << endl;
	cout << hash(1220, 54, alpha, beta, p) << endl;
	cout << hash(212, 4214, alpha, beta, p) << endl;

	return 0;
}