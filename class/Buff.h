#pragma once
#ifndef __Buff_h__
#define __Buff_h__
#include"cocos2d.h"
USING_NS_CC;
class Buff :public cocos2d::Sprite
{
public:
	static Buff* creat(SpriteFrameCache* cache, char* s);
};
#endif
