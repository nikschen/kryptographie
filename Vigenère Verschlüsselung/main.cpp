#include <iostream>
#include <string>

std::string encryptVigenere(std::string _plainText, std::string _key)
{
	std::string secretText = "";
	std::string loopedKey = ""; //key looped in _plainText length
	for (int i=0;i<_plainText.length();i++)
	{
		loopedKey += _key[i%_key.length()];
		int positionsToPush = loopedKey[i]-'A';
		char encryptedChar;
		if(_plainText[i] + positionsToPush > 'Z') //if the encrypted char is out of range
		{
			encryptedChar = _plainText[i] + positionsToPush - 26;
		}
		else
		{
			encryptedChar = _plainText[i] + positionsToPush;
		}
		
		secretText += encryptedChar;
	}
	
	return secretText;
}

int main()
{
	std::string plainText = "HELLOWORLD";
	std::cout << encryptVigenere(plainText, "KEY")<< std::endl;
	
	return 0;
}