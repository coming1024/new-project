#if true

/*
	Program LevelEnv 关卡场景
	File version alpha 0.4
	TC202006201042
	ERR=ETH (P.Q.)
*/

#pragma once
#include "cocos2d.h"
#include <ctime>
#include "MapGenMerge.h"
#include "MapGenCocos.h"

class LevelEnv : public cocos2d::Scene
{
private:
	cocos2d::Size VisibleSize;
	cocos2d::Vec2 Origin;
	const char* Audio;
	const char* AudioSwitch;
public:
	LevelEnv();
	~LevelEnv();
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(LevelEnv);
};

/*
	Program LevelEnv 关卡场景
	End
*/

#endif