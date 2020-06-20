#if true

/*
	Program MapGenCocos 地图生成Cocos版
	File version alpha 0.6
	TC202006201012
	ERR=ETH (P.Q.)
*/

#pragma once
#include "cocos2d.h"
#include "MapGenMerge.h"

using std::vector;
using namespace cocos2d;
namespace MGM
{
	class Cmap : public Gmap
	{
	private:

	public:
		Cmap(unsigned int svt, unsigned int shr);
		Cmap(Cmap& clone);
		~Cmap();
		bool Cmap::GenerateMap(unsigned int cst, unsigned int ced, unsigned int cob, unsigned int cbx, double rst = 0.4, double red = 0.8);
		Sprite* BackInstantiate(unsigned int cvt, unsigned int chr);
		Sprite* TileInstantiate(unsigned int cvt, unsigned int chr);
		Sprite* ForeInstantiate(unsigned int cvt, unsigned int chr);
		Node* MapInstantiate(int layer);
	};

}

/*
	Program MapGenCocos 地图生成Cocos版
	End
*/

#endif
