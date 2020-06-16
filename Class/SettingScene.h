#ifndef __SETTINGSCENE_H__
#define __SETTINGSCENE_H__

#include "cocos2d.h"
#include "ParentScene.h"

class SettingScene :public ParentScene
{
public:
	//游戏界面大小声明
	cocos2d::Size VisibleSize;

	//横纵轴初始值大小声明
	cocos2d::Vec2 Origin;

public:
	SettingScene();
	~SettingScene();

	//场景初始化
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(SettingScene);
	
	//音量控制
	void VolumeControl(cocos2d::Ref* pSender);
	//返回上一个界面
	void BackToLastScene(cocos2d::Ref* pSender);
};

#endif // !__INFOSCENE_H__


