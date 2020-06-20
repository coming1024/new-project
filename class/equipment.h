#ifndef __equipment_h__
#define __equipment_h__
#pragma once
#include<cocos2d.h>
#include"Bullet.h"
USING_NS_CC;
class equipment :public cocos2d::Sprite
{
public:
	int _ATK;
	int _speed;
	bool operator==(const equipment&)const;
	int _type;//为1是远程，为0是近战
	bool _isContinue;
	Vector<SpriteFrame*> vector_frame;
	Bullet* _bullet;
	int _width;
	int _hight;
	static equipment* create(int, int, int, bool, SpriteFrameCache* cache, char* s, Bullet*);
	static equipment* create(int, int, int, bool, SpriteFrameCache* cache, char* s, Vector<SpriteFrame*>, int w, int h);
	int getWidth();
	int getHight();
	bool getType();
	int getSpeed();
	int getATK();
	bool getIsContinue();
};
#endif
