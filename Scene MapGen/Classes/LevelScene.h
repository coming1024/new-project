#if false

#pragma once
#ifndef __LEVELSCENE_H__
#define __LEVELSCENE_H__

#include "cocos2d.h"
#include "MapGenV2.h"

class LevelScene : public cocos2d::Scene
{
private:
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(LevelScene);
};

#endif // __LEVELSCENE_H__

#endif