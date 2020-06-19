#if false

#include "LevelScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* LevelScene::createScene()
{
	return LevelScene::create();
}

bool LevelScene::init()
{
	if (!Scene::init()) return false;

	auto dirs = Director::getInstance();
	Size visibleSize = dirs->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto sprite1 = Sprite::create("CloseSelected.png");
	sprite1->setPosition(Vec2(100, 100));
	addChild(sprite1);

	auto myNode = Node::create();
	myNode->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));

	unsigned int Size_Vert = 25;
	unsigned int Size_Hori = 40;
	Gmap Tmap(Size_Vert, Size_Hori);
	Tmap.GenStar(1, 0.4);
	Tmap.GenExit(3, 0.8);
	Tmap.GenObst(100);
	for (unsigned int vcot = 0; vcot <= Size_Vert + 1; vcot++)
		for (unsigned int hcot = 0; hcot <= Size_Hori + 1; hcot++)
		{
			auto sprite1 = Sprite::create("CloseSelected.png");
			sprite1->setPosition(Vec2(hcot * 25, vcot * 25));
			if (Tmap.GetTile(vcot, hcot) != Gmap::tile::empty) addChild(sprite1);
		}


	addChild(myNode);

	return true;
}

#endif