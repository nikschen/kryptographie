#include <bitset>
#include <iostream>
#include <string>


using std::string; 
using std::to_string;
using std::cout;
using std::endl;

int currentRound = 0;

int shiftingDistance[16] =
{
	1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1
};

#pragma region Boxes


std::string input64 = "0000000100100011010001010110011110001001101010111100110111101111";
std::string key64 = "0001001100110100010101110111100110011011101111001101111111110001";


int initialPermutation[64] = {
	58,50,42,34,26,18,10,2,
	60,52,44,36,28,20,12,4,
	62,54,46,38,30,22,14,6,
	64,56,48,40,32,24,16,8,
	57,49,41,33,25,17,9,1,
	59,51,43,35,27,19,11,3,
	61,53,45,37,29,21,13,5,
	63,55,47,39,31,23,15,7
};

int keyPermutation[56] = {
	57,49,41,33,25,17,9,
	1,58,50,42,34,26,18,
	10,2,59,51,43,35,27,
	19,11,3,60,52,44,36,
	63,55,47,39,31,23,15,
	7,62,54,46,38,30,22,
	14,6,61,53,45,37,29,
	21,13,5,28,20,12,4
};

int keyCompression[48] = {
	14,17,11,24,1,5,
	3,28,15,6,21,10,
	23,19,12,4,26,8,
	16,7,27,20,13,2,
	41,52,31,37,47,55,
	30,40,51,45,33,48,
	44,49,39,56,34,53,
	46,42,50,36,29,32
};

int finalPermutation[64] = {
	40,8,48,16,56,24,64,32,
	39,7,47,15,55,23,63,31,
	38,6,46,14,54,22,62,30,
	37,5,45,13,53,21,61,29,
	36,4,44,12,52,20,60,28,
	35,3,43,11,51,19,59,27,
	34,2,42,10,50,18,58,26,
	33,1,41,9,49,17,57,25
};

int expansionMatrix[48] = {
	31,0,1,2,3,4,
	3,4,5,6,7,8,
	7,8,9,10,11,12,
	11,12,13,14,15,16,
	15,16,17,18,19,20,
	19,20,21,22,23,24,
	23,24,25,26,27,28,
	27,28,29,30,31,0
};

int pBoxPermutation[32] = {
	16,7,20,21,29,12,28,17,
	1,15,23,26,5,18,31,10,
	2,8,24,14,32,27,3,9,
	19,13,30,6,22,11,4,25
};

int substitionBoxes[8][4][16] =
{ {
	14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7,
	0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8,
	4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0,
	15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13
},
{
	15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10,
	3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5,
	0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15,
	13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9
},
{
	10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8,
	13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1,
	13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7,
	1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12
},
{
	7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15,
	13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9,
	10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4,
	3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14
},
{
	2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9,
	14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6,
	4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14,
	11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3
},
{
	12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11,
	10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8,
	9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6,
	4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13
},
{
	4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1,
	13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6,
	1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2,
	6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12
},
{
	13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7,
	1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2,
	7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8,
	2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11
} 
};
#pragma endregion

void output(string _variableName, string _outputString)
{
	string output = "";
	for (int i = 0; i < _outputString.length(); i++)
	{
		if (i % 8 == 0)output += " ";
		output += _outputString[i];
	}

	cout << _variableName << ": " << output << endl;
}

string inputPermutation(string _testVectorX64)
{
	string resultVector64 = "";
	for (int idx=0;idx<_testVectorX64.length();idx++)
	{
		resultVector64 += _testVectorX64[initialPermutation[idx]-1];
	}
	return resultVector64;
}
string endPermutation(string _testVectorX64)
{
	string resultVector64 = "";
	for (int idx = 0; idx < _testVectorX64.length(); idx++)
	{
		resultVector64 += _testVectorX64[finalPermutation[idx] - 1];
	}
	return resultVector64;
}
void splitInLAndR32(string _testVectorX64, string* _ptestVectorL32, string* _ptestVectorR32)
{
	*_ptestVectorL32 = _testVectorX64.substr(0,32);
	*_ptestVectorR32 = _testVectorX64.substr(32,32);
}
void expansionPermutation(string* _vectorR32)
{
	string resultVector = "";
	string fourBitBlocks[8];
	string rightVector = *_vectorR32;
	for (int idx=0; idx<8;idx++)
	{
		fourBitBlocks[idx] = rightVector.substr(idx * 4, 4);
		int leftNeighbourIdx = idx * 4 - 1;
		int rightNeighbourIdx = idx * 4 + 4;
		if (leftNeighbourIdx < 0) leftNeighbourIdx = 31;
		if (rightNeighbourIdx > 31) rightNeighbourIdx = 0;
		fourBitBlocks[idx] = rightVector[leftNeighbourIdx] + fourBitBlocks[idx] + rightVector[rightNeighbourIdx];
	}
	for (string block : fourBitBlocks)
	{
		resultVector += block;
	}
	*_vectorR32=resultVector;
}
string key56Permutation(string _key64)
{
	string resultKey = "";
	for (int idx = 0; idx < 56; idx++)
	{
		resultKey += _key64[ keyPermutation[idx]-1];
	}
	//output("key56PermutationResult",resultKey);
	return resultKey;
}
void splitKey(string _key56, string* _pLeftKeyHalf28, string* _pRightKeyHalf28)
{
	*_pLeftKeyHalf28 = _key56.substr(0, 28);
	*_pRightKeyHalf28 = _key56.substr(28, 28);
}

void keyShift(string* _key28)
{
	string oldKey = *_key28;
	string newKey = "";
	for (int i = 0; i < oldKey.length(); i++)
	{
		int idxInOldKey = i + shiftingDistance[currentRound];
		if (idxInOldKey >= oldKey.length())
		{
			idxInOldKey= idxInOldKey-oldKey.length();
		}
		newKey += oldKey[idxInOldKey];
	}
	//output("KeyBeforeShift",oldKey);
	//output("KeyAfterShift",newKey);
	*_key28 = newKey;
	
}

void shiftKeys(string* _pLeftKeyHalf28, string* _pRightKeyHalf28)
{
	keyShift(_pLeftKeyHalf28);
	keyShift(_pRightKeyHalf28);
	currentRound += 1;
}

string keyCompressionPermutation48(string* _pLeftKeyHalf28, string* _pRightKeyHalf28)
{
	string wholeKey = *_pLeftKeyHalf28 + *_pRightKeyHalf28;
	output("whole key",wholeKey);
	string newKey = "";
	for (int idx = 0; idx < 48; idx++)
	{
		newKey += wholeKey[keyCompression[idx]-1];
	}
	//output("keyCompressionResult",newKey);

	return newKey;
}

void linkKeyWithRightHalfViaXOR(string* _rightVector48, string _currentKey)
{
	string result = "";
	string rightVectorOld = *_rightVector48;
	for (int i=0;i<48;i++)
	{
		if (rightVectorOld[i] == _currentKey[i]) result += '0';
		else result += '1';
	}
	*_rightVector48 = result;
}

string linkVectorsViaXOR(string leftVector, string rightVector)
{
	string result = "";
	for (int i = 0; i < 32; i++)
	{
		if (leftVector[i] == rightVector[i]) result += '0';
		else result += '1';
	}

	return result;
}

void splitInto6BitGroups(string _input48, string* _6BitBlockArray)
{

	for (int i = 0; i < 8; i++)
	{
		_6BitBlockArray[i] = _input48.substr(i*6, 6);
	}

}

string decToBin(int _dec)
{
	return std::bitset<4>(_dec).to_string();
}

int binToDec(string _bin)
{
	return std::stoi(_bin, nullptr, 10);
}

void sBoxSubstitution(string* _vectorR48)
{
	string _6BitBlocks[8];
	string result32 = "";
	splitInto6BitGroups(*_vectorR48, _6BitBlocks);
	for (int i = 0; i < 8; i++)
	{
		string currentBitBlock = _6BitBlocks[i];
		string rowBinary = "";
		string colBinary = "";
		rowBinary += currentBitBlock[0];
		rowBinary += currentBitBlock[5];
		colBinary += currentBitBlock.substr(1,4);
		int row = binToDec(rowBinary);
		int col = binToDec(colBinary);
		result32 += decToBin(substitionBoxes[i][row][col]);
	}

	*_vectorR48 = result32;
}

void permutationPBox(string* _vectorR32)
{
	string oldVectorR = *_vectorR32;
	string newVectorR = "";
	for (int i = 0; i < 32; i++)
	{
		newVectorR += oldVectorR[pBoxPermutation[i] - 1];
	}

	*_vectorR32 = newVectorR;
}

int main()
{
	
	//output(inputPermutation(input64));
	string test= inputPermutation(input64);
	string leftVector;
	string rightVector;
	splitInLAndR32(test, &leftVector, &rightVector);


	string permutatedKey56 = key56Permutation(key64);
	string leftKeyHalf28 = "";
	string rightKeyHalf28 = "";
	splitKey(permutatedKey56, &leftKeyHalf28, &rightKeyHalf28);


	for (int i = 0; i < 16; i++)
	{
		if (i != 0)
		{
			string leftVectorTemp = rightVector;
			rightVector = linkVectorsViaXOR(leftVector, rightVector);
			leftVector = leftVectorTemp;
		}

		shiftKeys(&leftKeyHalf28, &rightKeyHalf28);
		string currentKey=keyCompressionPermutation48(&leftKeyHalf28, &rightKeyHalf28);
		expansionPermutation(&rightVector);
		linkKeyWithRightHalfViaXOR(&rightVector, currentKey);
		sBoxSubstitution(&rightVector);
		permutationPBox(&rightVector);
		//output("leftVector",leftVector);
		//output("rightVector",rightVector);
	}

	output("endResult",endPermutation(leftVector + rightVector));

	return 0;
}