#if true

/*
	Program LevelEnv 关卡场景
	File version alpha 0.5
	TC202006201600
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
	MGM::Cmap* GlobalMap;
	Node* GenerateEnv(int level);
	void Trigger(Ref* pSender);
};

/*
	Program LevelEnv 关卡场景
	End
*/

#endif