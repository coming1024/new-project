#if true

/*
	Program MapGenCocos 地图生成Cocos版
	File version alpha 0.5
	TC202006192028
	ERR=ETH (P.Q.)
*/

#include "MapGenCocos.h"

namespace MGM
{
	//constructor | 构造函数
	Cmap::Cmap(unsigned int svt, unsigned int shr) : Gmap(svt, shr)
		///Explicitly call the parent constructor
		///显式调用父类构造函数
	{

	}

	//clone constructor | 复制构造函数
	Cmap::Cmap(Cmap& clone) : Gmap(clone)
		///Explicitly call the parent constructor
		///显式调用父类构造函数
	{

	}

	//destructor | 析构函数
	Cmap::~Cmap()
		///🏃卡其脱离太
		///Mono Mono Yi
	{

	}

	//generate map | 生成地图
	bool Cmap::GenerateMap(unsigned int cst, unsigned int ced, unsigned int cob, unsigned int cbx, double rst, double red)
		///Encapsulated map generation, generates 'cst' starts, 'ced' exits, 'cob' obstacles, 'cbx' boxes, start generation range 'rst', 0.4 by default, exit generation range 'red', 0.8 by default
		///封装的地图生成，生成'cst'个入口，'ced'个出口，'cob'个障碍，'cbx'个盒子，入口生成范围'rst'默认0.4，出口生成范围'red'默认0.8
	{
		int Star_Attp = 100;
		int Exit_Attp = 100;
		int Obst_Attp = 1000;
		int Boxx_Attp = 1000;
		for (unsigned int num = cst; num && Star_Attp > 0; Star_Attp--)
			if (GenerateTile(tile::start, 1, rst)) num--;
		for (unsigned int num = ced; num && Exit_Attp > 0; Exit_Attp--)
			if (GenerateTile(tile::end, 2, red)) num--;
		for (unsigned int num = cob; num && Obst_Attp > 0; Obst_Attp--)
			if (GenerateTile(tile::obstacle, 0)) num--;
		for (unsigned int num = cbx; num && Boxx_Attp > 0; Boxx_Attp--)
			if (GenerateTile(tile::box, 0)) num--;
		return Star_Attp && Exit_Attp && Obst_Attp && Boxx_Attp;
	}

	//instantiate background | 实例化背景
	Sprite* Cmap::BackInstantiate(unsigned int cvt, unsigned int chr)
		///Instantiate tile background at 'cvt,chr'(vertical,horizontal)
		///实例化坐标为'cvt,chr'(垂直,水平)的方块的背景
	{
		char texture[256] = { 0 };
		Sprite* tile = Sprite::create();
		tile->setAnchorPoint(Vec2(0, 0));
		tile->setPosition(Vec2((float)chr * 64, -(float)cvt * 64));
		switch (GetTile(cvt, chr))
		{
		case tile::empty:
		case tile::obstacle:
		case tile::box:
		{
			sprintf(texture, "RH_Environment/SoulForest/empty_%d.png", rand() % 1);
			tile->setTexture(texture);
			break;
		}
		case tile::start:
		{
			sprintf(texture, "RH_Environment/SoulForest/start_%d.png", rand() % 1);
			tile->setTexture(texture);
			break;
		}
		case tile::end:
		{
			sprintf(texture, "RH_Environment/SoulForest/end_%d.png", rand() % 1);
			tile->setTexture(texture);
			break;
		}
		case tile::border:
		default:
		{
			tile = nullptr;
			break;
		}
		}
		return tile;
	}

	//instantiate tile | 实例化方块
	Sprite* Cmap::TileInstantiate(unsigned int cvt, unsigned int chr)
		///Instantiate tile at 'cvt,chr'(vertical,horizontal)
		///实例化坐标为'cvt,chr'(垂直,水平)的方块
	{
		char texture[256] = { 0 };
		Sprite* tile = Sprite::create();
		tile->setAnchorPoint(Vec2(0, 0));
		tile->setPosition(Vec2((float)chr * 64, -(float)cvt * 64));
		switch (GetTile(cvt, chr))
		{
		case tile::border:
		{
			sprintf(texture, "RH_Environment/SoulForest/border_%db.png", rand() % 1);
			tile->setTexture(texture);
			PhysicsBody* rigid = PhysicsBody::createBox(Size(64, 64), PhysicsMaterial(0.1f, 0.5f, 0.5f));
			rigid->setDynamic(false);
			tile->addComponent(rigid);
			break;
		}
		case tile::obstacle:
		{
			sprintf(texture, "RH_Environment/SoulForest/border_%db.png", rand() % 1);
			tile->setTexture(texture);
			PhysicsBody* rigid = PhysicsBody::createBox(Size(64, 64), PhysicsMaterial(0.1f, 0.5f, 0.5f));
			rigid->setDynamic(false);
			tile->addComponent(rigid);
			break;
		}
		case tile::box:
		{
			sprintf(texture, "RH_Environment/SoulForest/border_%db.png", rand() % 1);
			tile->setTexture(texture);
			PhysicsBody* rigid = PhysicsBody::createBox(Size(64, 64), PhysicsMaterial(0.1f, 0.5f, 0.5f));
			rigid->setDynamic(false);
			tile->addComponent(rigid);
			break;
		}
		case tile::empty:
		case tile::start:
		case tile::end:
		default:
		{
			tile = nullptr;
			break;
		}
		}
		return tile;
	}

	//instantiate foreground | 实例化前景
	Sprite* Cmap::ForeInstantiate(unsigned int cvt, unsigned int chr)
		///Instantiate tile background at 'cvt,chr'(vertical,horizontal)
		///实例化坐标为'cvt,chr'(垂直,水平)的方块的前景
	{
		char texture[256] = { 0 };
		Sprite* tile = Sprite::create();
		tile->setAnchorPoint(Vec2(-0.5, -0.5));
		tile->setPosition(Vec2((float)chr * 64, -(float)cvt * 64));
		switch (GetTile(cvt, chr))
		{
		case tile::border:
		{
			sprintf(texture, "RH_Environment/SoulForest/border_%d.png", rand() % 1);
			tile->setTexture(texture);
			break;
		}
		case tile::obstacle:
		{
			sprintf(texture, "RH_Environment/SoulForest/border_%d.png", rand() % 1);
			tile->setTexture(texture);
			break;
		}
		case tile::box:
		{
			sprintf(texture, "RH_Environment/SoulForest/border_%d.png", rand() % 1);
			tile->setTexture(texture);
			break;
		}
		case tile::empty:
		case tile::start:
		case tile::end:
		default:
		{
			tile = nullptr;
			break;
		}
		}
		return tile;
	}
}

/*
	Program MapGenCocos 地图生成Cocos版
	End
*/

#endif
