#include <iostream>

int advancedEuklid(int _a0, int _a1)
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

	std::cout<<"aN-1=" << aIMinus1 << "\nxN-1=" << xIMinus1 << "\nyN-1=" << yIMinus1 << std::endl;

	return aIMinus1;
}

int main()
{
	advancedEuklid(93, 42);
	advancedEuklid(5666, 4453);
	return 0;
}