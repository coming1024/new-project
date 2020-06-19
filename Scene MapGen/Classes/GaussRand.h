#if true

/*
	Header GaussRand 正态分布随机
	File version 1
	TC202006171426
	https://www.cnblogs.com/yeahgis/archive/2012/07/13/2590485.html
*/

#pragma once
#include <stdlib.h>
#include <math.h>

namespace MGM
{
	double GaussRand();
	double FixedGaussRand(double Expt, double Vari);
}

/*
	Header GaussRand 正态分布随机
	End
*/

#endif