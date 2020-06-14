#pragma once
#ifndef __Prop_h__
#define __Prop_h__
#include<cocos2d.h>
USING_NS_CC;
class Prop: public Sprite 
{
public:
	static Prop* create(int,int, SpriteFrame*);
	int getAddNum();
	void setAddNum(int);
	int getType();
	void setType(int);
private:
	int _type;
	int _addNum;
};
#endif

