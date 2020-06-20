
#ifndef __INFOSCENE_H__
#define __INFOSCENE_H__

#include "cocos2d.h"

class InfoScene :public cocos2d::Scene
{
public:
	//游戏界面大小声明
	cocos2d::Size VisibleSize;

	//横纵轴初始值大小声明
	cocos2d::Vec2 Origin;
public:
	InfoScene();
	~InfoScene();

	//场景初始化
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(InfoScene);

	//返回主界面
	void BackToLastScene(cocos2d::Ref* pSender);
};

#endif // !__INFOSCENE_H__