#if true

/*
	Program MapGenCocos 地图生成Cocos版
	File version alpha 0.7
	TC202006201600
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
		Arry_Bodr = CCArray::create();
		CC_SAFE_RETAIN(Arry_Bodr);
		Arry_Star = CCArray::create();
		CC_SAFE_RETAIN(Arry_Star);
		Arry_Exit = CCArray::create();
		CC_SAFE_RETAIN(Arry_Exit);
		Arry_Obst = CCArray::create();
		CC_SAFE_RETAIN(Arry_Obst);
		Arry_Boxx = CCArray::create();
		CC_SAFE_RETAIN(Arry_Boxx);
	}

	//clone constructor | 复制构造函数
	Cmap::Cmap(Cmap& clone) : Gmap(clone)
		///Explicitly call the parent constructor
		///显式调用父类构造函数
	{
		Arry_Bodr = CCArray::create();
		CC_SAFE_RETAIN(Arry_Bodr);
		Arry_Bodr = clone.Arry_Bodr; //并不确定这样用没有问题，待测试，尽量不要使用复制构造
		Arry_Star = CCArray::create();
		CC_SAFE_RETAIN(Arry_Star);
		Arry_Star = clone.Arry_Star;
		Arry_Exit = CCArray::create();
		CC_SAFE_RETAIN(Arry_Exit);
		Arry_Exit = clone.Arry_Exit;
		Arry_Obst = CCArray::create();
		CC_SAFE_RETAIN(Arry_Obst);
		Arry_Obst = clone.Arry_Obst;
		Arry_Boxx = CCArray::create();
		CC_SAFE_RETAIN(Arry_Boxx);
		Arry_Boxx = clone.Arry_Boxx;
	}

	//destructor | 析构函数
	Cmap::~Cmap()
		///🏃卡其脱离太
		///Mono Mono Yi
	{
		//可能需要释放array？
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
		if (GetTile(cvt, chr) != tile::border &&
			GetTile(cvt, chr) != tile::empty &&
			GetTile(cvt, chr) != tile::start &&
			GetTile(cvt, chr) != tile::end &&
			GetTile(cvt, chr) != tile::obstacle &&
			GetTile(cvt, chr) != tile::box)
			return nullptr;
		Sprite* back = Sprite::create();
		back->setAnchorPoint(Vec2(0, 0));
		back->setPosition(Vec2((float)chr * 64, -(float)cvt * 64)); //!64使用
		unsigned int type;
		char texture[256] = { 0 };
		switch (GetTile(cvt, chr))
		{
		case tile::border:
		case tile::empty:
		case tile::obstacle:
		case tile::box:
			type = rand() % 4;
			sprintf(texture, "RH_Environment/SoulForest/empty_%d.png", type);
			back->setTexture(texture);
			break;
		case tile::start:
			type = rand() % 1;
			sprintf(texture, "RH_Environment/SoulForest/start_%d.png", type);
			back->setTexture(texture);
			Arry_Star->addObject(back);
			break;
		case tile::end:
			type = rand() % 1;
			sprintf(texture, "RH_Environment/SoulForest/end_%d.png", type);
			back->setTexture(texture);
			Arry_Exit->addObject(back);
			break;
		}
		return back;
	}

	//instantiate tile | 实例化方块
	Node* Cmap::TileInstantiate(unsigned int cvt, unsigned int chr)
		///Instantiate tile at 'cvt,chr'(vertical,horizontal)
		///实例化坐标为'cvt,chr'(垂直,水平)的方块
	{
		if (GetTile(cvt, chr) != tile::border &&
			GetTile(cvt, chr) != tile::obstacle &&
			GetTile(cvt, chr) != tile::box)
			return nullptr;
		Node* tile = Node::create();
		Sprite* body = Sprite::create(); //方块本体
		body->setAnchorPoint(Vec2(0, 0));
		body->setPosition(Vec2((float)chr * 64, -(float)cvt * 64)); //!64使用
		Sprite* mask = Sprite::create(); //方块遮挡层---原来的前景
		mask->setAnchorPoint(Vec2(-0.5, -0.5));
		mask->setPosition(body->getPosition());
		mask->setLocalZOrder(2); //设置最优先渲染层
		PhysicsBody* rigid = PhysicsBody::createBox(Size(64, 64), PhysicsMaterial(0.1f, 0.5f, 0.5f)); //方块物理
		rigid->setDynamic(false);
		body->addComponent(rigid);
		tile->addChild(body);
		tile->addChild(mask);
		unsigned int type;
		char texture[256] = { 0 };
		switch (GetTile(cvt, chr))
		{
		case tile::border:
			type = rand() % 2;
			sprintf(texture, "RH_Environment/SoulForest/border_%db.png", type);
			body->setTexture(texture);
			sprintf(texture, "RH_Environment/SoulForest/border_%d.png", type);
			mask->setTexture(texture);
			Arry_Bodr->addObject(body);
			break;
		case tile::obstacle:
			type = rand() % 2;
			sprintf(texture, "RH_Environment/SoulForest/border_%db.png", type);
			body->setTexture(texture);
			sprintf(texture, "RH_Environment/SoulForest/border_%d.png", type);
			mask->setTexture(texture);
			Arry_Obst->addObject(body);
			break;
		case tile::box:
			type = rand() % 1;
			sprintf(texture, "RH_Environment/SoulForest/box_%db.png", type);
			body->setTexture(texture);
			sprintf(texture, "RH_Environment/SoulForest/box_%d.png", type);
			mask->setTexture(texture);
			Arry_Boxx->addObject(body);
			break;
		}
		return tile;
	}

	//instantiate map | 实例化地图
	Node* Cmap::MapInstantiate(void)
		///Instantiate the map, return the node of all map objects
		///实例化地图，返回所有地图对象所在的节点
	{
		Node* envi = Node::create();
		for (unsigned int vcot = 0; vcot <= GetSize().front() + 1; vcot++)
			for (unsigned int rev_hcot = 0; rev_hcot <= GetSize().back() + 1; rev_hcot++)
			{
				Sprite* back = nullptr;
				Node* tile = nullptr;
				back = BackInstantiate(vcot, GetSize().back() + 1 - rev_hcot);
				tile = TileInstantiate(vcot, GetSize().back() + 1 - rev_hcot);
				if (back != nullptr) envi->addChild(back);
				if (tile != nullptr) envi->addChild(tile);
			}
		return envi;
	}
}

/*
	Program MapGenCocos 地图生成Cocos版
	End
*/

#endif
