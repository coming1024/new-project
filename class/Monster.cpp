#include "Monster.h"
USING_NS_CC;
Monster::Monster(void)
{
	IsRunning = false;//没在放动画
	MonsterDirecton = TRUE;//向右运动
	Monster_name = NULL;
	IsAttack = false;
	Monster_xue = NULL;
}

Monster::~Monster(void)
{

}
CCSprite* Monster::GetImage()
{
	return m_MonsterImage;
}
void  Monster::InitMonsterImage(char* name)
{
	Monster_name = name;
	this->m_MonsterImage = CCSprite::create(name);
	m_MonsterImage->setFlipX(MonsterDirecton);
	this->addChild(m_MonsterImage);
}
void Monster::InitMonsterImage(char* name, char* xue_back, char* xue_fore)
{
	InitMonsterImage(name);
	//设置怪物的血条 
	Monster_xue = new HealthPoint();
	Monster_xue->setPosition(ccp(m_MonsterImage->getPositionX() + 25, m_MonsterImage->getPositionY() + 50));//设置在怪物上头  
	//Monster_xue->setScale(2.2f);  
	Monster_xue->setBackgroundTexture(xue_back);
	Monster_xue->setForegroundTexture(xue_fore);
	Monster_xue->setTotalProgress(300.0f);
	Monster_xue->setCurrentProgress(300.0f);
	this->addChild(Monster_xue);
}
void  Monster::SetAnimation(const char* name_each, unsigned int num, bool run_directon)
{
	if (MonsterDirecton != run_directon)
	{
		MonsterDirecton = run_directon;
		m_MonsterImage->setFlipX(run_directon);
	}
	if (IsRunning || IsAttack)
		return;
	CCAnimation* animation = CCAnimation::create();
	for (int i = 1; i <= num; i++)
	{
		char szName[100] = { 0 };
		sprintf(szName, "%s%d.png", name_each, i);
		animation->addSpriteFrameWithFileName(szName); //加载动画的帧  
	}
	animation->setDelayPerUnit(2.8f / 14.0f);
	animation->setRestoreOriginalFrame(true);
	animation->setLoops(-1); //动画循环
	//将动画包装成一个动作
	CCAnimate* act = CCAnimate::create(animation);
	m_MonsterImage->runAction(act);
	IsRunning = true;

}
void  Monster::StopAnimation()
{
	if (!IsRunning)
		return;
	m_MonsterImage->stopAllActions();//当前精灵停止所有动画
	//恢复精灵原来的初始化贴图 
	this->removeChild(m_MonsterImage, TRUE);//把原来的精灵删除掉
	m_MonsterImage = CCSprite::create(Monster_name);//恢复精灵原来的贴图样子
	m_MonsterImage->setFlipX(MonsterDirecton);
	this->addChild(m_MonsterImage);
	IsRunning = false;
}
void  Monster::AttackAnimation(const char* name_each, const unsigned int num, bool run_directon)
{
	if (IsAttack || IsRunning)
		return;
	CCAnimation* animation = CCAnimation::create();
	for (int i = 1; i <= num; i++)
	{
		char szName[100] = { 0 };
		sprintf(szName, "%s%d.png", name_each, i);
		animation->addSpriteFrameWithFileName(szName); //加载动画的帧  
	}
	animation->setDelayPerUnit(2.8f / 14.0f);
	animation->setRestoreOriginalFrame(true);
	animation->setLoops(1); //动画循环1次  
	//将动画包装成一个动作
	CCAnimate* act = CCAnimate::create(animation);
	//创建回调动作，攻击结束后调用AttackEnd()
	CCCallFunc* callFunc = CCCallFunc::create(this, callfunc_selector(Monster::AttackEnd));
	//创建连续动作
	CCActionInterval* attackact = CCSequence::create(act, callFunc, NULL);

	m_MonsterImage->runAction(attackact);
	IsAttack = true;

}
void Monster::AttackEnd()
{
	//恢复精灵原来的初始化贴图 
	this->removeChild(m_MonsterImage, TRUE);//把原来的精灵删除掉
	m_MonsterImage = CCSprite::create(Monster_name);//恢复精灵原来的贴图样子
	m_MonsterImage->setFlipX(MonsterDirecton);
	this->addChild(m_MonsterImage);
	IsAttack = false;
}
