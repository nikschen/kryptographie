#include <iostream>

using std::cout;
using std::endl;

struct SPoint {
	int m_x;
	int m_y;

	
	bool operator==(const SPoint& p) const
	{
		return (m_x == p.m_x && m_y == p.m_y);
	}
	bool operator!=(const SPoint& p) const
	{
		return (m_x != p.m_x || m_y != p.m_y);
	}
};

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

	return xIMinus1;
}

int calculateM(SPoint _P, SPoint _Q, int _a, int _p)
{
	int m = 0;

	if (_P == _Q)
	{
		int nominator = 3 * _P.m_x * _P.m_x + _a;
		int denominator = 2 * _P.m_y;
		while (denominator < 0) denominator += _p;
		int inverseDenominator = advancedGGT(denominator, _p);
		while (nominator < 0) nominator += _p;
		while (inverseDenominator < 0) inverseDenominator += _p;
		m = (nominator * inverseDenominator)%_p;
	}
	else
	{
		int nominator = _Q.m_y - _P.m_y;
		int denominator = _Q.m_x - _P.m_x;
		while (denominator < 0) denominator += _p;
		int inverseDenominator = advancedGGT(denominator, _p);
		while (nominator < 0) nominator += _p;
		while (inverseDenominator < 0) inverseDenominator += _p;
		m = (nominator * inverseDenominator) % _p;
	}
	while (m < 0) m += _p;
	return m;
};

SPoint pointMultiplication(SPoint _P, SPoint _Q, int _d, int _p, int _a, int _b)
{
	SPoint R{ 0,0 };
	int m = calculateM(_P, _Q, _a, _p);
	int x = (m * m - _P.m_x - _Q.m_x)%_p;
	while (x < 0) x += _p;
	R.m_x = x % _p;
	int y = (m * (_P.m_x - R.m_x) - _P.m_y) % _p;
	while (y < 0) y += _p;
	R.m_y = y % _p;

	return R;
};

int main()
{
	int d=1;
	int p=17;
	SPoint originalP{ 5,1 };
	SPoint P{5,1};
	SPoint Q{5,1};
	SPoint R{0,0};
	int a=2;
	int b=2;

	while (originalP.m_x != R.m_x)
	{
		R=pointMultiplication(P, Q, d, p, a, b);
		cout << "R"<<d<<"=(" << R.m_x << "," << R.m_y << ")"<<endl;
		d++;
		P = R;
	}
	return 0;
}