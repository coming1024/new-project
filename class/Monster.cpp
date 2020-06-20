#include "Monster.h"
#include "qishi.h"
#include "equipment.h"
USING_NS_CC;
Monster::Monster(void)
{
	IsRunning = false;//没在放动画
	MonsterDirecton = TRUE;//向右运动
	Monster_name = NULL;
	IsAttack = false;
	Monster_xue = NULL;
	IsHurt = false;
	Isdead = false;
	//my_hero=NULL;
	//my_map=NULL;
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
	if (MonsterDirecton)
	{
		Monster_xue->setPosition(ccp(m_MonsterImage->getPositionX() + 25, m_MonsterImage->getPositionY() + 50));//设置在怪物上头  
	}
	//Monster_xue->setScale(2.2f);  
	Monster_xue->setBackgroundTexture(xue_back);
	Monster_xue->setForegroundTexture(xue_fore);
	Monster_xue->setTotalHealth(80.0f);
	Monster_xue->setCurrentHealth(80.0f);
	this->addChild(Monster_xue);
}
void  Monster::SetAnimation(const char* name_each, unsigned int num, bool run_directon)
{
	//设置方向
	if (MonsterDirecton != run_directon)
	{
		MonsterDirecton = run_directon;
		m_MonsterImage->setFlipX(run_directon);
	}
	//正在走动、攻击、受伤或已死亡，就返回
	if (IsRunning || IsAttack)
		return;
	//设置动画
	CCAnimation* animation = CCAnimation::create();
	for (int i = 1; i <= num; i++)
	{
		char szName[100] = { 0 };
		sprintf(szName, "%s%d.png", name_each, i);
		animation->addSpriteFrameWithFileName(szName); //加载动画的帧  
	}
	animation->setDelayPerUnit(0.1f);
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
	//存在血条
	if (Monster_xue != NULL)
	{
		if (MonsterDirecton)
		{
			Monster_xue->setPosition(ccp(m_MonsterImage->getPositionX() + 20, m_MonsterImage->getPositionY() + 50));
		}
		else
			Monster_xue->setPosition(ccp(m_MonsterImage->getPositionX() - 20, m_MonsterImage->getPositionY() + 50));
	}
}
void  Monster::AttackAnimation(const char* name_each, const unsigned int num, bool run_directon)
{
	//正在走动、攻击、受伤或已死亡，就返回
	if (IsRunning || IsAttack || IsHurt || Isdead)
		return;
	CCAnimation* animation = CCAnimation::create();
	for (int i = 1; i <= num; i++)
	{
		char szName[100] = { 0 };
		sprintf(szName, "%s%d.png", name_each, i);
		animation->addSpriteFrameWithFileName(szName); //加载动画的帧  
	}
	animation->setDelayPerUnit(0.1f);
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
void Monster::FollowRun(qishi* m_hero, CCNode* m_map)
{
	//得到两点x的距离,记得怪物的坐标要加上地图的
	float x = m_hero->getPositionX() - (this->getPositionX() + m_map->getPositionX());
	//得到两点y的距离，记得怪物的坐标要加上地图的
	float y = m_hero->getPositionY() - (this->getPositionY() + m_map->getPositionY());

	//先计算怪物和英雄的距离
	dis = sqrt(pow(x, 2) + pow(y, 2));

	if (dis >= 300)//当怪物与英雄距离超过300
		return;
	if (dis <= 100)//在怪物攻击范围内，怪物停止移动
	{
		this->StopAnimation();//停止跑动
		JudegeAttack();//以一定的概率判断是是否出动攻击
		return;
	}

	if (x < -100)//判断怪物横坐标和英雄的距离
	{

		MonsterDirecton = true;
		m_MonsterImage->setFlipX(MonsterDirecton);//设置方向
		if (IsAttack)
			return;
		this->setPosition(this->getPositionX() - 1, this->getPositionY());//怪物向英雄移动
		this->SetAnimation("monster_run", 3, MonsterDirecton);//播放动画

	}
	else if (x > 100)
	{

		MonsterDirecton = false;
		m_MonsterImage->setFlipX(MonsterDirecton);//设置方向
		if (IsAttack)
			return;
		this->setPosition(this->getPositionX() + 1, this->getPositionY());
		this->SetAnimation("monster_run", 3, MonsterDirecton);//播放动画
	}
	else if (x <= 100)//怪物橫坐標和英雄相差在100以内时，开始移动怪物纵坐标
	{

		if (m_hero->getPositionY() > this->getPositionY())
		{
			m_MonsterImage->setFlipX(MonsterDirecton);//设置方向
			if (IsAttack)
				return;
			this->setPosition(this->getPositionX(), this->getPositionY() + 1);
			this->SetAnimation("monster_run", 3, MonsterDirecton);//播放动画
		}
		else if (m_hero->getPositionY() < this->getPositionY())
		{
			m_MonsterImage->setFlipX(MonsterDirecton);//设置方向
			if (IsAttack)
				return;
			this->setPosition(this->getPositionX(), this->getPositionY() - 1);
			this->SetAnimation("monster_run", 3, MonsterDirecton);//播放动画
		}
	}

}
void Monster::JudegeAttack()
{
	srand((UINT)GetCurrentTime());
	int x = rand() % 100;
	if (x > 98)
	{
		this->AttackAnimation("monster_attack", 3, MonsterDirecton);
	}

}
void  Monster::MonsterSeeRun()
{
	if (dis < 300)
		return;
	this->SetAnimation("monster_run", 3, MonsterDirecton);//播放动画
	CCMoveBy* moveby1;

	//怪物来回巡逻
	if (MonsterDirecton == true)
	{
		moveby1 = CCMoveBy::create(2, ccp(-100, 0));
		MonsterDirecton = false;
	}
		
	else
	{
		moveby1 = CCMoveBy::create(2, ccp(100, 0));
		MonsterDirecton = false;
	}
		
	//创建回调动作，巡逻路线完后
	CCCallFunc* callFunc = CCCallFunc::create(this, callfunc_selector(Monster::StopAnimation));
	//创建连续动作
	CCActionInterval* xunluo = CCSequence::create(moveby1, callFunc, NULL);
	this->runAction(xunluo);
}
//启动监听
void Monster::StartListen(qishi* m_hero, CCNode* m_map)
{
	my_hero = m_hero;
	my_map = m_map;
	this->schedule(schedule_selector(Monster::updateMonster), 3.0f);//每隔3秒计算距离
	this->scheduleUpdate();//英雄一旦进入可视范围，怪物追着英雄打
}
//监听函数,每隔3秒检测下
void Monster::updateMonster(float delta)
{
	//得到两点x的距离,记得怪物的坐标要加上地图的
	float x = my_hero->getPositionX() - (this->getPositionX() + my_map->getPositionX());
	//得到两点y的距离，记得怪物的坐标要加上地图的
	float y = my_hero->getPositionY() - (this->getPositionY() + my_map->getPositionY());
	//先计算怪物和英雄的距离
	dis = sqrt(pow(x, 2) + pow(y, 2));
	if (dis >= 300)
	{
		if (!IsRunning)
			MonsterSeeRun();
	}
}
void Monster::update(float delta)
{
	//已死亡，就返回
	if (Isdead)
		return;
	if (dis < 300)///当英雄在它的可视范围内，不断追着英雄
		FollowRun(my_hero, my_map);
}

//受伤动画
void Monster::HurtAnimation(const char* name_each, const unsigned int num, bool run_directon)
{
	if (IsHurt || Isdead)
		return;
	//受伤优先
	if (IsRunning || IsAttack)
	{
		m_MonsterImage->stopAllActions();//当前精灵停止所有动画
	   //恢复精灵原来的初始化贴图 
		this->removeChild(m_MonsterImage, TRUE);//把原来的精灵删除掉
		m_MonsterImage = CCSprite::create(Monster_name);//恢复精灵原来的贴图样子
		m_MonsterImage->setFlipX(MonsterDirecton);
		this->addChild(m_MonsterImage);
		IsRunning = false;
		IsAttack = false;
	}


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
	//创建回调动作，受伤动画结束调用HurtEnd()
	CCCallFunc* callFunc = CCCallFunc::create(this, callfunc_selector(Monster::HurtEnd));
	//创建连续动作
	CCActionInterval* hurtackact = CCSequence::create(act, callFunc, NULL);

	m_MonsterImage->runAction(hurtackact);
	IsHurt = true;


}
//受伤动画结束
void Monster::HurtEnd()
{
	IsHurt = false;
	Monster_xue->setCurrentHealth(Monster_xue->getCurrentHealth() - 10);
	if (Monster_xue->getCurrentHealth() == 0)
	{
		//播放怪物死亡动画
		DeadAnimation("monster_dead", 2, MonsterDirecton);
	}
}
//死亡动画
void Monster::DeadAnimation(const char* name_each, const unsigned int num, bool run_directon)
{
	Isdead = true;
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
	//创建回调动作，死亡结束后调用deadact()
	CCCallFunc* callFunc = CCCallFunc::create(this, callfunc_selector(Monster::DeadEnd));
	//创建连续动作
	CCActionInterval* deadact = CCSequence::create(act, callFunc, NULL);
	m_MonsterImage->runAction(deadact);

}
//死亡动画结束
void Monster::DeadEnd()
{
	//恢复死亡的样子
	this->removeChild(m_MonsterImage, TRUE);//把原来的精灵删除掉
	m_MonsterImage = CCSprite::create("monster_dead2.png");//恢复死亡的样子
	m_MonsterImage->setFlipX(MonsterDirecton);
	this->addChild(m_MonsterImage);
	//掉落血瓶
	auto propSF1=proCache->getSpriteFrameByName("addHealth.png");
	auto prop1=Prop::create(3,1,propSF1);
	prop1->setPosition(visibleSize.width/2,visibleSize.height/3);
	this->addChild(prop1,2);
	propArray->addObject(prop1);
	//auto bulletFrame=bullteCache->getSpriteFrameByName("ptzd.png");
	//auto bullet=Bullet::create(3,bulletFrame);
	//auto equipmentCRQ=equipment::create(2,3,1,1,equipmentCache,"cfqz.png",bullet);
	//equipmentCFQ->setPosition(visibleSize.width/2,visibleSize.height/2);
	//this->addChild(equipmentCFQ,2);
	//weaponArray->addObject(equipmentCFQ);
	//存在血条
	if (Monster_xue != NULL)
	{
		if (MonsterDirecton)//因为怪物中心不在图片中心，所以只能根据怪物的脸朝向，设置血条的横坐标
			Monster_xue->setPosition(ccp(m_MonsterImage->getPositionX() + 60, m_MonsterImage->getPositionY()));//设置在怪物上头  
		else
			Monster_xue->setPosition(ccp(m_MonsterImage->getPositionX() - 60, m_MonsterImage->getPositionY()));
	}
	//怪物闪两下再死亡
	CCBlink* blinkact = CCBlink::create(3, 6);//3是持续时间，6是闪的次数

	//创建回调动作，闪烁结束后调用BlinkEnd()
	CCCallFunc* callFunc = CCCallFunc::create(this, callfunc_selector(Monster::BlinkEnd));
	//创建连续动作
	CCActionInterval* deadact = CCSequence::create(blinkact, callFunc, NULL);
	m_MonsterImage->runAction(deadact);

}
//闪烁结束
void Monster::BlinkEnd()
{
	this->removeAllChildren();//把怪物和血条都删除掉;
}
