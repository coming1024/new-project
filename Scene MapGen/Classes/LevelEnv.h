#if true

/*
	Program LevelEnv �ؿ�����
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
	static cocos2d::Scene* createScene(); //������
	virtual bool init();
	CREATE_FUNC(LevelEnv); //�����ã���Ҫ
};

/*
	Program LevelEnv �ؿ�����
	End
*/

#endif