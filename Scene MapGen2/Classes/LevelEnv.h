#if true

/*
	Program LevelEnv 关卡场景
	File version alpha 0.3
	TC202006192221
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
#include"Monster.h"
#include"MonsterBullet.h"

class LevelEnv : public cocos2d::Scene
{
private:
	cocos2d::Size VisibleSize;
	cocos2d::Vec2 Origin;
	const char* Audio;
	const char* AudioSwitch;
	/////////////////
	Monster* monster1;
	Monster* monster2;
	MonsterBullet* monsterBu1;
	qishi* hero_qishi;
	void initDate();
	void onKeyPressed(EventKeyboard::KeyCode keycode, Event* event);
	void onKeyReleased(EventKeyboard::KeyCode keycode, Event* event);
	bool onTouchBegan(Touch* pTouch, Event* pEvent);
	void onTouchMoved(Touch* pTouch, Event* pEvent);
	void onTouchEnded(Touch* pTouch, Event* pEvent);
	void upDataHeroNature(float t);
	void upDataAddEnergy(float t);
	bool isCollision(CCRect rect1, CCRect rect2);
	void playerAndWeaponCollision(CCArray* weaponArray1);
	void playerAndPropCollison(CCArray* propArray1);
	void playerAndChestCollison(CCArray* chestArray1);
	void monsterAndPlayerCollision(CCArray* monsterArray1);
	void upDataMAPC(float t);
	void monsterAndBulletCollision(CCArray* monsterArray1, CCArray* bulletArray2);
	void upDataMABC(float t);
	void monsterAndWeaponCollision(CCArray* monsterArray1);
	void upDataMAWC(float t);
	void obstacleAndBulletCollison(CCArray* barrierArray1, CCArray* bulletArray1);
	void upDataOABC(float t);
	void upDataDeath(float t);
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

	/// <summary>
	/// ////////////////
	/// </summary>
	CCArray* weaponArray;
	CCArray* propArray;
	CCArray* chestArray;
	CCArray* monsterArray;///
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
