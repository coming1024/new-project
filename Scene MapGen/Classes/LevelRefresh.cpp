#if true

/*
	Program LevelRefresh 关卡刷新
	File version 1
	TC202006192111
	ERR=ETH (P.Q.)
*/

#include "cocos2d.h"
#include "LevelEnv.h"

USING_NS_CC;

class LevelRefresh : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(LevelRefresh);
};

Scene* LevelRefresh::createScene()
{
	return LevelRefresh::create();
}

bool LevelRefresh::init()
{
	if (!Scene::init()) return false;
	Director::getInstance()->replaceScene(LevelEnv::createScene());
}

/*
	Program LevelRefresh 关卡刷新
	End
*/

#endif