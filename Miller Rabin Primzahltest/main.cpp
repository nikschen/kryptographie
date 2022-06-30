#include <iostream>
#include <string>
#include <time.h>
#include <bitset>

//Implementieren Sie den Miller - Rabin Test zum Testen von Primzahlen.
//Übergeben Sie dafür Ihrem Programm die Rundenzahl k und die zu testende Zahl n.
//Das a ist in jeder Runde eine neue Zufallszahl zwischen 2 und n − 2

using std::cin;
using std::cout;
using std::endl;
using std::string;

string decToBin(long long _dec)
{
	string binary = std::bitset<32>(_dec).to_string();
	binary.erase(0, binary.find_first_not_of('0'));
	return binary;
}

long long squareAndMultiply(long long _base, long long _exponent, long long _mod)
{
	string binaryExp = decToBin(_exponent);
	string commandChain = "";
	long long result = 1;
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

bool millerRabin(long long _s,long long _n, long long _d, long long _x0)
{
	
	long long xi = 0;
	long long xIMinus1 = _x0;

	for (long long i = 1; i <= _s; i++)
	{
		xi = (xIMinus1 * xIMinus1) % _n;
		if (xi == 1 && xIMinus1 != 1 && xIMinus1 != (_n - 1)) return true;
	}
	if (xi != 1) return true;

	return false;
}


int main()
{
	srand(time(NULL));
	
	long long a = 0;
	long long d = 0;
	long long n = 11;
	long long k = 5;
	long long s = 0;
	long long x0 = 0;
	
	bool isPrime = false; 
	
	cout << "Provide n to Test:" <<endl;
	cout << "n= ";
	cin >> n;

	
	d = n - 1;
	while (d % 2 == 0)
	{
		d /= 2;
		s++;
	}

	for (long long i = 0; i < k; i++)
	{
		while (a < 2)
		{
			a = rand() % (n - 2);
		}
		x0 = squareAndMultiply(a, d, n) % n;
		isPrime = !millerRabin(s, n, d, x0);
		if (!isPrime) break;
	}

	if (isPrime) cout << n << " is very likely to be a Prime" << endl;
	else cout << n << " is not a Prime" << endl;

	return 0;
}
