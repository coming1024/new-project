#if true

/*
	Program LevelEnv 关卡场景
	File version alpha 0.1
	TC202006191312
	ERR=ETH (P.Q.)
*/

#pragma once
#include "cocos2d.h"
#include <ctime>
#include "MapGenMerge.h"

class LevelEnv : public cocos2d::Scene
{
private:
	cocos2d::Size VisibleSize;
	cocos2d::Vec2 Origin;
	const char* Audio;
	void TileInstantiate(MGM::Gmap &map, unsigned int cvt, unsigned int chr, Node* mnode);
public:
	LevelEnv();
	~LevelEnv();
	static cocos2d::Scene* createScene(); //创建用
	virtual bool init();
	CREATE_FUNC(LevelEnv); //创建用，必要
};

/*
	Program LevelEnv 关卡场景
	End
*/

#endif