#if true

/*
	Program LevelEnv 关卡场景
	File version alpha 0.1
	TC202006191312
	ERR=ETH (P.Q.)
*/

#include "LevelEnv.h"
#include "SimpleAudioEngine.h"
#include "MapGenMerge.h"

USING_NS_CC;

LevelEnv::LevelEnv()
{
	VisibleSize = Director::getInstance()->getVisibleSize();
	Origin = Director::getInstance()->getVisibleOrigin();
	Audio = "Astrodophin.mp3"; //sry的滑稽
}

LevelEnv::~LevelEnv()
{
	//doing nothing
}

Scene* LevelEnv::createScene()
{
	return LevelEnv::create();
}

bool LevelEnv::init()
{
	if (!Scene::init()) return false;

	CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(Audio, true);

	srand((unsigned int)time(NULL)); //初始化随机数种子

	auto title = Label::createWithTTF("Level Environment Preview", "fonts/Marker Felt.ttf", 24);
	if (title != nullptr)
	{
		title->setPosition(Vec2(Origin.x + VisibleSize.width / 2, Origin.y + VisibleSize.height - title->getContentSize().height));
		this->addChild(title, 1);
	}



	unsigned int Size_Vert = 25;
	unsigned int Size_Hori = 40;
	MGM::Gmap Tmap(Size_Vert, Size_Hori);
	Tmap.GenStar(1, 0.4);
	Tmap.GenExit(3, 0.8);
	Tmap.GenObst(100);

	auto myNode = Node::create();
	myNode->setPosition(Vec2(100, VisibleSize.height-100));

	for (unsigned int vcot = 0; vcot <= Size_Vert + 1; vcot++)
		for (unsigned int hcot = 0; hcot <= Size_Hori + 1; hcot++)
			TileInstantiate(Tmap, vcot, hcot, myNode);

	addChild(myNode);


	return true;
}

void LevelEnv::TileInstantiate(MGM::Gmap &map, unsigned int cvt, unsigned int chr, Node* mnode)
{
	Sprite* tile = Sprite::create();
	switch (map.GetTile(cvt, chr))
	{
	case MGM::Gmap::tile::border:
		tile->setTexture("border.png");
		if(false){
			PhysicsBody* rigid = PhysicsBody::createBox(Size(65.0f, 81.0f), PhysicsMaterial(0.1f, 1.0f, 0.0f));
			rigid->setDynamic(false);
			tile->addComponent(rigid); //为方块添加物理碰撞，待完善
		}
		break;
	case MGM::Gmap::tile::empty:
		tile->setTexture("empty.png");
		break;
	case MGM::Gmap::tile::start:
		tile->setTexture("start.png");
		break;
	case MGM::Gmap::tile::end:
		tile->setTexture("exit.png");
		break;
	case MGM::Gmap::tile::obstacle:
		tile->setTexture("obstacle.png");
		if (false) {
			PhysicsBody* rigid = PhysicsBody::createBox(Size(65.0f, 81.0f), PhysicsMaterial(0.1f, 1.0f, 0.0f));
			rigid->setDynamic(false);
			tile->addComponent(rigid); //为方块添加物理碰撞，待完善
		}
		break;
	default:
		break;
	}
	tile->setPosition(Vec2(chr * 16, -(int)(cvt * 16)));
	mnode->addChild(tile);
}

/*
	Program LevelEnv 关卡场景
	End
*/

#endif