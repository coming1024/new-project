#if true

/*
	Program LevelEnv 关卡场景
	File version alpha 0.2
	TC202006191617
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
	const char* AudioSwitch;
	MGM::Gmap GenerateMap(unsigned int svt, unsigned int shr, unsigned int cst = 0, unsigned int ced = 0, unsigned int cob = 0, unsigned int cbx = 0);
	void TileInstantiate(MGM::Gmap &map, Node* mnode, unsigned int cvt, unsigned int chr);
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