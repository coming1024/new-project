#pragma once
#ifndef __qishi_h__
#define __qishi_h__
#include<iostream>
#include"cocos2d.h"
#include<vector>
#include"buff.h"
#include"hero.h"
#include"equipment.h"
USING_NS_CC;
class qishi:public hero
{
public:
	static qishi* create(SpriteFrameCache* cache, char* s);
	//通过player->heromove()来调用英雄移动;
	virtual bool heroMove(EventKeyboard::KeyCode keycode, Event* event);
	virtual bool heroStopMove(EventKeyboard::KeyCode keycode, Event* event);
	
	virtual bool commonAttack(Touch* pTouch, Event* pEvent);
	virtual bool stopcommonAttack(Touch* tTouch, Event* eEvent);
	virtual bool take_buff(Buff* buff);
	virtual bool clear_buff();
	virtual void die();
	virtual void take_damage();
	virtual void die_animation();
	void setfalse();
};
#endif

