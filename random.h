#include<time.h>

class RandomNumber
{
private:
	const unsigned int maxshort = 65536u;
	const unsigned int multiplier = 1194211693u;
	const unsigned int adder = 12345u;
	unsigned int randSeed = 0;
public:
	RandomNumber()
	{
		randSeed = (unsigned int)time(0);
	}
	int Rondom(int n)
	{
		randSeed = randSeed*multiplier + adder;
		return randSeed%n;
	}
};
