#if false

/*
	Program GaussRand 正态分布随机测试
	File version 1
	TC202006171426
	ERR=ETH (P.Q.)
*/

#include <iostream>
#include <math.h>
#include "GaussRand.h"

int main(void)
{
	int aq = 0, as = 0, ad = 0;
	while (true)
	{
		double a = FixedGaussRand(0, 1);
		aq++;
		if (abs(a) < 2) as++;
		if (abs(a) < 0.6) ad++;
		std::cout << as << "/" << aq << "\t" << (double)as / aq << std::endl;
		std::cout << "\t" << ad << "/" << aq << "\t" << (double)ad / aq << std::endl;
		system("pause>nul");
	}
	return 0;
}

/*
	Program GaussRand 正态分布随机测试
	End
*/

#endif