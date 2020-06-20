#if true

/*
	Program MapGen 地图生成合并版
	File version alpha 0.5
	TC202006192028
	ERR=ETH (P.Q.)
*/

#pragma once
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using std::vector;
namespace MGM
{
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
		obstacle = 3,
		box = 4
	};
	private:
		unsigned int Size_Vert;
		unsigned int Size_Hori;
		tile* Smap;
		vector<vector<unsigned int>> Cord_Star;
		vector<vector<unsigned int>> Cord_Exit;
		vector<vector<unsigned int>> Cord_Obst;
		vector<vector<unsigned int>> Cord_Boxx;
		vector<unsigned int> RandCoord(unsigned int rvt, unsigned int rhr, int mode);
		vector<unsigned int> RandCoord(void);
	public:
		Gmap(unsigned int svt, unsigned int shr);
		Gmap(Gmap& clone);
		~Gmap();
		vector<unsigned int> GetSize(void);
		tile GetTile(unsigned int cvt, unsigned int chr);
		tile SetTile(unsigned int cvt, unsigned int chr, tile tl);
		void GenInit(void);
		void GenStar(unsigned int num, double range, int maxatt = 100);
		void GenExit(unsigned int num, double range, int maxatt = 100);
		void GenObst(unsigned int num, int maxatt = 1000);
		void GenBoxx(unsigned int num, int maxatt = 1000);
		bool GenerateTile(tile tl, int mode, double range = 0);
		void PrintMap(std::ostream& os = std::cout);
	};
}

/*
	Program MapGen 地图生成合并版
	End
*/

#endif