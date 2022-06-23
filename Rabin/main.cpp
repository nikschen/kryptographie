#include <bitset>
#include <iostream>
#include <string>

using std::string;
using std::cout;
using std::endl;

long advancedGGT(long _a0, long _a1)
{
	long xIMinus1 = 1;
	long xI = 0;
	long yIMinus1 = 0;
	long yI = 1;
	long aIMinus1 = _a0;
	long aI = _a1;
	long qI = 0;

	do
	{
		long aIMinus1Temp = aIMinus1;
		long xIMinus1Temp = xIMinus1;
		long yIMinus1Temp = yIMinus1;
		aIMinus1 = aI;
		xIMinus1 = xI;
		yIMinus1 = yI;


		qI = aIMinus1Temp / aI;
		aI = aIMinus1Temp - qI * aI;
		xI = xIMinus1Temp - qI * xI;
		yI = yIMinus1Temp - qI * yI;


	} while (aI != 0);

	return xIMinus1;
}

string decToBin(long _dec)
{
	string binary = std::bitset<16>(_dec).to_string();
	binary.erase(0, binary.find_first_not_of('0'));
	return binary;
}

long squareAndMultiply(long _base, long _exponent, long _mod)
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

long encrypt(long _message, long _mod)
{
	return squareAndMultiply(_message, 2, _mod);
}

void decrypt(long* _results, long _chiffre)
{

}

long main()
{
	long results[4];
	long p = 7;
	long q = 11;
	long n = p * q;
	long message = 40;
	long c = encrypt(message, n);
	cout << "c=" << c << endl;
	long mpExponent = (p + 1) * advancedGGT(4, p)%p;
	long mqExponent = (q + 1) * advancedGGT(4, q)%q;
	long mp = squareAndMultiply(c, mpExponent, p);
	cout << "mp=" << mp << endl;
	long mq = squareAndMultiply(c, mqExponent, q);
	cout << "mq=" << mq << endl;
	long yp = advancedGGT(p, q);
	long yq = advancedGGT(q, p);
	cout << "yp=" << yp << endl;
	cout << "yq=" << yq << endl;
					 // 2    7  4    2    11  2
	long dividendOfR = yp * p * mq + yq * q * mp;
	while (dividendOfR < 0) dividendOfR += n;
	long r = dividendOfR % n;
	long minusR = n - r;
	long dividendOfS = yp * p * mq - yq * q * mp;
	while (dividendOfS < 0) dividendOfS += n;
	long s = dividendOfS % n;
	long minusS = n - s;
	cout << "r=" << r << endl;
	cout << "-r=" << minusR << endl;
	cout << "s=" << s << endl;
	cout << "-s=" << minusS << endl;

	return 0;
}