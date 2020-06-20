#ifndef __Bullet_h__
#define __Bullet_h__
#pragma once
#include<cocos2d.h>
USING_NS_CC;
class Bullet :public Sprite
{
public:
	int _ATK;
	SpriteFrame* _bulletFrame;
	bool operator==(const Bullet&)const;
	static Bullet* create(int, SpriteFrame*);
	Bullet* clone();
	int getATK();
};
#endif
