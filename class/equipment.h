#ifndef __equipment_h__
#define __equipment_h__
#pragma once
#include<cocos2d.h>
USING_NS_CC;
class equipment:public cocos2d::Sprite
{
public:
	int _ATK;
	int _speed;
	bool operator==(const equipment&)const;
	int _type;//为1是远程，为0是近战
	Vector<SpriteFrame*> vector_frame,vector_frame_y;
	SpriteFrame* _bullet;
	static equipment* create(int, int, int, SpriteFrameCache* cache, char* s,SpriteFrame*);
	static equipment* create(int, int, int, SpriteFrameCache* cache, char* s, Vector<SpriteFrame*>);
};
#endif
