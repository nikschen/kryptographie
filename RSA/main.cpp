#include <iostream>
#include <string>
#include <bitset>

using std::string; 
using std::cout;
using std::endl;

int ggT(int _a, int _b)
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

int advancedGGT(int _a0, int _a1)
{
	int xIMinus1 = 1;
	int xI = 0;
	int yIMinus1 = 0;
	int yI = 1;
	int aIMinus1 = _a0;
	int aI = _a1;
	int qI = 0;

	do
	{
		int aIMinus1Temp = aIMinus1;
		int xIMinus1Temp = xIMinus1;
		int yIMinus1Temp = yIMinus1;
		aIMinus1 = aI;
		xIMinus1 = xI;
		yIMinus1 = yI;


		qI = aIMinus1Temp / aI;
		aI = aIMinus1Temp - qI * aI;
		xI = xIMinus1Temp - qI * xI;
		yI = yIMinus1Temp - qI * yI;


	} while (aI != 0);

	//std::cout << "aN-1=" << aIMinus1 << "\nxN-1=" << xIMinus1 << "\nyN-1=" << yIMinus1 << std::endl;

	return xIMinus1;
}

int getE(int _phi)
{
	int e = 3;
	while (ggT(e, _phi) != 1)
	{
		e++;
	}
	return e;
}

string decToBin(int _dec)
{
	string binary = std::bitset<16>(_dec).to_string();
	binary.erase(0, binary.find_first_not_of('0'));
	return binary;
}

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

int main()
{
	int d = 0; 
	int e = 0;
	int n = 0;
	int p = 13;
	int q = 23;
	int phi = (p-1)*(q-1);
	int M = 212;
	int C = 0;

	//int p = 11;
	//int q = 13;
	//int n = 143;
	//int phi = 120;
	//int e = 7;
	//int d = 103;
	//int M = 15;
	//int C = 115;

	//int p = 23;
	//int q = 67;
	//int n = 1541;
	//int phi = 1452;
	//int e = 5;
	//int d = 581;
	//int M = 15;
	//int C = 1203;

	n = p * q;
	e = getE(phi);
	d = advancedGGT(e, phi);
	if (d < 0) d += phi;
	cout << squareAndMultiply(8, 27, 55);
	C = squareAndMultiply(M, e, n);
	M = squareAndMultiply(C, d, n);
	cout << "d=" << d << endl;
	cout << "e=" << e << endl;
	cout << "phi=" << phi << endl;
	cout << "n=" << n << endl;
	cout << "C=M^e =>C=" << C << endl;
	cout << "M=C^d =>M=" << M << endl;
	
	return 0;
}