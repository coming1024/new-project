#ifndef __Monster_H__
#define __Monster_H__
#include "cocos2d.h"
//#include "ProgressView.h"
USING_NS_CC;
class Monster :public cocos2d::CCNode
{
public:
	Monster(void);
	~Monster(void);
	//根据图片名创建怪物，不带血条
	void InitMonsterImage(char* name);
	//带血条的怪物 
	void InitMonsterImage(char* name, char* blood_increase, char* blood_decrease);
	//设置动画,picture_num为图片数目，run_directon为精灵脸朝向，false朝右,picture_each为name_png中每一小张图片的公共名称部分
	void SetAnimation(const char* picture_each, const unsigned int picture_num, bool run_directon);
	//停止动画
	void StopAnimation();
	//攻击动画
	void AttackAnimation(const char* picture_each, const unsigned int picture_num, bool run_directon);
	//攻击动画结束
	void AttackEnd();
	//返回英雄
	CCSprite* GetImage();
	//判断是否在跑动画
	bool IsRunning;
	//判断是否在攻击动画
	bool IsAttack;
	//英雄运动的方向
	bool MonsterDirecton;
	CREATE_FUNC(Monster);
private:
	CCSprite* m_MonsterImage;//怪物精灵
	char* Monster_name;//用来保存初始状态的怪物图片名称
	//ProgressView* Monster_xue;//怪物血条

};
#endif // __HERO_H__
