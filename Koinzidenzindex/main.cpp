#include <iostream>
#include <map>
#include <string>

std::map<char, int> letterFrequencyMap;

void getLetterFrequencies(std::string _text)
{
	for (char& letter : _text)
	{
		letterFrequencyMap[letter] += 1;
	}
}

float getCoincidenceIndex(std::string _text)
{
	int frequencySum = 0;
	for (char c = 'A'; c < ('Z' + 1); c++)
	{
		frequencySum += letterFrequencyMap[c] * (letterFrequencyMap[c] - 1);
	}

	return (frequencySum / (float)((_text.length() * (_text.length() - 1))));
}

int main()
{
	for (char i = 'A'; i < ('Z' + 1); i++)
	{
		letterFrequencyMap.insert(std::pair<char, int>(i,0));
	}
	std::string text = "HELLOWORLD";
	getLetterFrequencies(text);
	for (auto const& [key, val] : letterFrequencyMap)
	{
		std::cout << key << ": " << val << std::endl;
	}
	std::cout<< "Koinzidenzindex I=" << getCoincidenceIndex(text)<< " = " << getCoincidenceIndex(text)*100 << "%" << std::endl;
	
	return 0;
}