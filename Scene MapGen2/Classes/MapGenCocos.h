#if true

/*
	Program MapGenCocos 地图生成Cocos版
	File version alpha 0.7
	TC202006201600
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
#pragma warning(suppress:4996) //shut up
		CCArray* Arry_Bodr;
#pragma warning(suppress:4996) //shut up
		CCArray* Arry_Star;
#pragma warning(suppress:4996) //shut up
		CCArray* Arry_Exit;
#pragma warning(suppress:4996) //shut up
		CCArray* Arry_Obst;
#pragma warning(suppress:4996) //shut up
		CCArray* Arry_Boxx;
		Sprite* BackInstantiate(unsigned int cvt, unsigned int chr);
		Node* TileInstantiate(unsigned int cvt, unsigned int chr);
		Node* MapInstantiate(void);
	};
}

/*
	Program MapGenCocos 地图生成Cocos版
	End
*/

#endif
