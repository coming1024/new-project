#if true

/*
	Program LevelEnv 关卡场景(合并)
	File version alpha 0.51
	TC202006210106
	ERR=ETH (P.Q.)
*/

#pragma once
#include "cocos2d.h"
#include <ctime>
#include "MapGenMerge.h"
#include "MapGenCocos.h"
#include"qishi.h"
#include"Chest.h"
#include"Prop.h"
#include"HerosHomeScene.h"
#include"PauseLayer.h"

class LevelEnv : public cocos2d::Scene
{
private:
	cocos2d::Size VisibleSize;
	cocos2d::Vec2 Origin;
	const char* Audio;
	const char* AudioSwitch;
	///
	qishi* hero_qishi;
	void initDate(Node* PtMap);
	void onKeyPressed(EventKeyboard::KeyCode keycode, Event* event);
	void onKeyReleased(EventKeyboard::KeyCode keycode, Event* event);
	bool onTouchBegan(Touch* pTouch, Event* pEvent);
	void onTouchMoved(Touch* pTouch, Event* pEvent);
	void onTouchEnded(Touch* pTouch, Event* pEvent);
	void upDataHeroNature(float t);
	void upDataAddEnergy(float t);
	void upDataBABC(float t);
	bool isCollision(CCRect rect1, CCRect rect2);
	void playerAndWeaponCollision(CCArray* weaponArray1);
	void playerAndPropCollison(CCArray* propArray1);
	void playerAndChestCollison(CCArray* chestArray1);
	void obstacleAndBulletCollison(CCArray* barrierArray1, CCArray* bulletArray1);
	void BackToHerosHomeScene(cocos2d::Ref* pSender);
public:
	LevelEnv();
	~LevelEnv();
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(LevelEnv);
	MGM::Cmap* GlobalMap;
	Node* GenerateEnv(int level);
	void Trigger(Ref* pSender);
	///
	CCArray* weaponArray;
	CCArray* propArray;
	CCArray* chestArray;
	SpriteFrameCache* equipmentCache;
	SpriteFrameCache* bulletCache;
	SpriteFrameCache* propCache;
	SpriteFrameCache* chestCache;
	SpriteFrameCache* heroCache;
};

/*
	Program LevelEnv 关卡场景
	End
*/

#endif