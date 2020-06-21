#ifndef __Chest_h__
#define __Chest_h__
#pragma once
#include<cocos2d.h>
#include"equipment.h"
USING_NS_CC;
class Chest :public Sprite
{
public:
	static Chest* creat(SpriteFrameCache* cache, char* s, Vector<SpriteFrame*>, equipment*);
	Vector<SpriteFrame*> vector_frame;
	equipment* getEquipment();
private:
	equipment* includeEquip;

};
#endif
