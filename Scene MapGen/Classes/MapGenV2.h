#if false
#pragma once

/*
	Program MapGen ��ͼ���ɲ���
	File version alpha 0.2
	TC202006171031
	ERR=ETH (P.Q.)
*/

/*
	Include
*/
#include <iostream>
#include <vector>
#include <ctime>
#include <cmath>
#include <algorithm>
#include "GaussRand.h"

/*
	Declaration
*/
using std::vector;
double GaussRand();
double FixedGaussRand(double Expt, double Vari);
bool CompVec2UInt(vector<unsigned int> fw, vector<unsigned int> bk);
class Gmap
{
public: enum class tile
{
	error = -2,
	border = -1,
	empty = 0,
	start = 1,
	end = 2,
	obstacle = 3
};
private:
	unsigned int Size_Vert;
	unsigned int Size_Hori;
	tile* Smap;
	vector<vector<unsigned int>> Cord_Star;
	vector<vector<unsigned int>> Cord_Exit;
	vector<vector<unsigned int>> Cord_Obst;
	vector<unsigned int> RandCoord(unsigned int rvt, unsigned int rhr, int mode);
	vector<unsigned int> RandCoord(void);
public:
	Gmap(unsigned int svt, unsigned int shr);
	~Gmap();
	tile GetTile(unsigned int cvt, unsigned int chr);
	tile SetTile(unsigned int cvt, unsigned int chr, tile tl);
	void GenInit(void);
	void GenStar(unsigned int num, double range, int maxatt = 100);
	void GenExit(unsigned int num, double range, int maxatt = 100);
	void GenObst(unsigned int num, int maxatt = 10000);
	void PrintMap(std::ostream& os = std::cout);
};

/*
	Program MapGen ��ͼ���ɲ���
	End
*/

#endif