#ifndef __MonsterBullet_H__

#define __MonsterBullet_H__

#include "cocos2d.h"

#include "HealthPoint.h"

#include "qishi.h"

USING_NS_CC;

class MonsterBullet :public cocos2d::CCNode

{

public:

	MonsterBullet(void);

	~MonsterBullet(void);

	//根据图片名创建怪物，不带血条

	void InitMonsterBulletImage(char* name);

	//带血条的怪物 

	void InitMonsterBulletImage(char* name, char* blood_increase, char* blood_decrease);

	//设置动画,picture_num为图片数目，run_directon为精灵脸朝向，false朝右,picture_each为name_png中每一小张图片的公共名称部分

	void SetBulletAnimation(const char* picture_each, const unsigned int picture_num, bool run_directon);

	//停止动画

	void StopBulletAnimation();

	//攻击动画

	void AttackBulletAnimation(const char* picture_each, const unsigned int picture_num, bool run_directon);

	//攻击动画结束

	void AttackBulletEnd();

	//返回英雄

	CCSprite* GetBulletImage();

	//判断是否在跑动画

	bool IsRunning;

	//判断是否在攻击动画

	bool IsAttack;

	//英雄运动的方向

	bool MonsterBulletDirecton;

	//在可视范围内，怪物跟随英雄运动

	void FollowBulletRun(qishi* m_hero, Node* m_map);

	//判断是否攻击

	void JudegeBulletAttack();

	//怪物巡逻路线

	void MonsterBulletSeeRun();

	//怪物启动监听英雄

	void StartBulletListen(qishi* m_hero, Node* m_map);

	//监听函数,每隔3秒检测下，计算英雄与怪物的距离

	void updateBulletMonster(float delta);

	//更新函数，如果英雄在可视范围内，不断触发

	void updateBullet(float delta);

	//受伤动画

	void HurtBulletAnimation(const char* name_each, const unsigned int num, bool run_directon);

	//受伤动画结束

	void HurtBulletEnd();

	//判断是否在受伤动画

	bool IsHurt;

	//死亡动画

	void DeadBulletAnimation(const char* name_each, const unsigned int num, bool run_directon);

	//死亡动画结束

	void DeadBulletEnd();

	//判断是否死亡

	bool Isdead;

	//怪物死亡闪烁结束

	void BlinkBulletEnd();



	CREATE_FUNC(MonsterBullet);



private:

	CCSprite* m_MonsterImage;//怪物精灵

	char* Monster_name;//用来保存初始状态的精灵图片名称

	HealthPoint* Monster_xue;//怪物血条

	qishi* my_hero;//当前英雄

	Node* my_map;//当前地图

	float   dis;//当前怪物和英雄的距离



};

#endif // __HERO_H__#pragma once
