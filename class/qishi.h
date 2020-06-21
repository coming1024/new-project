#pragma once
#ifndef __qishi_h__
#define __qishi_h__
#include<iostream>
#include"math.h"
#include"cocos2d.h"
#include<vector>
#include"hero.h"
#include"equipment.h"
USING_NS_CC;
class qishi :public hero
{
public:
	static qishi* create(SpriteFrameCache* cache, char* s);
	//ͨ��player->heromove()������Ӣ���ƶ�;
	virtual bool heroMove(EventKeyboard::KeyCode keycode, Event* event);
	virtual bool heroStopMove(EventKeyboard::KeyCode keycode, Event* event);

	virtual bool commonAttack(Touch* pTouch, Event* pEvent);
	virtual bool stopcommonAttack(Touch* tTouch, Event* eEvent);
	void setWalkFalse();
	CCArray* _pt_bullets;
};
#endif

